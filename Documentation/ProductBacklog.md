### Groep 1:
- Arda Keskin [ 1096673 ]
- Dennis Zejnilovic [ 1098617 ]
- Scott van der Heijden [ 1103349 ]
- Julius De Maesschalck [ 1101422 ]

### User Stories

#### Must haves

---

| #  | User Story | Requirements | Taken | Acceptatiecriteria | Story Points |
|----|------------|--------------|-------|--------------------|--------------|
| 1  | Als bank wil ik dat de pinautomaat alleen euro’s gebruikt als valuta, omdat de automaat in een euroland komt te staan en alleen met deze munteenheid betaald kan worden. | In de bank zitten alleen euro's. | De kas moet gevuld worden met eurobiljetten. | Er zitten niets anders dan euro's in de bank. |  5
| 2  | Als eindgebruiker wil ik geld kunnen opnemen bij de pinautomaat, zodat ik contant geld kan gebruiken voor betalingen. | Pinautomaat kan geld uitegeven via een uitgeef gleuf. | Behuizing van uitgeef gleuf maken, actuator(en) toevoegen in de uitgeef gleuf, logica van de uitgeef gleuf onderzoeken, Pinautomaat briefgeld laten uitgeven. | Eindgebruiker ontvangt contant geld na succesvolle transactie. |  8
| 3  | Als bank wil ik dat er een transactielimiet van 1000 euro is, zodat de rekening van de eindgebruiker veiliger is tegen diefstal en de automaat minder vaak bijgevuld hoeft te worden. | Transactielimiet per opname. | Maximaal 1000 euro per transactie limiet . | Er kan nooit meer dan 1000 euro per opname worden opgenomen. |  6
| 4  | Als eindgebruiker wil ik zelf kunnen aangeven welk briefgeld ik ontvang, zodat ik het geld in een voor mij handige samenstelling krijg. | Keuze in biljetten. | Gebruiker kan voorkeur aangeven. | Pinautomaat biedt keuzemogelijkheden voor biljetten. |  5
| 5  | Als bank wil ik dat de pinautomaat alleen briefjes tussen 10 en 50 euro bevat, zodat er geen onhandig klein of te groot briefgeld in omloop is. | Alleen 10, 20 en 50 euro biljetten. | Pinautomaat bevat alleen deze biljetten. | Automaat bevat geen andere biljetten dan 10, 20 en 50 euro. |  3
| 6  | Als bank wil ik geen toegang hebben tot de rekeningen en het geld daarop, zodat de privacy en veiligheid van eindgebruikers gewaarborgd blijft. | Geen directe toegang tot rekeningen. | Bank beheert geen saldo. | Bank kan saldo niet inzien of wijzigen. |  4
| 7  | Als eindgebruiker wil ik mijn saldo kunnen zien tijdens de interactie, zodat ik weet hoeveel geld ik nog heb voor opnames. | Saldo-overzicht beschikbaar. | Saldo wordt weergegeven op de GUI. | Gebruiker ziet saldo voordat een opname wordt gedaan. |  6
| 8  | Als bank wil ik dat een transactie stopt als de eindgebruiker wegloopt zonder af te ronden, zodat onbevoegden geen toegang krijgen tot het geld. | Automatische annulering. | Tijdslimiet op transacties implementeren. | Transactie wordt geannuleerd als gebruiker niet op tijd reageert. |  7
| 9  | Als bank wil ik dat de pinautomaat tussen 1.000 en 10.000 euro aan contant geld bevat, zodat er altijd voldoende geld beschikbaar is zonder te veel risico. | Minimum en maximum kasinhoud. | Automaat moet voldoende voorraad hebben. | Contant geld ligt tussen 1.000 en 10.000 euro. |  5
| 10 | Als bank wil ik dat de pinautomaat een oneindig aantal gebruikers aankan, zodat het systeem schaalbaar blijft voor nieuwe eindgebruikers. | Onbeperkte gebruikerscapaciteit. | De database heeft geen limiet voor het aantal gebruikers die kunnen worden aangemaakt | Geen limiet op aantal transacties of gebruikers. |  7
| 11 | Als bank wil ik eindgebruikersgegevens kunnen beheren (maar niet het saldo), zodat ik accounts kan aanmaken en updaten zonder financiële toegang. | Gebruikersbeheer zonder saldo-toegang. | Behering van de bank via de database | Bank kan accounts aanmaken/wijzigen zonder saldo-inzage. |  5
| 12 | Als eindgebruiker wil ik na drie foutieve pincode-invoeringen een waarschuwing krijgen, zodat ik weet dat mijn pas geblokkeerd wordt bij de volgende fout. | Pincode beveiliging. | Waarschuwingsmelding na 3 foute pogingen. | Gebruiker wordt gewaarschuwd na 3 fouten. |  6
| 13 | Als bank wil ik passen kunnen blokkeren en deblokkeren, zodat verloren of gestolen passen beveiligd kunnen worden. | Pasbeheerfunctie. | Functie om passen te blokkeren/deblokkeren. | Blokkade en deblokkade functionaliteit beschikbaar. |  8
| 14 | Als eindgebruiker wil ik mijn contactloze pas kunnen gebruiken bij de pinautomaat, zodat ik sneller en gemakkelijker geld kan opnemen. | Contactloos pinnen. | RFID sensor coderen, RFID implementeren in de pinautomaat, contactloze bankpas connecten aan een gebruiker | Pinautomaat accepteert contactloze kaarten. |  5
| 15 | Als eindgebruiker wil ik een pin bon kunnen ontvangen als bewijs van mijn transactie, zodat ik een overzicht heb van mijn opname. | Transactiebon beschikbaar. | Optie om bon te printen. | Gebruiker ontvangt een bon indien gewenst. |  8
| 16 | Als eindgebruiker wil ik dat mijn pin bon de transactiedatum/tijd, het bedrag, de laatste vier cijfers van mijn rekeningnummer en het pinautomaat-ID bevat, zodat ik mijn transactie kan verifiëren. | Gedetailleerde transactiebon. | Bon bevat datum, tijd, bedrag, laatste 4 IBAN-cijfers en automaat-ID. | Bon bevat essentiële details. |  7
| 17 | Als eindgebruiker wil ik dat de pinautomaat automatisch teruggaat naar het beginscherm bij fouten, zodat de machine niet vastloopt en ik een nieuwe poging kan doen. | Automatische reset bij fouten. | Systeem keert terug naar startscherm bij een system error. | Automaat blijft bruikbaar na een fout. |  5
| 18 | Als bank wil ik dat de eindgebruiker minimaal 20 euro per transactie kan opnemen, zodat er minder transacties plaatsvinden en dus de automaat minder vaak bijgevuld hoeft te worden. | Minimumbedrag per opname. | Opnames vanaf minimaal 20 euro toegestaan. | Gebruiker kan geen bedragen onder 20 euro opnemen. |  4
| 19 | Als eindgebruiker wil ik een foutmelding krijgen als mijn saldo te laag is, zodat ik weet dat de transactie niet kan doorgaan. | Saldo-controle voor opname. | Foutmelding bij onvoldoende saldo. | Transactie wordt geweigerd bij onvoldoende saldo. |  6
| 20 | Als bank wil ik dat de pinautomaat kan communiceren met de NOOB-server, zodat transacties correct verwerkt worden. | Verbinding met NOOB-server. | NOOB server onderzoeken, NOOB server connecten aan de database, NOOB server communicatie met andere banken. | Transacties worden correct verwerkt via NOOB-server. |  8
| 21 | Als bank wil ik dat de database van de pinautomaat eindgebruiker gegevens zoals naam, e-mail, IBAN en saldo bevat, zodat eindgebruiker beheer en transacties goed werken. | Pinautomaat-database. | Keuze database onderzoeken, database laten werken met de NOOB server, tabellen en kolommen toevoegen in de database. | Gegevens correct opgeslagen en beheerd. |  7
| 22  | Als bank wil ik dat de componenten van mijn pinautomaat langdurig mee gaan en betrouwbaar zijn, zodat de automaat correct kan werken op een snelle en veilige manier | Er wordt onderzoek gedaan naar de componenten. | Er wordt een onderzoeksverslag gemaakt voor alle benodigde componenten van de pinautomaat. | De optimale hardware voor de pinautomaat is gekozen op basis van de conclusie van het onderzoeksverslag. |  6

