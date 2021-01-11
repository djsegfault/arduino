#include <heltec.h>
#include <DHTesp.h>
#include <PubSubClient.h>
#include <TaskManager.h>
#include <WiFi.h>

// Remember to copy config_TEMPLATE.h to config.h and update the values
#include "config.h"

// Constants for display locations: character width in dots and height in dots
const int CW = 5;
const int CH = 9;

// Globals
DHTesp dht;
WiFiClient espClient;
PubSubClient mqttClient(espClient);
double temperature_f = 0;
double humidity = 0;
char buffer[81];

void mqttConnect()
{
    // Loop until we're reconnected
    while (!mqttClient.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (mqttClient.connect(MQTT_CLIENT_NAME, MQTT_USERNAME, MQTT_PASSWORD))
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
    Serial.println(WIFI_SSID);
    WiFi.disconnect();
    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.print("IP number assigned by DHCP is ");
    Serial.println(WiFi.localIP());
}

void setupDHTTask()
{
    // Read dht every 1000[ms] and repeat forever
    Tasks.interval(10000, [] {
        // Reading temperature for humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
        TempAndHumidity dhtValues = dht.getTempAndHumidity();
        // Check if any reads failed and exit early (to try again).
        if (dht.getStatus() != 0)
        {
            Serial.println("DHT11 error status: " + String(dht.getStatusString()));
            return false;
        }

        temperature_f = (1.8 * dhtValues.temperature) + 32.0;
        humidity = dhtValues.humidity;
        Serial.println(temperature_f);
        Serial.println(humidity);

        // Send to MQTT
        mqttConnect();
        sprintf(buffer, "%2.2f", temperature_f);
        mqttClient.publish("sensors/basement/temperature_f", buffer);

        sprintf(buffer, "%2.2f", humidity);
        mqttClient.publish("sensors/basement/humidity", buffer);
        updateDisplay();

    });
}

void setupMQTT()
{
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
    mqttClient.setCallback(mqttSubHandler);
    mqttConnect();
}

void updateDisplay()
{
    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "IP");
    sprintf(buffer, "IP %s", WiFi.localIP().toString().c_str());
    Heltec.display->drawString(0, CH*1, MQTT_CLIENT_NAME);
    Heltec.display->drawString(0, 0, buffer);
    sprintf(buffer, "T %2.2f  H %2.2f", temperature_f, humidity);
    Heltec.display->drawString(0, CH*3, buffer);
    sprintf(buffer, "MS %ld", millis());
    Heltec.display->drawString(0, CH*4, buffer);
    Heltec.display->display();
}

void setup()
{
    // Serial setup
    Serial.begin(115200);
    delay(2000);

    // Display setup
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

    // Sensor setup
    dht.setup(DHT_DATA_PIN, DHTesp::DHT11);
    Serial.println("DHT initiated");

    setupWiFi();
    setupMQTT();
    setupDHTTask();
}

void loop()
{
    Tasks.update();
}
