/*
  bot.ino

  version 3.1 (final version)

  CMI-TI 22 TINNES01
  Student: Thijs Dregmans (1024272)
  Netwerken & Security (vervolg) opdracht 2
  Last edited: 29-03-2023

*/

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include "secret.h"


#include "time.h"
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 0;

#include "DHT.h"

// Sensor settings
#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  espClient.setCACert(local_root_ca);

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String command;
  for (int i = 0; i < length; i++) {
    command += (char)payload[i];
  }
  Serial.println(command);

  if (command == String(MQTT_CLIENT_ID)+": temperatuur") {
    delay(2000);
    float t = dht.readTemperature();
    Serial.print("Temperatuur is ");
    Serial.println(t);
    String message = "Temperatuur is ";
    message.concat(String(t));
    message.concat("ºC");
    client.publish(MQTT_TOPIC, message.c_str());
  }
  else if (command == String(MQTT_CLIENT_ID)+": vochtigheid") {
    delay(2000);
    float h = dht.readHumidity();
    Serial.print("Luchtvochtigheid is ");
    Serial.println(h);
    String message = "Luchtvochtigheid is ";
    message.concat(String(h));
    message.concat("%");
    client.publish(MQTT_TOPIC, message.c_str());
  }
  else if (command == String(MQTT_CLIENT_ID)+": led:aan") {
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish(MQTT_TOPIC, "LED is aan");
  }
  else if (command == String(MQTT_CLIENT_ID)+": led:uit") {
    digitalWrite(LED_BUILTIN, LOW);
    client.publish(MQTT_TOPIC, "LED is uit");
  }


}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
      Serial.println("connected");
      
      // Once connected, publish an announcement...
      String message = String(MQTT_CLIENT_ID);
      message.concat(" connected with MQTT broker.");
      client.publish(MQTT_TOPIC, message.c_str());
      
      // ... and resubscribe
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // Initialize the BUILTIN_LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  // Setup wifi and Mqtt client
  setup_wifi();
  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);


  dht.begin();
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
