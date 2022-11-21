#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "<WIFI-NAME>";
const char* password = "<PASSWORD>";

// MQTT
const char *mqtt_broker = "broker.hivemq.com";
const int mqtt_port = 1883;

const char *topic = "esp8266/mack";

const char *client_id = "nodemcu-tiengo121987";
const char *mqtt_username = "gustavotiengo";
const char *mqtt_password = "public";

// WiFi Client
WiFiClient wifiClient;

// MQTT Client
PubSubClient client(wifiClient);


// Variaveis globais para controlar push notifications e buzzer
bool pushNotificationActive = false;
bool buzzActive = false;

void setup() {
  // LEDs vermelhos
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);

  // Buzzer 1 (mais proximo aos leds)
  pinMode(D1, OUTPUT);
  
  // Buzzer 2 (mais distante dos leds)
  pinMode(D2, OUTPUT);

  // Sensor de presenca
  pinMode(D4, INPUT);
  digitalRead(D4);

  Serial.begin(115200);

  // Conexao WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {    
    delay(1000);
  }

  // Conexao MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    if (client.connect(client_id, mqtt_username, mqtt_password)) {
        client.subscribe(topic);
    } else {
        delay(1000);
    }
  }

  delay(500);
}

void loop() {
  int sinalSensorMovimento = digitalRead(D4);

  if (sinalSensorMovimento == HIGH) {
    client.publish(topic, "1");
    buzzAndLights();
    delay(2000);
    client.publish(topic, "0");

    if (pushNotificationActive) {
      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient httpClient; 
        httpClient.begin(wifiClient, "http://api.pushingbox.com/pushingbox?devid=v71BA0E477C0365B");
        int httpCode = httpClient.GET();

        if (httpCode > 0) {
          httpClient.end();
        }
      }
    }

  } else {
    noTone(D1);
    noTone(D2);
  }

   if (!client.connected()) {
    reconnect();
  }

   client.loop();
}

void buzzAndLights() {
  digitalWrite(D0, HIGH);
  buzz();
  digitalWrite(D0, LOW);
  buzz();
  digitalWrite(D0, HIGH);
  buzz();
  digitalWrite(D0, LOW);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(client_id, mqtt_username, mqtt_password)) {
      client.subscribe(topic);
    } else {
      delay(1000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
    String message;

    // convert *byte to string
    for (int i = 0; i < length; i++) {
        message = message + (char) payload[i];  
    }

    if (message == "pushon") { 
      pushNotificationActive = true;
    } 
    
    if (message == "pushoff") {
      pushNotificationActive = false;
    }     

    if (message == "buzzon") { 
      buzzActive = true;
    } 
    
    if (message == "buzzoff") {
      buzzActive = false;
    }    

    if (message == "ledon") { 
      digitalWrite(D0, HIGH); 
    } 
    
    if (message == "ledoff") {
      digitalWrite(D0, LOW); 
    }     
}

void buzz() {
  int tempo = 150;
  if (buzzActive) {
    tone(D1, 220, tempo);
    tone(D2, 220, tempo);  
    delay(tempo);
    tone(D1, 350, tempo * 2);  
    tone(D2, 350, tempo * 2);  
    delay(tempo * 2);
  } else {
    delay(tempo * 3);    
  }
}