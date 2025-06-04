# 1 "C:\\Users\\scott\\AppData\\Local\\Temp\\tmprxubmv__"
#include <Arduino.h>
# 1 "C:/Users/scott/OneDrive/School TI 1/OP3/Project/Code/CodeKS/src/kaart_scanner.ino"
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Keypad.h>
#include <HardwareSerial.h>
#include "Adafruit_Thermal.h"
#include "adalogo.h"

#define RSTPIN 22
#define SSPIN 21

#define ROW_NUM 4
#define COLUMN_NUM 4

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte pin_rows[ROW_NUM] = {13, 12, 14, 27};
byte pin_column[COLUMN_NUM] = {26, 25, 33, 32};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

String input_password;


#define SCK 18
#define MISO 19
#define MOSI 23

const int printerBaudrate = 19200;


#define PRINTER_RX 16
#define PRINTER_TX 17
HardwareSerial mySerial(1);
Adafruit_Thermal myPrinter(&mySerial);

MFRC522 rc(SSPIN, RSTPIN);


const char *ssid = "Scott";
const char *password = "ChickenSteel";


const char *serverURL = "http://192.168.81.29:3000";

const int UID_LEN = 4;
byte readcard[UID_LEN];
void setup();
void loop();
void scanNetworks();
bool getid();
void connectWiFi();
void printBon();
void waitForSerial();
#line 55 "C:/Users/scott/OneDrive/School TI 1/OP3/Project/Code/CodeKS/src/kaart_scanner.ino"
void setup()
{
  Serial.begin(115200);
  mySerial.begin(printerBaudrate, SERIAL_8N1, PRINTER_RX, PRINTER_TX);
  myPrinter.begin();
  myPrinter.setDefault();
  input_password.reserve(32);

  SPI.begin(SCK, MISO, MOSI, SSPIN);
  rc.PCD_Init();

  scanNetworks();
  connectWiFi();
}

void loop()
{
  if (!getid())
    return;



  String uidString = "";
  for (int i = 0; i < UID_LEN; i++)
  {
    if (readcard[i] < 0x10)
      uidString += "0";
    uidString += String(readcard[i], HEX);
  }
  uidString.toLowerCase();




  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String url = String(serverURL) + "/kaart/" + uidString;
    Serial.println("Connecting to: " + url);
    http.begin(url);
    int httpCode = http.GET();
    Serial.println(httpCode);




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

            HTTPClient http;
            http.begin(String(serverURL) + "/kaart/validate");
            http.addHeader("Content-Type", "application/json");

            String postData = "{\"kaart_id\":\"" + uidString + "\",\"pincode\":\"" + input_password + "\"}";
            int httpResponseCode = http.POST(postData);
            String response = http.getString();

            if (httpResponseCode == 200)
            {
              Serial.println("Pincode correct! Welkom!");
              printBon();
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
            break;
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
            Serial.print("*");
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

        http.end();
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
}




void scanNetworks()
{
  int n = WiFi.scanNetworks();
  Serial.println("Scan complete");
  for (int i = 0; i < n; ++i)
  {
    Serial.printf("%d: %s (%d)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
}




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




void printBon()
{
  myPrinter.printBitmap(bitmap_width, bitmap_height, epd_bitmap_Banque_1__6_);
}


void waitForSerial()
{
  while (!Serial.available())
    delay(10);
}