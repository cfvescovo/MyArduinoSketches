#include <WiFiEsp.h>
int SENSOR_PIN = A0;
char ssid[] = "Wi-Fi SSID";
char pass[] = "Wi-Fi password";
int status = WL_IDLE_STATUS;
char server[] = "server ip";
int port = 10020;
int REFRESH_RATE = 10000;
WiFiEspClient client;
String rt = "\r\n";
String txt = "Sensor value: ";

void setup()
{
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
  Serial1.begin(115200);
  WiFi.init(&Serial1);
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true)
      ;
  }
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("You're connected to the network");
  Serial.println();
  Serial.println("Starting connection to server...");
  if (client.connect(server, port))
  {
    Serial.println("Connected to server");
    client.write("OK\r\n");
  }
}

void loop()
{
  int value = analogRead(SENSOR_PIN);
  String value_str = String(value);
  String value_to_send = txt + value_str + rt;
  client.print(value_to_send);
  delay(REFRESH_RATE);
}
