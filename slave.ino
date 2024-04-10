#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial Gsm(9, 10);

String phone_no[] = {"8897008307"};
int i;
TinyGPS gps;
String textMessage;
void setup()
{
  Serial.begin(38400);
  Gsm.begin(9600);
  delay(2000);
  //  Serial.print("AT+CMGF=1\r");
  //  delay(100);
  //  Serial.print("AT+CNMI=2,2,0,0,0\r");
  //  delay(100);
}
char c;
void loop() {
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  if (Serial.available()) {
    c = Serial.read();
    Serial.println(((int) c ) - 48);

    if (gps.encode(c))
      newData = true;

    if (c == '1') {
      for (i = 0; i < sizeof(phone_no) / sizeof(String); i++) {
        float flat, flon;
        unsigned long age;
        gps.f_get_position(&flat, &flon, &age);
        Gsm.print("AT+CMGF=1\r");
        delay(400);
        Gsm.print("AT+CMGS=\"");
        Gsm.print(phone_no[i]);
        Gsm.println("\"");
        delay(3000);
        delay(500);
      }
    }
  } else {
    delay(10);
  }
}
