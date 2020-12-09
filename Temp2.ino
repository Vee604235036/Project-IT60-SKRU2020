#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>                   //เรียกใช้ ไลบรารี่ บอร์ดesp8266
#include <OneWire.h>                              //ไลบรารี่ของ DS18B20
#include <DallasTemperature.h>                    //ไลบรารี่ของ เซนเซอร์อุณหภูมิ
#define ONE_WIRE_BUS 2                            // กำหนด INPUT
OneWire oneWire(ONE_WIRE_BUS);                    // ADC เซนเซอร์อุณหภูมิ
DallasTemperature DSTEMP(&oneWire);               // ADC DS18B20
char auth[] = "iZZOfGMzeAfyM4te1i0vJCJw0YXy-Zxg"; //กำหนด TOKEN แอปฯBlynk
char ssid[] = "IoT_IT60_SKRU";                    //กำหนด SSID 
char pass[] = "604235036";                        //กำหนด PASSWORD
float temp;                                       //ตัวแปรเก็บค่าแปลงให้เป็นหน่วย℃
#define hot  D1                                   //Relay ช่องที่1
#define cold D2                                   //Relay ช่องที่2
WidgetLED led1(V4);                               //กำหนด pin ของตัวแปร ในแอปฯBlynk
WidgetLED led2(V5);                               //กำหนด pin ของตัวแปร ในแอปฯBlynk
WidgetLED ledBlynk(V10);                          //กำหนด pin ของตัวแปร ในแอปฯBlynk
void setup()
{
  Serial.begin(9600);                             //กำหนดเริ่มการรับส่งข้อมูลด้วยความเร็ว Baud Rate 9600
  Blynk.begin(auth, ssid, pass);                  //เริ่มการรับส่งข้อมูลผ่าน Blynk App 
  DSTEMP.begin();                                 //เริ่มการรับส่งข้อมูลของเซนเซอร์DS18B20 
  pinMode(hot, OUTPUT);                           //กำหนดให้ตัวแปรชื่อ hot เป็น Output 
  pinMode(cold, OUTPUT);                          //กำหนดให้ตัวแปรชื่อ cold เป็น Output 
}
BLYNK_CONNECTED() {                               //ซิงค์ข้อมูลทั้งหมดล่าสุดจาก Blynk Server
  Blynk.syncAll();
}
void loop()
{
  Blynk.run();
  DSTEMP.requestTemperatures();                     //เรียกใช้ DS18B20
  temp = DSTEMP.getTempCByIndex(0);                 //ดึงค่าอุณหภูมิ
  Blynk.virtualWrite(V3, temp);                     //แสดงค่าออกมาทางจอของแอปฯBlynk ที่pin V3
  Serial.print("อุณหภูมิในบ่อปลา =  ");                //แสดงผลออกทาง Serial Monitor
  Serial.print(DSTEMP.getTempCByIndex(0));          //แสดงค่าอุณหภูมิออกทาง Serial Monitor
  Serial.print(" °C \n");                           //แสดงผลออกทาง Serial Monitor
  if (temp > 30 )                                   //ทำงานเมื่ออุณหภูมิมากกว่า30
  {
    digitalWrite(hot, HIGH);                        //สั่งให้รีเลย์เครื่องchillerทำงาน
    led1.on();                                      //สั่งให้LEDในแอพทำงาน
    Serial.println(" ลดอุณหภูมิ ");                   //แสดงผลออกทาง Serial Monitor
  }
  else if (temp < 25 ) {                            //ทำงานเมื่ออุณหภูมิมากกว่า30
    digitalWrite(cold, HIGH);                       //สั่งให้รีเลย์เครื่องheaterทำงาน
    led2.on();                                      //สั่งให้LEDในแอพทำงาน
    Serial.println(" เพิ่มอุณหภูมิ");                   //แสดงผลออกทาง Serial Monitor
  }
  else   {
    led1.off();                                     //สั่งให้LED1ในแอพดับ
    Serial.println("LED off ");                     //แสดงผลออกทาง Serial Monitor
    digitalWrite(hot, LOW);                         //สั่งให้รีเลย์เครื่องchillerทำงาน
    digitalWrite(cold, LOW);                        //สั่งให้รีเลย์เครื่องheaterหยุดทำงาน
    led2.off();                                     //สั่งให้LED2ในแอพดับ
    Serial.println("V2: LED off ");                 //แสดงผลออกทาง Serial Monitor
  }
  delay(60000);                                      //กำหนดความหน่วง 60000 มิลลิวินาที หรือเท่ากับ 1นาที  
  return;
}
