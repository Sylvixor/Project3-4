# Test Rapport – Project ¾ – Groep 1

Dennis Zejnilovic (1098617), Scott van der Heijden (1103349), Arda Keskin (1096673), Julius de Maesschalck (1101422)

Klas: 1-A

## Inhoudsopgave

* 1. [Test 1](#Test1)
	* 1.1. [Testdoel](#Testdoel)
	* 1.2. [Testopstelling](#Testopstelling)
	* 1.3. [Uitvoer van de tekst](#Uitvoervandetest)
	* 1.4. [Verwachte resultaat](#Verwachteresultaat)
	* 1.5. [Acceptatiecriteria](#Acceptatiecriteria)
	* 1.6. [Testresultaten](#Testresultaten)
	* 1.7. [Conclusie](#Conclusie)
* 2. [Test 2](#Test2)
	* 2.1. [Testdoel](#Testdoel-1)
	* 2.2. [Testopstelling](#Testopstelling-1)
	* 2.3. [Uitvoer van de tekst](#Uitvoervandetest-1)
	* 2.4. [Verwachte resultaat](#Verwachteresultaat-1)
	* 2.5. [Acceptatiecriteria](#Acceptatiecriteria-1)
	* 2.6. [Testresultaten](#Testresultaten-1)
	* 2.7. [Conclusie](#Conclusie-1)
* 3. [Test 3](#Test3)
	* 3.1. [Testdoel](#Testdoel-2)
	* 3.2. [Testopstelling](#Testopstelling-2)
	* 3.3. [Uitvoer van de tekst](#Uitvoervandetest-2)
	* 3.4. [Verwachte resultaat](#Verwachteresultaat-2)
	* 3.5. [Acceptatiecriteria](#Acceptatiecriteria-2)
	* 3.6. [Testresultaten](#Testresultaten-2)
	* 3.7. [Conclusie](#Conclusie-2)
* 4. [Changelog](#Changelog)

##  1. <a name='Test1'></a>Test 1

###  1.1. <a name='Testdoel'></a>Testdoel

---

Verifiëren dat het logo correct en volledig geprint wordt op bonpapier via de aangesloten thermische bonprinter.

###  1.2. <a name='Testopstelling'></a>Testopstelling

---

- Thermische bonprinter.
- Laptop met code.
- Testlogo als bitmap.

###  1.3. <a name='Uitvoervandetest'></a>Uitvoer van de tekst

---

De thermische printer genereerde een bon met een duidelijk zichtbaar logo aan de bovenkant van het papier. Geen extra tekst of symbolen aanwezig. Print kwam direct 
na het activeren van de opdracht.

###  1.4. <a name='Verwachteresultaat'></a>Verwachte resultaat

---

- Het logo wordt correct weergegeven.
- Geen fouten op de console of logging.

###  1.5. <a name='Acceptatiecriteria'></a>Acceptatiecriteria

---

- Logo is volledig en correct geprint.
- Geen visuele afwijkingen.
- Geen fouten op de console of logging.

###  1.6. <a name='Testresultaten'></a>Testresultaten

---

- ✅ Logo werd direct en volledig zichtbaar geprint
- ✅ Geen visuele fouten of printproblemen
- ✅ Geen foutmeldingen tijdens opdracht of uitvoer

###  1.7. <a name='Conclusie'></a>Conclusie

---

De test is geslaagd. De bonprinter print het logo zoals verwacht, voldoet aan de performancecriteria, en functioneert correct binnen het systeem. Dit onderdeel is klaar voor gebruik in productie.

##  2. <a name='Test2'></a>Test 2

###  2.1. <a name='Testdoel-1'></a>Testdoel

---

Controleren of de RFID-lezer correct functioneert in combinatie met de GUI en of de kaartinformatie correct wordt gevalideerd aan de hand van de gegevens in de database.

###  2.2. <a name='Testopstelling-1'></a>Testopstelling

---

- RFID-lezer verbonden aan een ESP32.
- RFID-kaart.
- Laptop met draaiende GUI en database.

###  2.3. <a name='Uitvoervandetest-1'></a>Uitvoer van de tekst

---

De kaart word gescant, waarna je de pincode kan invoeren om op het hoofdmenu te komen. Foutieve invoer geeft een error terug.

###  2.4. <a name='Verwachteresultaat-1'></a>Verwachte resultaat

---

- RFID-lezer detecteert kaart binnen 2 seconden
- UID wordt correct verzonden naar de GUI
- GUI stuurt de UID naar de backend
- Backend controleert UID tegen de database
- Systeem toont afhankelijk van de status een goed/fout scherm
- Geen crashes of communicatieproblemen

###  2.5. <a name='Acceptatiecriteria-1'></a>Acceptatiecriteria

---

- Kaart wordt binnen 2 seconden herkend
- UID komt correct door het hele systeem heen
- Backend valideert tegen juiste database-invoer
- GUI reageert correct op geldige/ongeldige status
- Logging toont geen fouten in communicatie

###  2.6. <a name='Testresultaten-1'></a>Testresultaten

---

- ✅ Geldige kaart werd succesvol verwerkt: pincode-invoer gestart
- ✅ Ongeldige kaart werd correct afgewezen met duidelijke melding
- ✅ Logging bevestigde correcte communicatie ESP32 → GUI → API → DB
- ✅ Reactietijd gemiddeld: 1.3 seconden
- ✅ Geen fouten, vertragingen of miscommunicatie gedetecteerd

###  2.7. <a name='Conclusie-1'></a>Conclusie

---

De test is geslaagd. De volledige flow van kaartinvoer via de RFID-lezer tot validatie in de backend werkt correct en voldoet aan de gestelde eisen. De GUI en API reageren zoals verwacht en het systeem is klaar voor verdere integratie.

##  3. <a name='Test3'></a>Test 3

###  3.1. <a name='Testdoel-2'></a>Testdoel

---

Verifiëren dat bij het scannen van een geldige RFID-kaart automatisch een bon wordt geprint waarop de naam van de kaarthouder correct en leesbaar staat vermeld.

###  3.2. <a name='Testopstelling-2'></a>Testopstelling

---

- RFID-lezer aangesloten op ESP32.
- Thermische bonprinter.
- Laptop met code.
- Geldige kaart met bijbehorende naam “Scott van der Heijden”.

###  3.3. <a name='Uitvoervandetest-2'></a>Uitvoer van de tekst

---

Na het scannen van de geldige kaart werd er direct een bon geprint met de tekst:

```Scott van der Heijden```

###  3.4. <a name='Verwachteresultaat-2'></a>Verwachte resultaat

---

- RFID-kaart wordt herkend.
- Tekst op bon is volledig, correct gespeld, en duidelijk leesbaar.

###  3.5. <a name='Acceptatiecriteria-2'></a>Acceptatiecriteria

---

- Correcte naam op bon bij geldige kaart
- Geen foutmeldingen of vertragingen.
- Geen vervorming of tekens weggevallen op bon

###  3.6. <a name='Testresultaten-2'></a>Testresultaten

---

- ✅ UID correct gelezen.
- ✅ Bon geprint met correcte en leesbare tekst
- ✅ Geen fouten of vertragingen gelogd

###  3.7. <a name='Conclusie-2'></a>Conclusie

---

De test is geslaagd. Het systeem koppelt de UID succesvol aan de juiste kaarthouder en print binnen enkele seconden een correcte bon. De complete flow van RFID-scan tot thermisch printen functioneert foutloos en voldoet aan alle acceptatiecriteria.

##  4. <a name='Changelog'></a>Changelog

| Datum      | Versie | Omschrijving  | Auteur | Opmerkingen |
| ---------- | ------ | ------------- | ------ | ----------- |
| 03-06-2025 | v1     | Eerste versie | Arda   |             |