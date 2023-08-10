# TINNES01
## Opdracht 1

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
4. Zet de `index.html` file in de `/public` directory
5. Zet de `nginx.conf` file <<<<<<<<<<<<<<<veranderen
6. Zet de `mosquitto.conf` file <<<<<<<<<<<<<<<veranderen
7. Zet het certificaat en privé-sleutel, in het mapje `cert`
8. Herstart de Docker containers

9. Open `https://localhost`

Hier zie je nu de chat app. De app werkt met Self-Signed Certificates (HTTPS).