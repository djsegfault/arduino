#include <heltec.h>
#include <DHTesp.h>
#include <PubSubClient.h>
#include <TaskManager.h>
#include <WiFi.h>

/**
 * config.sh should define:
 * const char* wifiSSID = "...";
 * const char* wifiPassword = "....."
 **/
#include "config.h"

// Constants
const int DHT_DATA_PIN = 17;

// Globals
DHTesp dht;
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void mqttConnect()
{
    // Loop until we're reconnected
    while (!mqttClient.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (mqttClient.connect(mqttClientName, mqttUser, mqttPassword))
        {
            Serial.println("MQTT connected");
            // Once connected, publish an announcement...
            //mqttClient.publish("sensors/basement/connected", "1");
            // ... and resubscribe
            //mqttClient.subscribe("sensors/basement/led");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void mqttSubHandler(char *topic, byte *message, unsigned int length)
{
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    // Act on message here
}

void setupWiFi()
{
    Serial.print("Connecting to ");
    Serial.println(wifiSSID);
    WiFi.disconnect();
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(wifiSSID, wifiPassword);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.print("IP number assigned by DHCP is ");
    Serial.println(WiFi.localIP());
}

void setupMQTT()
{
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCallback(mqttSubHandler);
    mqttConnect();
}

void setup()
{
    // Serial setup
    Serial.begin(115200);
    delay(2000);

    // Sensor setup
    dht.setup(DHT_DATA_PIN, DHTesp::DHT11);
    Serial.println("DHT initiated");

    setupWiFi();
    setupMQTT();

    // Read dht every 1000[ms] and repeat forever
    Tasks.interval(10000, [] {
        char buffer[8];
        // Reading temperature for humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
        TempAndHumidity newValues = dht.getTempAndHumidity();
        // Check if any reads failed and exit early (to try again).
        if (dht.getStatus() != 0)
        {
            Serial.println("DHT11 error status: " + String(dht.getStatusString()));
            return false;
        }

        double temperature_f = (1.8 * newValues.temperature) + 32.0;
        double humidity = newValues.humidity;
        Serial.println(temperature_f);
        Serial.println(humidity);

        // Send to MQTT
        mqttConnect();
        sprintf(buffer,"%2.2f", temperature_f);
        mqttClient.publish("sensors/basement/temperature_f", buffer);
        Serial.print("Sent T ");
        Serial.println(buffer);
        sprintf(buffer,"%2.2f", humidity);
        mqttClient.publish("sensors/basement/humidity", buffer);
        Serial.print("Sent H ");
        Serial.println(buffer);

        Serial.print("interval forever task: now = ");
        Serial.println(millis());
    });

    Serial.print("task start: now = ");
    Serial.println(millis());

    if (!mqttClient.connected()) {
        Serial.println("End of setup, NOT connected");
    } else {
        Serial.println("End of setup, still connected");
    }
}

void loop()
{
    Tasks.update();
}
