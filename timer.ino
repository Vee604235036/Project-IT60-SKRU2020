#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>                       //เรียกใช้ ไลบรารี่ บอร์ดesp8266
#define Relay1 D1                                     //กำหนดตัวแปร Relay1 เป็นpin D1
char auth[] = "iZZOfGMzeAfyM4te1i0vJCJw0YXy-Zxg";     //กำหนด TOKEN แอปฯBlynk
char ssid[] = "IoT_IT60_SKRU";                        //กำหนด SSID
char pass[] = "604235036";                            //กำหนด PASSWORD
BLYNK_WRITE(V13)                                      //กำหนดPin สำหรับ timer ของแอพ
{
  Serial.print("โปรแกรม 1  : ทำงาน = ให้อาหารปลา ");
  if (param.asInt() == 1) {         //สถานะ 1 = ติด(ระบบทำงาน)
    digitalWrite(Relay1, HIGH);     //สั่งให้ตัวแปรชื่อ Relay1ทำงาน
  }
  else if (param.asInt() == 0) {    //สถานะ 0 = ดับ(ระบบหยุดทำงาน)
    digitalWrite(Relay1, LOW);      //สั่งให้ตัวแปรชื่อ Relay1 หยุดทำงาน
  }
}
BLYNK_WRITE(V14)                    //กำหนดPin สำหรับ timer ของแอพ
{
  Serial.print("โปรแกรม 2  : ทำงาน = ให้อาหารปลา");
  if (param.asInt() == 1) {         //สถานะ 1 = ติด(ระบบทำงาน)
    digitalWrite(Relay1, HIGH);     //สั่งให้ตัวแปรชื่อ Relay1ทำงาน
  }
  else if (param.asInt() == 0) {    //สถานะ 0 = ดับ(ระบบหยุดทำงาน)
    digitalWrite(Relay1, LOW);      //สั่งให้ตัวแปรชื่อ Relay1 หยุดทำงาน
  }
}
BLYNK_WRITE(V15)                    //กำหนดPin สำหรับ timer ของแอพ
{
  Serial.print("โปรแกรม 3 : ทำงาน = ให้อาหารปลา ");
  if (param.asInt() == 1) {     //สถานะ 1 = ติด(ระบบทำงาน)
    digitalWrite(Relay1, HIGH); //สั่งให้ตัวแปรชื่อ Relay1ทำงาน
  }
  else if (param.asInt() == 0) { //สถานะ 0 = ดับ(ระบบหยุดทำงาน)
    digitalWrite(Relay1, LOW);  //สั่งให้ตัวแปรชื่อ Relay1 หยุดทำงาน
  }
}
void setup()
{
  Serial.begin(9600);                 //กำหนดเริ่มการรับส่งข้อมูลด้วยความเร็ว Baud Rate 9600
  pinMode(Relay1, OUTPUT);            //กำหนดให้ตัวแปรชื่อ Relay1 เป็น Output
  Blynk.begin(auth, ssid, pass);      //เริ่มการรับส่งข้อมูลผ่าน Blynk App
}
void loop()
{
  Blynk.run();                       //กำหนดให้สามารถควบคุมจากแอปฯ Blynk
}
