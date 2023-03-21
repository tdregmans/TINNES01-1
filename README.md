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
4. Zet de inhoud van de map in de eerder gekozen map
5. Herstart de Docker containers

6. Open `https://localhost`

Hier zie je nu de chat app. De app werkt met Self-Signed Certificates (HTTPS).

## TINNES01 - Opdracht 2

Thijs Dregmans (1024272) - 21-03-2023


