#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Keypad.h>
#include <HardwareSerial.h>
#include "Adafruit_Thermal.h"
#include "adalogo.h"
#include <WebServer.h>

#define RSTPIN 22
#define SSPIN 21

WebServer server(80);  // REST API server

#define ROW_NUM 4    // four rows
#define COLUMN_NUM 4 // four columns

char My_Array[20];
int count = 0;
int aantal10 = 0;
int aantal20;
int aantal50;
int opgenomenBedrag;
String naam;
String pasnummer;
#define servo1 9

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte pin_rows[ROW_NUM] = {13, 12, 14, 27};
byte pin_column[COLUMN_NUM] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

String input_password;

// SPI for ESP32
#define SCK 18
#define MISO 19
#define MOSI 23

const int printerBaudrate = 19200;

// Thermal Printer
#define PRINTER_RX 16 // RX on ESP32 (to printer TX)
#define PRINTER_TX 17 // TX on ESP32 (to printer RX)
HardwareSerial mySerial(1);
Adafruit_Thermal myPrinter(&mySerial);

MFRC522 rc(SSPIN, RSTPIN);

// WiFi credentials
const char *ssid = "Scott";
const char *password = "ChickenSteel";

// Backend server IP and port (Docker host)
const char *serverURL = "http://192.168.81.29:3000"; // Replace Ipgoeshere with host IP

const int UID_LEN = 4;
byte readcard[UID_LEN];

void setup()
{
  Serial.begin(115200);
  mySerial.begin(printerBaudrate, SERIAL_8N1, PRINTER_RX, PRINTER_TX);
  myPrinter.begin();
  myPrinter.setDefault();
  input_password.reserve(32); // maximum input characters is 33

  SPI.begin(SCK, MISO, MOSI, SSPIN);
  rc.PCD_Init();

  ServoInit(9, 0);
  ServoInit(10, 0);
  ServoInit(11, 0);

    server.on("/api/withdraw", HTTP_POST, []() {
    if (server.hasArg("plain") == false) {
      server.send(400, "application/json", "{\"error\":\"Missing body\"}");
      return;
    }

    String body = server.arg("plain");
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, body);

    if (error) {
      server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
      return;
    }

    int amount = doc["amount"];
    String kaart_id = doc["kaart_id"]; // optioneel, afhankelijk van frontend

    int remaining = amount;
    aantal50 = remaining / 50; remaining %= 50;
    aantal20 = remaining / 20; remaining %= 20;
    aantal10 = remaining / 10; remaining %= 10;

    if (remaining != 0) {
      server.send(400, "application/json", "{\"error\":\"Ongeldig bedrag, niet uit te keren in 10/20/50\"}");
      return;
    }

    opgenomenBedrag = amount;
    Serial.printf("Opname aangevraagd: €%d\n", amount);
    printMoney();
    printBon();

    server.send(200, "application/json", "{\"message\":\"Succesvol opgenomen\"}");
  });

  server.begin(); // Start de webserver

  
  scanNetworks();
  connectWiFi();

  
}

void loop()
{
  if (!getid())
    return;

  // Read UID on pass and convert to String
  //------------------------------------------
  String uidString = "";
  for (int i = 0; i < UID_LEN; i++)
  {
    if (readcard[i] < 0x10)
      uidString += "0"; // zero padding
    uidString += String(readcard[i], HEX);
  }
  uidString.toLowerCase();
  //------------------------------------------

  // Connect to backend if wifi access available
  //------------------------------------------
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String url = String(serverURL) + "/kaart/" + uidString;
    Serial.println("Connecting to: " + url);
    http.begin(url);
    int httpCode = http.GET();
    Serial.println(httpCode);
    //----------------------------------------

    // HTTP responses dictate what happens
    //----------------------------------------
    if (httpCode == 200)
    {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);

      if (error)
      {
        Serial.print("JSON parse fout: ");
        Serial.println(error.c_str());
        return;
      }

      String voornaam = doc["voornaam"];
      String pincodeFromDB = doc["pincode"];
      Serial.println("Server response: " + payload);
      Serial.println("Welkom, " + voornaam + "!");
      Serial.println("Voer uw pincode in:");
      Serial.println("Voer uw pincode in:");
      input_password = "";

      while (true)
      {
        char key = keypad.getKey();
        if (key)
        {
          if (key == '*')
          {
            // Zodra gebruiker op '*' drukt, stuur de pincode naar server
            HTTPClient http;
            http.begin(String(serverURL) + "/kaart/validate");
            http.addHeader("Content-Type", "application/json");

            String postData = "{\"kaart_id\":\"" + uidString + "\",\"pincode\":\"" + input_password + "\"}";
            int httpResponseCode = http.POST(postData);
            String response = http.getString();

            if (httpResponseCode == 200)
            {
              Serial.println("Pincode correct! Welkom!");
            }
            else if (httpResponseCode == 401)
            {
              Serial.println("Verkeerde pincode.");
            }
            else
            {
              Serial.println("Serverfout bij pincodevalidatie.");
              Serial.println(response);
            }

            http.end();
            break; // Stop na validatie
          }
          else if (key == '#')
          {
            Serial.println("Geannuleerd.");
            input_password = "";
            break;
          }
          else
          {
            input_password += key;
            Serial.print("*"); // Masked input
          }
        }
      }
    }
    else if (httpCode == 404)
    {
      Serial.println("Gebruiker niet gevonden. Toevoegen? (yes/no)");
      waitForSerial();
      String ans = Serial.readStringUntil('\n');
      ans.trim();

      if (ans.equalsIgnoreCase("yes"))
      {
        Serial.println("Voornaam invoeren:");
        waitForSerial();
        String name = Serial.readStringUntil('\n');
        name.trim();

        http.end(); // Reuse HTTP client for POST
        http.begin(String(serverURL) + "/Gebruiker");
        http.addHeader("Content-Type", "application/json");

        String postData = "{\"gebruiker_id\":\"" + uidString + "\",\"voornaam\":\"" + name + "\"}";
        int code = http.POST(postData);

        if (code == 201)
        {
          Serial.println("Gebruiker toegevoegd!");
        }
        else
        {
          Serial.print("Fout bij toevoegen: ");
          Serial.println(code);
        }
      }
      else
      {
        Serial.println("Gebruiker niet toegevoegd.");
      }
    }
    else
    {
      Serial.print("Server error: ");
      Serial.println(httpCode);
    }

    http.end();
  }
  else
  {
    Serial.println("WiFi niet verbonden.");
  }
  delay(1000);

  char C = Serial.read();
   if(C == '.') 
   {
      count = 0;
      String nothing = String(My_Array);
      memset(My_Array, 0, sizeof(My_Array));
        if(nothing.charAt(0)=='1'){   //aantal 10
          nothing.remove(0,1);
         aantal10 = nothing.toInt();     
        }
        else if(nothing.charAt(0)=='2'){   //aantal 20
          nothing.remove(0,1);
          aantal20 = nothing.toInt();
        }
        else if(nothing.charAt(0)=='3'){   //aantal 50                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
          nothing.remove(0,1);
          aantal50 = nothing.toInt();
        }
        else if(nothing.charAt(0)=='4'){   //naam gebruiker
          nothing.remove(0,1);
          naam = nothing;
        }
        else if(nothing.charAt(0)=='5'){   //pasnummer
          nothing.remove(0,7);
          pasnummer = nothing;
        }
        else if(nothing.charAt(0)=='7'){
          Serial.println("Initiate money printing..(met bon)");
          opgenomenBedrag = (aantal10*10)+(aantal20*20)+(aantal50*50);
          printMoney();
          Serial.println("Done.");
          Serial.println("Print bon..");
          delay(1000);
          printBon();
          Serial.println("Done.");
        }
        else if(nothing.charAt(0)=='8'){
          Serial.println("Initiate money printing..(zonder bon)");
          printMoney();
          Serial.println("Done.");
        }
   }
   else{  My_Array[count++] = C; 
   }
  server.handleClient();
}
//----------------------------------------

