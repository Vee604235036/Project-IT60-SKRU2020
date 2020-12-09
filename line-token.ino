#include <TridentTD_LineNotify.h>                                //เรียกใช้ไลบรารี่LineNotify
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>                                         //เรียกใช้ ไลบรารี่ บอร์ดesp8266
#include <BlynkSimpleEsp8266.h>
#define LINE_TOKEN "YoVyek8CSt8ZjcibEmoO2qdKa8whnrYChhBgKOT6PgS" //กำหนดเลขTOKEN LineNotify
char auth[] = "iZZOfGMzeAfyM4te1i0vJCJw0YXy-Zxg";                //กำหนด TOKEN แอปฯBlynk
char ssid[] = "IoT_IT60_SKRU";                                   //กำหนด SSID
char pass[] = "604235036";                                       //กำหนด PASSWORD
#define pingPin D4                                               //กำหนดตัวแปรpingPin เป็นpin D4
#define inPin   D5                                               //กำหนดตัวแปรinPin   เป็นpin D5
void setup() {
  Blynk.begin(auth, ssid, pass);                                 //เริ่มการรับส่งข้อมูลผ่าน Blynk App
  Serial.begin(9600);                                            //กำหนดเริ่มการรับส่งข้อมูลด้วยความเร็ว Baud Rate 9600
  Serial.println();
  Serial.println(LINE.getVersion());                             //ส่งข้อมูลไปยังLINE
  Serial.printf("WiFi connecting to %s\n", SSID);                //แสดงผลออกทาง Serial Monitor
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");                                           //แสดงผลออกทาง Serial Monitor
  }
  Serial.printf("\nWiFi connected\nIP : ");                      //แสดงผลออกทาง Serial Monitor
  Serial.println(WiFi.localIP());                                //แสดงผลออกทาง Serial Monitor
  LINE.setToken(LINE_TOKEN);                                     //เรียกใช้TOKEN LineNotify
}
BLYNK_CONNECTED() {                                              //ซิงค์ข้อมูลทั้งหมดล่าสุดจาก Blynk Server
  Blynk.syncAll();
}
void loop() {

  long duration, cm;                                             //กำหนดตัวแปรเพื่อหาค่าcm
  pinMode(pingPin, OUTPUT);                                      //กำหนดให้ตัวแปรชื่อ pingPin เป็น Output
  digitalWrite(pingPin, LOW);                                    //กำหนดค่าเริ่มต้นใช้ digitalWrite
  delayMicroseconds(2);                                          //หน่วงเวลา โดยมีหน่วยเป็น uS (micro-Second) ซึ่งมีค่าการหน่วงเวลา เท่ากับ 1/1,000,000 วินาที จะหน่างเวลาน้อยกว่าคำสั่ง Delay
  digitalWrite(pingPin, HIGH);                                   //กำหนดค่าเริ่มต้นใช้ digitalWrite
  delayMicroseconds(5);                                          //หน่วงเวลา โดยมีหน่วยเป็น uS (micro-Second) ซึ่งมีค่าการหน่วงเวลา เท่ากับ 1/1,000,000 วินาที จะหน่างเวลาน้อยกว่าคำสั่ง Delay
  digitalWrite(pingPin, LOW);                                    //กำหนดค่าเริ่มต้นใช้ digitalWrite
  pinMode(inPin, INPUT);                                         //กำหนดให้ตัวแปรชื่อ inPin เป็น Input
  duration = pulseIn(inPin, HIGH);                               //เป็นฟังก์ชั่นสำหรับอ่านสัญญาณดิจิตอล
  cm = microsecondsToCentimeters(duration);                      //ดึงค่าcm
  if ((cm > 0) && (cm <= 20)) {                                  //ทำงานเมื่อcmมากกว่า0และน้อยกว่าหรือเท่ากับ20cm
    Serial.print(cm);                                            //แสดงผลออกทาง Serial Monitor
    Serial.print(sumturbidity );                                 //แสดงผลออกทาง Serial Monitor
    Serial.print("cm");
    Serial.println();
    Blynk.virtualWrite(V27, cm);                                 //แสดงผลออกทางแอปฯBlynk ที่pin V27
    Blynk.run();                                                 //กำหนดให้สามารถควบคุมได้จากแอปฯBlynk
  }
  if (cm >= 10) {                                                //แจ้งเตือนเมื่อมากกว่าหรือเท่ากับ10cm
    LINE.notify("อาหารปลาใกล้หมดแล้วครับ กรุณาเติมด้วยครับ");           //ข้อความที่จะแจ้งเตือนไปยัง LINE
  }
  delay(1800000);                                               //กำหนดความหน่วง 1800000 มิลลิวินาที หรือเท่ากับ30นาที
}
