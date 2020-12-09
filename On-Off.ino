#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "iZZOfGMzeAfyM4te1i0vJCJw0YXy-Zxg";
char ssid[] = "Tongsuk_2";
char pass[] = "0858936200";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(12, OUTPUT);

}
void loop() {
  Blynk.run();
  Blynk.virtualWrite(12, HIGH);
}
