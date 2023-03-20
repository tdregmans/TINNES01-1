/*
  bot.ino

  version 1
    
  CMI-TI 22 TINNES01
  Student: Thijs Dregmans (1024272)
  Netwerken & Security (vervolg) opdracht 2
  Last edited: 20-03-2023
 
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include "secret.h"

#include "DHT.h"

#define DHTPIN 13     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);


WiFiClient wifiClient;

PubSubClient client(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String command;
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    command += (char)payload[i];
  }
  Serial.println();

  // react to command
  if(command == "temperature") {
    delay(2000);
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    // Read temperature as Celsius
    float t = dht.readTemperature();
    if (isnan(t)) {
      client.publish("chat/message","sensor.");
    }
    else {
      client.publish("chat/message","sensor.");
    }
  }
  // react to command
  else if(command == "humidity") {
    delay(2000);
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    if (isnan(h)) {
      client.publish("chat/message","sensor.");
    }
    else {
      client.publish("chat/message","sensor.");
    }
  }
  // react to command
  else if(command == "LED on") {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  // react to command
  else if(command == "LED off") {
      digitalWrite(LED_BUILTIN, LOW);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_HOST)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("chat/message","sensor.");
      // ... and resubscribe
      client.subscribe("chat/message");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);

  // Allow the hardware to sort itself out
  delay(1500);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
