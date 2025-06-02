# Onderzoeksverslag

Arda Keskin - 1096673

Scott van der Heijden - 1103349

Dennis Zejnilovic - 1098617

Julius De Maesschalck - 1101422

## Inhoudsopgave

- [Onderzoeksverslag](#onderzoeksverslag)
  - [Inhoudsopgave](#inhoudsopgave)
- [Inleiding](#inleiding)
- [Sensoren](#sensoren)
    - [Infrarood sensor](#infrarood-sensor)
    - [Aanvullende sensoren](#aanvullende-sensoren)
    - [Tussenconclusie](#tussenconclusie)
- [Actuatoren](#actuatoren)
    - [Uitgeeflade](#uitgeeflade)
    - [Bonprinter](#bonprinter)
    - [Knoppen](#knoppen)
    - [Tussenconclusie](#tussenconclusie-1)
- [Micro-/Macro controllers](#micro-macro-controllers)
    - [Keuze](#keuze)
    - [Toepassing](#toepassing)
    - [Tussenconclusie](#tussenconclusie-2)
- [Interface](#interface)
    - [Visuelen](#visuelen)
    - [Feedback](#feedback)
    - [Tussenconclusie](#tussenconclusie-3)
- [Conclusie](#conclusie)

# Inleiding

Dit onderzoeksverslag wordt opgesteld met als doel de onderzoeksvraag te
beantwoorden. Om tot een acceptabele conclusie te komen worden er
vergelijkingen getrokken tussen verschillende onderdelen die mogelijk
overwegen kunnen worden voor het project. Het project in kwestie is het
bouwen van een functioneel pinautomaat waarbij een klant geld kan
pinnen, voor dit project hoeft de klant geen geld te kunnen storten.\
In dit onderzoeksverslag wordt bepaald welke sensoren, actuatoren, micro
controllers en interfaces benodigd zijn voor de pinautomaat, daarnaast
wordt dit document gebruikt als verantwoording voor de gemaakte keuzes
betreffende zowel hardware als software gerelateerde delen van het
project. De methode voor het bepalen van de meest geschikte onderdelen
maakt gebruik van een aantal vergelijkingsvlakken afhankelijk van de
producteisen van het project. Waar nodig worden de producteisen benoemd
bij het vergelijken van onderdelen, deze producteisen zijn afkomstig uit
de wensen van de product owners en user stories.\
Dit verslag wordt verdeeld in de verschillende onderdeel categorieën,
waarbij elk deel afgesloten wordt met een tussenconclusie. Aan het einde
van het verslag worden de bevindingen besproken en wordt er een
eindconclusie getrokken. De onderzoeksvraag van dit rapport is als
volgt: Welke hardware onderdelen en software gerelateerde keuzes zijn
het best geschikt voor de pinautomaat.

# Sensoren

Bij de ontwikkeling van een kleinschalige pinautomaat speelt het gebruik 
van sensoren een cruciale rol in het waarborgen van betrouwbaarheid en 
gebruiksvriendelijkheid. Een belangrijk aandachtspunt is het correct 
detecteren van het aantal uitgegeven biljetten. Hiervoor is het essentieel 
dat de hardware betrouwbaar kan signaleren of een biljet daadwerkelijk is 
uitgegeven, en dat er niet per ongeluk meerdere biljetten tegelijk worden 
meegenomen of juist geen biljet wordt uitgegeven.

### Infrarood sensor

Voor het detecteren van biljetuitgifte wordt gebruikgemaakt van 
infraroodsensoren. Deze sensoren werken door middel van het onderbreken 
van een infraroodstraal; wanneer een biljet langs de sensor wordt 
getransporteerd, onderbreekt het de straal tijdelijk, wat door het systeem 
geïnterpreteerd wordt als een succesvolle uitgifte. Door deze methode kan 
er nauwkeurig worden vastgesteld of er exact één biljet is uitgegeven. In 
het geval dat de sensor meerdere onderbrekingen waarneemt binnen een korte 
tijdsspanne, kan het systeem concluderen dat er mogelijk meerdere 
biljetten tegelijk zijn uitgegeven, wat aanleiding kan zijn voor een 
foutmelding of het blokkeren van verdere transacties.

### Aanvullende sensoren

Als uitbreiding kunnen druksensoren of capacitieve sensoren worden 
overwogen om bijvoorbeeld de aanwezigheid van biljetten in het interne 
magazijn te controleren. Zo kan worden gedetecteerd wanneer het 
biljettenvak leeg dreigt te raken, wat tijdig onderhoud of bijvulling 
mogelijk maakt. Dit verhoogt de betrouwbaarheid en gebruikservaring van de 
pinautomaat, doordat fouten of storingen preventief gesignaleerd kunnen 
worden.

### Tussenconclusie

De keuze voor infraroodsensoren als primaire detectiemethode is passend 
voor dit project vanwege de lage kosten, eenvoudige implementatie en hoge 
betrouwbaarheid voor biljetdetectie. Door het combineren van meerdere 
sensoren kan redundantie worden ingebouwd, waardoor het systeem robuuster 
wordt tegen fouten. Eventuele aanvullende sensoren kunnen de 
functionaliteit uitbreiden en bijdragen aan een professionelere 
eindoplossing.

# Actuatoren

Binnen het project voor een kleinschalige pinautomaat worden diverse 
actuatoren gebruikt om fysieke acties uit te voeren, zoals het uitgeven 
van geld en het geven van gebruikersfeedback. Deze componenten worden 
aangestuurd via een centrale microcontroller (ESP32), die verantwoordelijk 
is voor het doorgeven van de juiste signalen op basis van 
gebruikersinteractie.

### Uitgeeflade

De uitgifte van biljetten gebeurt met behulp van een DC-motor. Deze motor 
is gekoppeld aan een mechanisme dat biljetten transporteert richting de 
uitgiftesleuf. Door de motor kort te activeren, wordt telkens één biljet 
uitgegeven. In combinatie met een sensor (bijv. infrarood) wordt 
gecontroleerd of het juiste aantal biljetten is uitgegeven.

### Bonprinter

Voor het printen van transactiebonnen wordt gebruikgemaakt van een 
thermische bonprinter. Deze printer maakt gebruik van warmtegevoelig 
papier en vereist geen inkt. De bonprinter ontvangt printopdrachten via de 
microcontroller en verwerkt deze op basis van binnengekomen gegevens. De 
keuze voor een thermisch model zorgt voor een eenvoudige, onderhoudsarme 
en snelle manier van printen.

### Knoppen

De pinautomaat is uitgerust met een reeks fysieke knoppen en een numeriek 
keypad. Deze knoppen kunnen bijvoorbeeld gebruikt worden om menuopties te 
selecteren of om een transactie te bevestigen.

### Tussenconclusie

De gekozen actuatoren vormen de uitvoerende componenten van de 
pinautomaat. Door gebruik te maken van een DC-motor, thermische 
bonprinter en fysieke invoerknoppen ontstaat een systeem dat de nodige 
fysieke handelingen kan uitvoeren om een realistische pinautomaatervaring 
te simuleren.

# Micro-/Macro controllers

Voor de besturing van de verschillende hardwarecomponenten in onze 
kleinschalige pinautomaat is gekozen voor een ESP32 microcontroller. Deze 
microcontroller fungeert als het centrale brein van het systeem en is 
verantwoordelijk voor de communicatie tussen sensoren, actuatoren en de 
gebruikersinterface.

### Keuze

De keuze voor de ESP32 is gebaseerd op meerdere voordelen die perfect 
aansluiten bij de eisen van het project:

- Wi-Fi en Bluetooth functionaliteit: De ESP32 ondersteunt standaard 
zowel Wi-Fi als Bluetooth, wat essentieel is voor de communicatie met 
de backend (zoals de NOOB-server en de bank-API). Hierdoor is er geen 
aparte netwerkmodule nodig.

- Voldoende GPIO-pinnen: Voor het aansturen van meerdere actuatoren 
(zoals een DC-motor, bonprinter en knoppen) zijn voldoende digitale 
in- en uitgangen vereist. De ESP32 biedt hierin ruime ondersteuning.

- Hoge verwerkingssnelheid: De dual-core processor van de ESP32 
maakt het mogelijk om meerdere taken tegelijk uit te voeren, zoals 
communicatie met de server én real-time verwerking van 
gebruikersinvoer.
    
- Ondersteuning voor externe libraries: Door de brede 
community-ondersteuning zijn er veel bestaande libraries beschikbaar 
voor onder andere het aansturen van schermen, bonprinters en motor 
drivers.

### Toepassing

De ESP32 wordt binnen dit project ingezet als microcontroller die direct 
de hardwarecomponenten aanstuurt. Via deze controller worden onder andere 
de volgende onderdelen bestuurd:

- De DC-motor die verantwoordelijk is voor de uitgifte van biljetten.
- De thermische bonprinter die transactiebewijzen print.
- Het keypad en de fysieke knoppen voor gebruikersinvoer.

### Tussenconclusie

De ESP32 voldoet volledig aan de eisen van dit project. Door zijn 
combinatie van snelheid, connectiviteit en veelzijdige I/O-mogelijkheden 
vormt hij een geschikte en efficiënte oplossing als centrale 
microcontroller voor de pinautomaat. Hierdoor is het niet nodig om gebruik 
te maken van een gescheiden micro- en macrocotrollerarchitectuur.

# Interface

De interface van de pinautomaat vormt de brug tussen de gebruiker en het 
onderliggende systeem. Het doel van deze interface is om gebruikers op een 
duidelijke, veilige en toegankelijke manier door het transactieproces te 
leiden. Binnen ons project wordt gekozen voor een combinatie van een 
digitale interface op een laptopscherm en fysieke invoer via knoppen en 
een keypad.

### Visuelen

De grafische gebruikersinterface (GUI) wordt weergegeven op een laptop. 
Deze laptop fungeert als scherm van de pinautomaat en toont alle nodige 
informatie aan de gebruiker, zoals:

- Welkomst- en keuzemenu’s
- Instructies tijdens de transactie
- Invoerfeedback (zoals het ingevoerde bedrag)
- Bevestigingsberichten en foutmeldingen


Door gebruik te maken van een laptop is het mogelijk om een flexibele en 
visueel aantrekkelijke interface te creëren met behulp van bestaande 
ontwikkeltools en frameworks. De GUI draait in verbinding met 
een externe server via ( vul in ).

### Feedback

Naast visuele feedback via het scherm en de knoppen, kan het systeem ook 
voorzien in:

- Auditieve feedback, zoals een korte pieptoon bij knopdrukken (via buzzer)
- Tactiele feedback, indien er knoppen met voelbare klikmechanismen worden 
gebruikt
- Printbon, als fysieke bevestiging van de transactie (zie hoofdstuk 
Bonprinter)

De combinatie van een laptop (voor visuele output) en fysieke invoer (via 
knoppen en keypad) zorgt voor een gebruikerservaring die lijkt op die van 
een echte pinautomaat. Het scheidt input en output op een natuurlijke 
manier, en maakt het systeem geschikt voor gebruik in testsituaties en 
demonstraties zonder directe afhankelijkheid van een touchscreen of 
touchscreen-software.

### Tussenconclusie

De gekozen interfaceopzet biedt een goede balans tussen 
gebruiksvriendelijkheid, functionaliteit en realisme. Door gebruik te 
maken van een laptop in combinatie met fysieke invoermogelijkheden 
ontstaat er een intuïtieve en herkenbare gebruikerservaring, die goed 
aansluit op het doel van dit project.

# Conclusie

De gekozen hardwarecomponenten sluiten goed aan op de functionele eisen en 
technische mogelijkheden van het project. De combinatie van eenvoudige, 
betrouwbare onderdelen en een krachtige centrale controller maakt het 
mogelijk om een werkende en goed te demonstreren pinautomaat te bouwen. De 
gemaakte keuzes zijn onderbouwd met zowel technische specificaties als 
projectbehoeften, waardoor dit verslag een solide basis vormt voor de 
verdere realisatie van het project.

Bedankt voor het lezen!