#### Should Haves

---

| #  | User Story | Requirements | Taken | Acceptatiecriteria |
|----|-----------|--------------|-------|---------------------|
| 22 | Als eindgebruiker wil ik de pinautomaat in zowel Nederlands als Engels kunnen gebruiken, zodat ik de instructies begrijp. | Meertalige ondersteuning. | Nederlands en Engels beschikbaar. | Gebruiker kan taal kiezen. |
| 23 | Als bank wil ik dat de pinautomaat voldoet aan de Nederlandse standaarden, zodat deze veilig en wettelijk goedgekeurd is. | Wettelijke en veiligheidsnormen. | Automaat voldoet aan regelgeving. | Pinautomaat voldoet aan NL-wetgeving. |
| 24 | Als eindgebruiker wil ik een gebruiksvriendelijke interface, zodat ik eenvoudig en intuïtief geld kan opnemen. | Intuïtieve bediening. | Gebruiksvriendelijke UI. | Duidelijke navigatie en knoppen. |
| 25 | Als eindgebruiker wil ik naar een vorig scherm kunnen teruggaan, zodat ik een fout kan corrigeren zonder de hele transactie opnieuw te starten. | Navigatiemogelijkheid. | "Vorige" knop aanwezig. | Gebruiker kan terug zonder alles opnieuw in te voeren. |
| 26 | Als blinde eindgebruiker wil ik de pinautomaat met braille of audiofeedback kunnen gebruiken, zodat ik zelfstandig geld kan opnemen. | Toegankelijkheid voor visueel beperkten. | Braille en/of audio-optie. | Gebruiker kan zelfstandig navigeren. |
| 27 | Als eindgebruiker wil ik dat de pinautomaat goed verlicht is, zodat ik me veilig voel tijdens het pinnen. | Verlichting aanwezig. | Goed zichtbare interface. | Automaat heeft verlichting voor zichtbaarheid en veiligheid. |
| 28 | Als eindgebruiker wil ik een melding krijgen als ik te lang niets doe, zodat ik weet dat mijn sessie wordt beëindigd. | Inactiviteitstimer. | Waarschuwing voor beëindiging sessie. | Gebruiker krijgt melding bij inactiviteit. |
| 29 | Als eindgebruiker wil ik een contactnummer op het scherm zien, zodat ik in geval van storing of noodhulp kan krijgen. | Contactinformatie zichtbaar. | Noodnummer op scherm. | Gebruiker ziet een contactnummer bij problemen. |
| 30 | Als bank wil ik dat de pinautomaat stevig en niet extern toegankelijk is, zodat diefstal en vandalisme voorkomen worden. | Fysieke beveiliging. | Behuizing is robuust. | Automaat is stevig en beschermd tegen vandalisme. |
| 31 | Als bank wil ik dat er 10 cent transactiekosten per opname worden gerekend, zodat de bank verdient aan de investering van de pinautomaat. | Transactiekosten. | 10 cent per opname. | Gebruiker betaalt 10 cent per transactie. |

