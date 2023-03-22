/*
  bot.ino - Thijs Dregmans (1024272)
  Last edited: 21-03-2023
*/


const int   daylightOffset_sec = 3600;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;

#include "secret.h"
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "DHT.h"
#include "time.h"
// Pin the DHT is connected to
#define DHTPIN 2
// Type of sensor
#define DHTTYPE DHT11

// Init sensor
DHT dht(DHTPIN, DHTTYPE);

// Init wifi clients
WiFiClientSecure espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

#define ESPTYPE ESP32


// coppied from NPT libary provided by Client
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
  String RecievedText;
  for (int i = 0; i < length; i++) {
    RecievedText += (char)payload[i];
  }
  Serial.println(RecievedText);

  if (RecievedText == String(MQTT_CLIENT_ID)+": temperatuur") {
    delay(2000);
    float t = dht.readTemperature();
    Serial.print("Temperatuur is ");
    Serial.println(t);
    client.publish(MQTT_TOPIC, String(t).c_str());
  }
  else if (RecievedText == String(MQTT_CLIENT_ID)+": vochtigheid") {
    delay(2000);
    float h = dht.readHumidity();
    Serial.print("Luchtvochtigheid is ");
    Serial.println(h);
    client.publish(MQTT_TOPIC, String(h).c_str());
  }
  else if (RecievedText == String(MQTT_CLIENT_ID)+": led:aan") {
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish(MQTT_TOPIC, "LED is aan");
  }
  else if (RecievedText == String(MQTT_CLIENT_ID)+": led:uit") {
    digitalWrite(LED_BUILTIN, LOW);
    client.publish(MQTT_TOPIC, "LED is uit");
  }

  //  // Switch on the LED if an 1 was received as first character
  //  if ((char)payload[0] == '1') {
  //    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  //    // but actually the LED is on; this is because
  //    // it is active low on the ESP-01)
  //  } else {
  //    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  //  }

}

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

  // connect certificate !!!!!!!!!!
  espClient.setCACert(local_root_ca);

  // BS
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connecting...");
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
      Serial.println("connected");
      
      // Once connected, publish an announcement...
      String message = "connected with MQTT broker.";
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
  dht.begin();
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);


  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  //  unsigned long now = millis();
  //  if (now - lastMsg > 2000) {
  //    lastMsg = now;
  //    ++value;
  //    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
  //    Serial.print("Publish message: ");
  //    Serial.println(msg);
  //    client.publish("outTopic", msg);
  //  }
}
