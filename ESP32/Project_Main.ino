/***********************************************************************
 * Project_Main.ino
 *
 * SafeHaven – ESP32 Secure Telemetry Publisher
 ***********************************************************************/

#include "secrets.h"
#include "SensorLogic.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <time.h>

// Secure TLS socket
WiFiClientSecure net;

// MQTT client layered on top of TLS socket
PubSubClient mqtt(net);

// Convert raw 12-bit ADC value (0–4095) to percentage (0–100)
float toPercent(int raw) {
    return (raw / 4095.0f) * 100.0f;
}

/***********************************************************************
 * syncTime()
 ***********************************************************************/
void syncTime() {

    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    Serial.print("Syncing time");

    time_t now = time(nullptr);

    while (now < 1700000000) {
        Serial.print(".");
        delay(500);
        now = time(nullptr);
    }

    Serial.println("\nTime Synced!");
}

/***********************************************************************
 * connectWiFi()
 ***********************************************************************/
void connectWiFi() {

    if (WiFi.status() == WL_CONNECTED) return;

    static bool started = false;

    if (!started) {
        started = true;

        WiFi.mode(WIFI_STA);
        WiFi.setSleep(false);
        WiFi.setAutoReconnect(true);
        WiFi.persistent(false);
        WiFi.begin(WIFI_SSID, WIFI_PASS);

        Serial.print("WiFi connecting");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi OK");
    } else {
        Serial.print(".");
    }
}

/***********************************************************************
 * connectMQTT()
 ***********************************************************************/
void connectMQTT() {

    if (WiFi.status() != WL_CONNECTED) return;

    mqtt.setServer(AWS_ENDPOINT, AWS_PORT);
    mqtt.setKeepAlive(60);

    Serial.print("MQTT connecting...");

    if (mqtt.connect(CLIENT_ID)) {
        Serial.println("OK");
    } else {
        Serial.print("FAIL, rc=");
        Serial.println(mqtt.state());
    }
}

/***********************************************************************
 * setup()
 ***********************************************************************/
void setup() {

    Serial.begin(115200);
    delay(200);

    initSensors();

    // WiFi Initial Connection
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.setAutoReconnect(true);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("WiFi connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println("\nWiFi OK");

    // Time Sync
    syncTime();

    // Load TLS Certificates
    net.setCACert(AWS_ROOT_CA);
    net.setCertificate(DEVICE_CERT);
    net.setPrivateKey(PRIVATE_KEY);

    net.setHandshakeTimeout(30);
    net.setTimeout(30);

    mqtt.setBufferSize(512);

    connectMQTT();
}

/***********************************************************************
 * loop()
 ***********************************************************************/
void loop() {

    Telemetry currentData = readSensors();

    // WiFi Reconnect
    if (WiFi.status() != WL_CONNECTED) {
        connectWiFi();
        return;
    }

    // MQTT Reconnect (Non-blocking)
    static uint32_t lastTry = 0;

    if (!mqtt.connected()) {
        if (millis() - lastTry > 3000) {
            lastTry = millis();
            connectMQTT();
        }
        return;
    }

    mqtt.loop();

    // Publish Every 2 Seconds
    static uint32_t lastPub = 0;

    if (millis() - lastPub > 2000) {

        lastPub = millis();
        time_t now = time(nullptr);

        char payload[384];

        snprintf(payload, sizeof(payload),
    "{\"device\":\"cpu-01\","
    "\"door\":%d,"
    "\"motion\":%d,"
    "\"tempC\":%.2f,"
    "\"water_raw\":%d,"
    "\"water_pct\":%.1f,"
    "\"pressure_raw\":%d,"
    "\"pressure_pct\":%.1f,"
    "\"states\":%s,"
    "\"ts\":%ld}",
    currentData.door,
    currentData.motion,
    currentData.temp,
    currentData.water,
    toPercent(currentData.water),
    currentData.pressure,
    toPercent(currentData.pressure),
    currentData.stateStr.c_str(),
    (long)now
);

        bool ok = mqtt.publish(TOPIC, payload);

        Serial.print(ok ? "PUB OK: " : "PUB FAIL: ");
        Serial.println(payload);
    }
}
