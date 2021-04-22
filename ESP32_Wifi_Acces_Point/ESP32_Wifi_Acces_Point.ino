#include<WiFi.h>

const char *ssid = "ESP32 Acces Point";
const char *pass = "AccesPoint";

void setup()
{
    Serial.begin(115200);
    delay(10);

    WiFi.softAP(ssid, pass);
    Serial.println("Acces Point : \"" + String(ssid) + "\" Started");
    Serial.print("IP address  : ");
    Serial.println(WiFi.softAPIP());

}

void loop()
{
    
}