#### Could Haves

---

| #  | User Story | Requirements | Taken | Acceptatiecriteria |
|----|-----------|--------------|-------|---------------------|
| 32 | Als bank wil ik een notificatie krijgen wanneer de pinautomaat bijgevuld moet worden, zodat deze altijd operationeel blijft. | Automatische meldingen. | Bank ontvangt bijvulmelding. | Notificatie wordt verzonden bij lage kasvoorraad. |
| 33 | Als kleurenblinde eindgebruiker wil ik dat de pinautomaat visueel toegankelijk is, zodat ik zonder problemen de interface kan gebruiken. | Kleurenblindvriendelijke UI. | Contrasten en kleurinstellingen. | Interface is toegankelijk voor kleurenblinden. |
| 34 | Als bank wil ik dat de pinautomaat een camera heeft, zodat ik verdachte activiteiten kan registreren voor veiligheidsdoeleinden. | Beveiligingscamera. | Camera in pinautomaat. | Opnames worden opgeslagen voor veiligheid. |
| 35 | Als eindgebruiker wil ik dat de pinautomaat een touchscreen heeft, zodat de bediening moderner en gemakkelijker is. | Touchscreen interface. | Pinautomaat heeft touchscreen. | Gebruiker kan alles via touchscreen bedienen. |

#### Won't Haves

---

| #  | User Story | Requirements | Taken | Acceptatiecriteria |
|----|-----------|--------------|-------|---------------------|
| 36 | Als bank wil ik niet dat er geld gestort kan worden bij de pinautomaat, om de productiekosten te beperken. | Geen stortingsmogelijkheid. | Geen ondersteuning voor stortingen. | Automaat accepteert alleen opnames, geen stortingen. |

### Changelog

---

| Datum      | Versie | Omschrijving                                         | Auteur | Opmerkingen |
| ---------- | ------ | ---------------------------------------------------- | ------ | ----------- |
| 20-02-2025 | v1     | Eerste versie                                        | Scott  |             |
| 20-02-2025 | v1.1   | Toevoeging requirements, taken en acceptatiecriteria | Arda   |             |
| 20-02-2025 | v1.2   | Kleine aanpassingen | Dennis   |             |
| 13-03-2025 | v2.0   | Aanpassingen aan taken en toevoeging van Story Points tabel | Scott   |             |

