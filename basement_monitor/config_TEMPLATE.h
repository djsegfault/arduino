// rename to config.h
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";
const char* MQTT_HOST = "";
const char* MQTT_CLIENT_NAME = "Demo1";
const char* MQTT_USERNAME = "";
const char* MQTT_PASSWORD = "";
const char* TOPIC_CONNECTED="sensors/demo/connected";
const char* TOPIC_LED="sensors/demo/led";
const char* TOPIC_TEMP="sensors/demo/temperature_f";
const char* TOPIC_HUM="sensors/demo/humidity";
const char* TOPIC_LIGHT_LEVEL="sensors/demo/light";
const char* TOPIC_LIGHT_ON_TIME="sensors/demo/light_on_time";
const int   MQTT_PORT = 1883;
const int   DHT_DATA_PIN = 17;
const int   LDR_PIN = 2;
const int   LED_PIN=25;
const int   DHT_INTERVAL=10000;
const int   LDR_INTERVAL=15000;
const int   MQTT_INTERVAL=500;

#define DHTTYPE DHT22