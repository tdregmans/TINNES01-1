# TINNES01-1
Netwerken &amp; Security (vervolg)

## Inleiding
Er zijn een aantal interessante ontwikkelingen op het gebied van netwerken: Virtuele systemen winnen terrein,
met name de online virtual machines, maar ook het Internet of Things (IoT) is hard in opkomst, al dan niet in
combinatie met cloud computing. Alleen: hoe verbind ik die aan elkaar? Hoe scheid ik mijn zakelijke netwerken
intern, en hoe zorg ik ervoor dat deze systemen veilig zijn?
In deze cursus ga je een verbredende (en soms verdiepende) slag maken op netwerken die je het eerste jaar
hebt gehad en de security rules die je geleerd hebt bij Security Basis hier toepassen.
Voornamelijk VLAN’s, VPN’s, IoT, cloud-oplossingen en de belangrijkste bijbehorende veiligheidsaspecten
zouden je klaar moeten stomen om te beginnen in dit interessante vakgebied.

## Goals

1. Je weet hoe je je eigen netwerken aan kan sluiten aan cloudnetwerken
2. Je kan uitleggen hoe VLAN’s werken, en je begrijpt het belang van
VLAN’s, het scheiden van netwerken en de beveiliging van deze
netwerken.
3. Je kan uitleggen wat verschillende karakteristieken zijn van WiFi, en je
kan beschrijven hoe je WiFi veiliger in kan zetten.
4. Je kan IoT en haar security issues duiden in de huidige ontwikkelingen
voor de toekomst
5. Je kan simpele elektronica op een veilige manier ontsluiten via een
cloudplatform

## TINNES01 - Opdracht 1

Thijs Dregmans (1024272) - 07-03-2023

### De opdracht

De opdracht is om een MQTT chat app op te zetten met behulp van twee Docker containers. Er zijn twee containers:

- De Message Broker
- De Client

De Client subscribes met MQTT op het topic 'chat' en publishes berichten. De Message Broker ontvangt de berichten en stuurt die door naar de subscribers. Op die manier kunnen meerdere Clients berichten naar elkaar sturen.

### Set up

Een aantal zaken zijn inbegrepen in de inleverset:
- Een Netwerk diagram
- Deze `README.md` file
- De `docker-compose.yml` file
- De `nginx.conf` file
- De `mosquitto.conf` file
- De `index.html` met het embedded Javascript
- Het certificaat
- De Private key

Om het system werkende te krijgen moet men de volgende stappen doorlopen:
1. Installeer Docker Desktop
2. Zet de `docker-compose.yml` file in een map
3. Gebruik het `docker compose up` commando in de Command Prompt
4. Zet de inhoud van deze map in de eerder gekozen map
5. Herstart de Docker containers

6. Open `https://localhost`

Hier zie je nu de chat app. De app werkt met Self-Signed Certificates (HTTPS).

## TINNES01 - Opdracht 2

Thijs Dregmans (1024272) - 21-03-2023

### De opdracht

Het bedrijf voor wie je aan het werk bent, is zeer te vreden met de chat applicatie die je hebt gebouwd. Het is nu enkele maanden later en het bedrijf is dankzij jouw applicatie enorm gegroeid in waarde. Er wordt geschat dat het bedrijf nu een waarde heeft van ruim € 500.000,-. Het bedrijf heeft jouw voor de applicatie rijkelijk betaald en is zich nu aan het verdiepen in de wondere wereld van IoT. Ze willen graag eigen hardware ontwikkelen en hebben contracten gesloten met Espressif (het bedrijf achter de ESP32/ESP8266 Microcontrollers ) en met Arduino. Dankzij deze contracten mag het bedrijf winst maken door gebruik maken van de producten van deze bedrijven. Het bedrijf heeft echter jouw kennis nodig om een prototype te maken met een ESP32 of ESP8266. Hierop moet code draaien dat is geschreven in Arduino. Het bedrijf wil graag dat de hardware inhaakt op de geweldige chat applicatie.

> Maak van een ESP32 of ESP8266 microcontroller een chatbot. Deze chatbot moet de temperatuur en vochtigheid sturen in de chat wanneer daar om gevraagd wordt door een chat gebruiker. Daarnaast moet een simpele LED aan en uit gezet kunnen worden.

### Set up en gebruik

Een aantal zaken zijn inbegrepen in de inleverset:
- Een Netwerk diagram
- Deze `README.md` file
- De bestanden die nodig zijn voor het opzetten van opdracht 1 i.e. de chatapp.
- De `bot.cpp` file
- De `secret.h` file

Om opdracht 2 werkend te krijgen, moet `bot.cpp` in combinatie met `secret.h` geupload worden op een ESP32. Het makkelijkste is om hiervoor de Arduino IDE te gebruiken. Ik heb hiervoor de volgende instellingen gebruikt:
- Board: "DOIT ESP32 DEVKIT V1"
- Upload Speed: "115200"
- Flash Frequency: "80MHz"
- Core Debug Level: "Geen"

`bot.cpp` en `secret.h` moeten in dezelfde map staan wanneer de code wordt geupload naar een ESP32.

Als in `secret.h` de SSID en password zijn aangepast, dan verbind de ESP automatische met de server `netwerkenbasis.com`.

De chatbot is nu in gebruik.

#### Gebruik

Als de chatbot eenmaal de verbonden is, dan wordt dat zichtbaar in de chatapp. De bot zal een bericht sturen: `BOT-1024272 connected with MQTT broker.`

Er zijn vervolgens een aantal commando's mogelijk:
- Om de temperatuur te meten, typt u `BOT-1024272: temperatuur`. De bot zal vervolgens na 2 seconden de gemeten temperatuur terugsturen. Bijvoorbeeld: `Temperatuur is 25.20ºC`. Het meten duurt 2 seconden door het gebruik van de DHT11; een zeer slome sensor.
- Om de luchtvochtigheid te meten, typt u `BOT-1024272: vochtigheid`. De bot zal vervolgens na 2 seconden de gemeten luchtvochtigheid terugsturen. Bijvoorbeeld: `Luchtvochtigheid is 50%`. Het meten duurt 2 seconden door het gebruik van de DHT11; een zeer slome sensor.
- Om de LED aan te zetten, typt u `BOT-1024272: led:aan`. De bot zal vervolgens de interne LED aanzetten en een bevestiging terugsturen: `LED is aan`.
- Om de LED uit te zetten, typt u `BOT-1024272: led:uit`. De bot zal vervolgens de interne LED uitzetten en een bevestiging terugsturen: `LED is uit`.

De bot gebruikt het gegeven topic `chat/message`. Dit kan eenvoudig worden aangepast in `secret.h`.
