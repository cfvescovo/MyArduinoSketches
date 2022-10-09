/*
  WiFi Web Server LED controller

 A simple web server that lets you blink an LED via the web.

 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off
 */

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Wi-Fi SSID";
char pass[] = "Wi-Fi password";
int keyIndex = 0;  // WEP-specific parameter

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
    Serial.begin(9600);
    pinMode(9, OUTPUT);  // set the LED pin mode

    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        while (true)
            ;
    }

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Network named: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        // wait 10 seconds for connection:
        delay(10000);
    }
    server.begin();
    printWifiStatus();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("new client");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        client.print(
                            "Click <a href=\"/H\">here</a> turn the LED on pin "
                            "9 on<br>");
                        client.print(
                            "Click <a href=\"/L\">here</a> turn the LED on pin "
                            "9 off<br>");
                        client.println();
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(9, HIGH);
                }
                if (currentLine.endsWith("GET /L")) {
                    digitalWrite(9, LOW);
                }
            }
        }
        client.stop();
        Serial.println("client disonnected");
    }
}

void printWifiStatus() {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");

    Serial.print("To see this page in action, open a browser to http://");
    Serial.println(ip);
}