#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);
String rfidCard;
int salah1 = 0;
int status1 = 0;

//Pin Buzzer + ke pin 3
byte alarm = 3;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();

//  Pin Lampu salah ke 6, lampu akses masuk ke 7
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}


void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
      if (rfidCard == "71 36 4 217" && status1 == 0) {
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        status1 = 0;
        salah1 = 0;
      }
      else if (rfidCard != "71 36 4 217" && salah1 == 0) {
        salah1 = 1;
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
        digitalWrite(7, HIGH);
        delay(500);

      }
      else if (salah1 == 1 && rfidCard != "71 36 4 217" ) {
        salah1 = 2;
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
        digitalWrite(7, HIGH);
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
        digitalWrite(7, HIGH);
      }
      else if (salah1 == 2 && rfidCard != "71 36 4 217" ) {
        salah1 = 3;
        tone(alarm, 800);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
        digitalWrite(7, HIGH);
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
        digitalWrite(7, HIGH);
        delay(500);
        digitalWrite(7, LOW);
        delay(500);
        digitalWrite(7, HIGH);
        noTone(alarm);
      }

    }
  }
}
