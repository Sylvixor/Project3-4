# Onderzoeksverslagen

Arda Keskin - 1096673

Scott van der Heijden - 1103349

Dennis Zejnilovic - 1098617

Julius De Maesschalck - 1101422

## Inhoudsopgave

- [Onderzoeksverslagen](#onderzoeksverslagen)
  - [Inhoudsopgave](#inhoudsopgave)
  - [Inleiding](#inleiding)
  - [Sensoren](#sensoren)
    - [Infrarood sensor](#infrarood-sensor)
    - [Aanvullende sensoren](#aanvullende-sensoren)
    - [Tussenconclusie](#tussenconclusie)
  - [Actuatoren](#actuatoren)
  - [Micro-/Macro controllers](#micro-macro-controllers)
  - [Bonprinter](#bonprinter)
  - [Interface](#interface)
  - [Conclusie](#conclusie)

## Inleiding

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

## Sensoren

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

## Actuatoren

## Micro-/Macro controllers

## Bonprinter

## Interface

## Conclusie