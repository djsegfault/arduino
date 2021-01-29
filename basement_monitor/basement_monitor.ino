/**
 * basement_monitor - IoT demo by David Kramer
 * See https://github.com/djsegfault/arduino/tree/master/basement_monitor
 * See LICENSE
 * See README.md
 **/

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
char buffer[81];
double temperature_f = 0;
double humidity = 0;
int lightLevel = 0;
long lightOnSince = 0;

boolean ledLit = false;

void mqttConnect()
{
    // Loop until we're reconnected
    while (!mqttClient.connected())
    {
        Heltec.display->clear();
        Heltec.display->drawString(0, 0, "Connecting to MQTT");
        sprintf(buffer, "Status=%d", mqttClient.state());
        Heltec.display->drawString(0, CH * 2, buffer);
        Heltec.display->display();

        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (mqttClient.connect(MQTT_CLIENT_NAME, MQTT_USERNAME, MQTT_PASSWORD))
        {
            Serial.println("MQTT connected");
            mqttClient.publish(TOPIC_CONNECTED, "1");
            boolean success = mqttClient.subscribe(TOPIC_LED);
            Serial.print("Subscribe returned ");
            Serial.println(success);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            Heltec.display->clear();
            Heltec.display->display();
            delay(5000);
        }
    }
}

void mqttCallback(char *topic, byte *message, unsigned int length)
{
    Serial.print("Message arrived on topic: '");
    Serial.print(topic);
    Serial.print("'. Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    // Act on LED message here
    if (strcmp(TOPIC_LED, topic) == 0)
    {
        if (message[0] == '1')
        {
            Serial.println("Turning LED on");
            digitalWrite(LED_PIN, HIGH);
            ledLit = true;
        }
        else
        {
            Serial.println("Turning LED off");
            digitalWrite(LED_PIN, LOW);
            ledLit = false;
        }
        updateDisplay();
    }
    else
    {
        Serial.println("Unknown topic");
    }
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
        Heltec.display->clear();
        Heltec.display->drawString(0, 0, "Connecting to SSID");
        sprintf(buffer, "'%s'", WIFI_SSID);
        Heltec.display->drawString(0, CH * 2, buffer);
        Heltec.display->display();
        delay(1000);
        Serial.print(".");
        Heltec.display->clear();
        Heltec.display->display();
        delay(1000);
    }

    Serial.print("IP number assigned by DHCP is ");
    Serial.println(WiFi.localIP());
}

void setupDHTTask()
{
    Tasks.interval(DHT_INTERVAL, [] {
        // Reading temperature for humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
        TempAndHumidity dhtValues = dht.getTempAndHumidity();
        // Check if any reads failed and exit early (to try again).
        if (dht.getStatus() != 0)
        {
            Serial.println("DHT error status: " + String(dht.getStatusString()));
            return false;
        }

        temperature_f = (1.8 * dhtValues.temperature) + 32.0;
        humidity = dhtValues.humidity;
        Serial.println(temperature_f);
        Serial.println(humidity);

        // Send to MQTT
        mqttConnect();
        sprintf(buffer, "%2.2f", temperature_f);
        mqttClient.publish(TOPIC_TEMP, buffer);

        sprintf(buffer, "%2.2f", humidity);
        mqttClient.publish(TOPIC_HUM, buffer);
        updateDisplay();
    });
}

void setupLDRTask()
{
    Tasks.interval(LDR_INTERVAL, [] {
        lightLevel = analogRead(LDR_PIN);
        sprintf(buffer, "%d", lightLevel);
        Serial.print("Light ");
        Serial.println(buffer);
        mqttClient.publish(TOPIC_LIGHT_LEVEL, buffer);
        updateDisplay();

        // Update light on time, reported as seconds since on
        if (lightLevel > 100)
        {
            if (lightOnSince == 0)
            {
                // Light just turned on
                lightOnSince = millis();
                sprintf(buffer, "%d", 0);
            }
            else
            {
                sprintf(buffer, "%d", (millis() - lightOnSince) / 1000);
            }
            mqttClient.publish(TOPIC_LIGHT_ON_TIME, buffer);
        }
        else
        {
            if (lightOnSince != 0)
            {
                // Lights off, reset
                lightOnSince = 0;
            }
        }
    });
}

void setupMQTTPollTask()
{
    Tasks.interval(MQTT_INTERVAL, [] {
        mqttClient.loop();
    });
}

void setupMQTT()
{
    mqttClient.setServer(MQTT_HOST, MQTT_PORT);
    mqttClient.setCallback(mqttCallback);
    mqttConnect();
}

void updateDisplay()
{
    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "IP");
    sprintf(buffer, "IP %s", WiFi.localIP().toString().c_str());
    Heltec.display->drawString(0, CH * 1, MQTT_CLIENT_NAME);
    Heltec.display->drawString(0, 0, buffer);
    sprintf(buffer, "T %2.2f", temperature_f);
    Heltec.display->drawString(0, CH * 3, buffer);
    sprintf(buffer, "H %2.2f", humidity);
    Heltec.display->drawString(CW * 11, CH * 3, buffer);
    sprintf(buffer, "L %5d", lightLevel);
    Heltec.display->drawString(0, CH * 4, buffer);
    sprintf(buffer, "LED %1d", ledLit);
    Heltec.display->drawString(CW * 11, CH * 4, buffer);
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
    dht.setup(DHT_DATA_PIN, DHTesp::DHT22);
    Serial.println("DHT initiated");

    // LED setup
    pinMode(LED_PIN, OUTPUT);

    setupWiFi();
    setupMQTT();
    setupDHTTask();
    setupLDRTask();
    setupMQTTPollTask();
}

void loop()
{
    Tasks.update();
}
