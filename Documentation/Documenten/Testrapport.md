# Test Rapport – Project ¾ – Groep 1

Dennis Zejnilovic (1098617), Scott van der Heijden (1103349), Arda Keskin (1096673), Julius de Maesschalck (1101422)

Klas: 1-A

-----
## 1. Test 1

#### 1.1. Testdoel

---

Verifiëren dat het logo correct en volledig geprint wordt op bonpapier via de aangesloten thermische bonprinter.

#### 1.2. Testopstelling

---

- Thermische bonprinter
- Laptop met code
- Testlogo als bitmap

#### 1.3. Uitvoer van de test

---

Na het activeren van de printopdracht startte de thermische bonprinter onmiddellijk met printen. Het resultaat was een bon met het logo duidelijk en scherp aan de bovenkant van het papier. Er werden geen extra onbedoelde teksten, symbolen of vlekken geprint. De printkwaliteit was consistent zonder strepen, witte plekken of vervormingen, en het printproces verliep zonder onderbrekingen of foutmeldingen.

#### 1.4. Verwachte resultaat

---

- Het logo wordt correct weergegeven.
- Geen fouten op de console of logging.

#### 1.5. Acceptatiecriteria

---

- Logo is volledig en correct geprint.
- Geen visuele afwijkingen.
- Geen fouten op de console of logging.

#### 1.6. Testresultaten en conclusie

---

- Het logo werd direct en volledig zichtbaar geprint zonder visuele fouten of afwijkingen.
- Tijdens de opdracht en uitvoer traden geen foutmeldingen of problemen op.
- De thermische bonprinter functioneert naar behoren binnen het systeem en voldoet aan alle gestelde criteria.
- **Conclusie:** De test is succesvol afgerond en het printen van het logo kan zonder aanpassingen in productie worden genomen.
  
## 2. Test 2

#### 2.1. Testdoel

---

Controleren of de RFID-lezer correct functioneert in combinatie met de GUI en of de kaartinformatie correct wordt gevalideerd aan de hand van de gegevens in de database.

#### 2.2. Testopstelling

---

- RFID-lezer verbonden aan een ESP32
- RFID-kaart
- Laptop met draaiende GUI en database

#### 2.3. Uitvoer van de test

---

Bij het scannen van een RFID-kaart detecteerde de lezer de kaart binnen enkele seconden. Direct daarna verscheen een invoerveld voor de pincode op de GUI. Bij het invoeren van de correcte pincode werd het hoofdmenu getoond. Bij een foutieve pincode gaf het systeem een duidelijke foutmelding weer. De communicatie tussen de ESP32, GUI, backend en database verliep soepel zonder merkbare vertraging of fouten. Alle systeemonderdelen reageerden binnen de gestelde tijdslimieten.

#### 2.4. Verwachte resultaat

---

- RFID-lezer detecteert kaart binnen 2 seconden
- UID wordt correct verzonden naar de GUI
- GUI stuurt de UID naar de backend
- Backend controleert UID tegen de database
- Systeem toont afhankelijk van de status een goed/fout scherm
- Geen crashes of communicatieproblemen

#### 2.5. Acceptatiecriteria

---

- Kaart wordt binnen 2 seconden herkend
- UID komt correct door het hele systeem heen
- Backend valideert tegen juiste database-invoer
- GUI reageert correct op geldige/ongeldige status
- Logging toont geen fouten in communicatie

#### 2.6. Testresultaten en conclusie

---

- Geldige kaarten werden succesvol herkend en verwerkt, waarna pincode-invoer correct startte.
- Ongeldige kaarten werden met een duidelijke melding afgewezen.
- Logging bevestigde een foutloze communicatie tussen ESP32, GUI, API en database.
- De gemiddelde reactietijd lag ruim binnen de limiet van 2 seconden.
- **Conclusie:** De RFID-lezer en backend validatie functioneren volledig conform de eisen. De integratie met de GUI is robuust en klaar voor productie.
  
## 3. Test 3

#### 3.1. Testdoel

---

Verifiëren dat bij het scannen van een geldige RFID-kaart automatisch een bon wordt geprint waarop de naam van de kaarthouder correct en leesbaar staat vermeld.

#### 3.2. Testopstelling

---

- RFID-lezer aangesloten op ESP32
- Thermische bonprinter
- Laptop met code
- Geldige kaart met bijbehorende naam “Scott van der Heijden”