// Scan for available networks on the ESP32
//----------------------------------------
void scanNetworks()
{
  int n = WiFi.scanNetworks();
  Serial.println("Scan complete");
  for (int i = 0; i < n; ++i)
  {
    Serial.printf("%d: %s (%d)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
}

void ServoInit(int pin, int p) {
  int pulseDuration = 1400;
  if (p == 1) {
    //Go UP
    pulseDuration = 1000;
  } else if (p == -1) {
    //Go DOWN
    pulseDuration = 2000;
  } else if (p == 0) {
    //STOP
    pulseDuration = 1400;
  }
  int totalDuration = 20000;
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulseDuration);
  digitalWrite(pin, LOW);
  delayMicroseconds(totalDuration - pulseDuration); // the duration of from pulse to pusle is 20ms
}
//----------------------------------------
void printMoney(){
  while(aantal10!=0){
    Serial.println("Print 10");
    ServoInit(9, 0);
    ServoInit(9, 1);
    delay(1400);
    ServoInit(9, 0);
    aantal10--;
    delay(2000);
  }
  while(aantal20!=0){
    Serial.println("Print 20");
    ServoInit(10, 0);
    ServoInit(10, -1);
    delay(1250);
    ServoInit(10, 0);
    aantal20--;
    delay(2000);
  }
  while(aantal50!=0){
    Serial.println("Print 50");
    ServoInit(11, 0);
    ServoInit(11, -1);
    delay(1300);
    ServoInit(11, 0);
    aantal50--;
    delay(2000);
  }
}


// Get the UID of the pass
//----------------------------------------
bool getid()
{
  if (!rc.PICC_IsNewCardPresent() || !rc.PICC_ReadCardSerial())
    return false;

  for (int i = 0; i < UID_LEN; i++)
  {
    readcard[i] = rc.uid.uidByte[i];
  }
  rc.PICC_HaltA();
  Serial.print("Gescand UID: ");
  for (int i = 0; i < UID_LEN; i++)
  {
    Serial.print(readcard[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  return true;
}
//----------------------------------------

// Connect ESP32 to WIFI using SSID and password
//----------------------------------------
void connectWiFi()
{
  Serial.print("Verbinden met WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi verbonden");
  Serial.print("IP adres: ");
  Serial.println(WiFi.localIP());
}
//----------------------------------------

// Print receipt with data from transaction
//----------------------------------------
void printBon()
{
  myPrinter.printBitmap(bitmap_width, bitmap_height, epd_bitmap_Banque_1__6_);
  myPrinter.println(F("========="));
  myPrinter.justify('C');
  myPrinter.println(F("Banque"));
  myPrinter.println(F("========="));

    
  myPrinter.print(F("PassNr.: XXXXXX"));
  myPrinter.println(pasnummer);
  myPrinter.println(F("====="));

  myPrinter.print(F("Bedrag: $"));
  myPrinter.println(opgenomenBedrag);
  myPrinter.println(F("====="));
}
//----------------------------------------

void waitForSerial()
{
  while (!Serial.available())
    delay(10);
}
