#include <heltec.h>
#include <DHTesp.h>
#include <PubSubClient.h>
#include <TaskManager.h>
#include <WiFi.h>

#include "config.h"
/**
 * config.sh should define:
 * const char* wifiSSID = "...";
 * const char* wifiPassword = "....."
 **/

// Constants
const int DHT_DATA_PIN = 17;

// Globals
DHTesp dht;

void setup()
{
    // Serial setup
    Serial.begin(115200);
    delay(2000);

    // Sensor setup
    dht.setup(DHT_DATA_PIN, DHTesp::DHT11);
    Serial.println("DHT initiated");

    // Wifi setup
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

    // Read dht every 1000[ms] and repeat forever
    Tasks.interval(5000, [] {
        // Reading temperature for humidity takes about 250 milliseconds!
        // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
        TempAndHumidity newValues = dht.getTempAndHumidity();
        // Check if any reads failed and exit early (to try again).
        if (dht.getStatus() != 0)
        {
            Serial.println("DHT11 error status: " + String(dht.getStatusString()));
            return false;
        }

        Serial.println((1.8 * newValues.temperature) + 32);
        Serial.println(newValues.humidity);

        Serial.print("interval forever task: now = ");
        Serial.println(millis());
    });

    Serial.print("task start: now = ");
    Serial.println(millis());
}

void loop()
{
    Tasks.update();
}