#### 3.3. Uitvoer van de test

---

Na het scannen van de geldige kaart werd de naam “Scott van der Heijden” binnen enkele seconden automatisch op de bon geprint. De tekst was volledig, correct gespeld en scherp leesbaar zonder vervormingen of weggevallen tekens. Het printproces startte direct na het scannen en er waren geen vertragingen of fouten zichtbaar in de interface of logbestanden.

#### 3.4. Verwachte resultaat

---

- RFID-kaart wordt herkend.
- Tekst op bon is volledig, correct gespeld, en duidelijk leesbaar.

#### 3.5. Acceptatiecriteria

---

- Correcte naam op bon bij geldige kaart
- Geen foutmeldingen of vertragingen.
- Geen vervorming of tekens weggevallen op bon

#### 3.6. Testresultaten en conclusie

---

- UID werd correct uitgelezen en gekoppeld aan de juiste naam.
- De bonprinter produceerde een duidelijke en foutloze afdruk met de correcte naam.
- Er traden geen fouten of vertragingen op tijdens het proces.
- **Conclusie:** De automatische printfunctie na RFID-scan werkt foutloos en voldoet aan alle eisen, klaar voor integratie in het eindproduct.
  
## 4. Test 4

#### 4.1. Testdoel

---

Verifiëren of de API succesvol kan communiceren met de database wanneer er een verzoek wordt gedaan voor het ophalen van informatie uit de database.

#### 4.2. Testopstelling

---

- API
- Laptop met code en toegang tot database

#### 4.3. Uitvoer van de test

---

Na het opstarten van de API en het openen van een testpagina in de browser word een query uitgevoerd om gegevens uit de database op te halen. De opgehaalde gegevens, waaronder namen en klant-ID’s, werden correct en snel getoond. Er traden geen fouten of vertragingen op en meerdere tabellen konden succesvol worden benaderd.

#### 4.4. Verwachte resultaat

---

- Bij het opvragen van gegevens krijgen we een naam en klantenID te zien wat bevestigt dat de communicatie werkt.

#### 4.5. Acceptatiecriteria

---

- Informatie is zichtbaar op de webpagina
- De informatie is correct en komt overeen met de database

#### 4.6. Testresultaten en conclusie

---

- Data werd direct en correct weergegeven.
- Meerdere tabellen waren toegankelijk zonder problemen.
- **Conclusie:** De API communiceert succesvol met de database en levert betrouwbare data, wat essentieel is voor verdere systeemintegratie.
  
## 5. Test 5

#### 5.1. Testdoel

Verifiëren dat de frontend kan samenwerken met de API.

#### 5.2. Testopstelling

- Laptop met de frontend code
- Laptop met de API
- Laptop met toegang tot database

#### 5.3. Uitvoer van de test

Met de frontend GUI draaiend en de API actief werd een gesimuleerde kaartscan uitgevoerd via een command prompt met een curl POST request. De frontend registreerde deze scan correct, waarbij het kaartnummer werd opgeslagen. Vervolgens ging de pagina automatisch over naar het pincode-invoerscherm. Er waren geen serverfouten of andere problemen die de voortgang belemmerden.

#### 5.4. Verwachte resultaat

- De pagina registreert de kaart scan.
- De pagina gaat door naar het volgende scherm waar de kaart scan onthouden wordt voor de pincode.

#### 5.5. Acceptatiecriteria

- De pagina registreert de scan en onthoud het kaartnummer.
- De pagina gaat door naar het pincode scherm.
- Er zijn geen serverfouten of errors die vooruitgang voorkomen.

#### 5.6. Testresultaten en conclusie

- De frontend herkende en verwerkte de gesimuleerde pas scan zonder problemen.
- De backend onthield het pasnummer correct.
- De frontend navigeerde succesvol naar het pincode scherm.
- **Conclusie:** De samenwerking tussen frontend en API functioneert correct en is geschikt voor verdere uitrol binnen het systeem.

##  6. <a name='Changelog'></a>Changelog

Datum      | Versie | Omschrijving              | Auteur |
---------- | ------ | ------------------------- | ------ |
03-06-2025 | v1     | Eerste versie             | Arda   |
04-06-2025 | v2     | Uitgebreid met meer tests | Scott  |