#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN A0

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;

// -------- KEYPAD --------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------- SECURITY --------
String validUID = "ef8bd91e";   // replace if needed
String password = "2323";
String input = "";

bool rfidVerified = false;

void setup() {
  Serial.begin(9600);a
  SPI.begin();
  rfid.PCD_Init();

  doorServo.attach(A1);
  doorServo.write(0); // locked position

  Serial.println("Scan RFID card...");
}

void loop() {

  // -------- RFID --------
  if (!rfidVerified) {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {

      String uid = "";

      for (byte i = 0; i < rfid.uid.size; i++) {
        uid += String(rfid.uid.uidByte[i], HEX);
      }

      uid.toLowerCase();

      Serial.print("Scanned UID: ");
      Serial.println(uid);

      if (uid == validUID) {
        Serial.println("RFID Verified ✅");
        Serial.println("Enter Password:");
        rfidVerified = true;
      } else {
        Serial.println("Wrong RFID ❌");
      }

      delay(1000);
    }
  }

  // -------- KEYPAD --------
  if (rfidVerified) {
    char key = keypad.getKey();

    if (key) {
      Serial.print("*");

      if (key == '#') {   // Enter
        Serial.println();

        if (input == password) {
          Serial.println("Access Granted ✅");

          // 🔓 Unlock (rotate 90°)
          doorServo.write(90);
          delay(30000);

          // 🔒 Lock again
          doorServo.write(0);
        } else {
          Serial.println("Wrong Password ❌");
        }

        // reset
        input = "";
        rfidVerified = false;

        Serial.println("\nScan RFID card again...");
      }
      else if (key == '*') {
        input = "";
        Serial.println("\nCleared");
      }
      else {
        input += key;
      }
    }
  }
}