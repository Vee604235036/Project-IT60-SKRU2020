#define SENSOR (A0)                   //กำหนด pin A0 เป็น input ของ DoSensor
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>              //เรียกใช้ ไลบรารี่ บอร์ดesp8266
#include <BlynkSimpleEsp8266.h>
float voltage, turbidity ;            //กำหนดตัวแปรสำหรับเก็บค่าโวลต์และความขุ่นเพื่อเปรียบเทียบ
int sumturbidity;                     //กำหนดตัวแปรสำหรับหารค่าอุณหภูมิ
#define Relay1 D1                     //กำหนดตัวแปรpin Output ไปยังรีเลย์ตัวที่1
char auth[] = "iZZOfGMzeAfyM4te1i0vJCJw0YXy-Zxg";  //กำหนด TOKEN แอปฯBlynk
char ssid[] = "IoT_IT60_SKRU";                     //กำหนด SSID
char pass[] = "604235036";                         //กำหนด PASSWORD
WidgetLED led1(V6);                                //กำหนด pin ของตัวแปรled1 ในแอปฯBlynk
WidgetLED led2(V7);                                //กำหนด pin ของตัวแปรled1 ในแอปฯBlynk
void setup()
{
  Serial.begin(9600);                              //กำหนดเริ่มการรับส่งข้อมูลด้วยความเร็ว Baud Rate 9600
  Blynk.begin(auth, ssid, pass);                   //เริ่มการรับส่งข้อมูลผ่าน Blynk App
  pinMode(SENSOR, INPUT);                          //กำหนดให้ตัวแปรชื่อ SENSOR เป็น Input
  pinMode(Relay1, OUTPUT);                         //กำหนดให้ตัวแปรชื่อ Relay1 เป็น Output
  digitalWrite(Relay1, LOW);                       //กำหนดค่าเริ่มต้นใช้ digitalWrite
  digitalWrite(Relay2, LOW);                       //กำหนดค่าเริ่มต้นใช้ digitalWrite
}
BLYNK_CONNECTED() {                                //ซิงค์ข้อมูลทั้งหมดล่าสุดจาก Blynk Server
  Blynk.syncAll();
}
void loop()
{
  voltage =  analogRead(SENSOR) * (5.0 / 1024.0);;                        //แปลงค่าโวลต์
  turbidity = -1120.4 * voltage * voltage + 5742.3 * voltage - 4352.9 ;   //แปลงค่าอุณหภูมิ
  sumturbidity = 16 + turbidity / 100  ;                                  //เปลี่ยนเป็นหน่วย NTU
  if ( (turbidity > 0))                                                   //เริ่มการตรวจสอบเงื่อนไขเมื่อความขุ่นมีค่ามากกว่า0
  {
    Serial.print("ระดับความขุ่น = ");                                        //แสดงผลออกทาง Serial Monitor
    Serial.print(sumturbidity );                                          //แสดงค่าความขุ่นออกทาง Serial Monitor
    Serial.println(" NTU");                                               //แสดงผลออกทาง Serial Monitor
    Blynk.virtualWrite(V29, sumturbidity);                                //ส่งค่าแสดงขึ้นแอปพลิเคชั่น
    Blynk.run();                                                          //กำหนดให้สามารถควบคุมได้จากแอปฯBlynk
    {
      if (sumturbidity < 30   ) {                                         //ถ้าค่าออกซิเจนน้อยกว่า30จะทำงาน
        led1.on();                                                        //สั่งให้LEDในแอพทำงาน
        digitalWrite(Relay1, HIGH);                                       //สั่งให้รีเลย์ทำงาน
        Serial.println("สถานะ LED1: on");                                 //แสดงผลออกทาง Serial Monitor
      }
      else if (sumturbidity > 60  ) {                                     //ถ้าค่าออกซิเจนมากกว่า60จะทำงาน
        led1.on();                                                        //สั่งให้LEDในแอพทำงาน
        digitalWrite(Relay1, HIGH);                                       //สั่งให้รีเลย์ทำงาน
        Serial.println("สถานะ LED: on");                                  //แสดงผลออกทาง Serial Monitor
      }
      else {
        digitalWrite(Relay1, LOW);                                        //สั่งให้รีเลย์หยุดการทำงาน
        Serial.println("สถานะ LED: off");                                 //แสดงผลออกทาง Serial Monitor
        led1.off();                                                       //สั่งให้LEDในแอพดับ
      }
    }
    delay(60000);                                                          //กำหนดความหน่วง 60000 มิลลิวินาที หรือเท่ากับ 1นาที
  }
}
