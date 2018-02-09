#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial blueToothSerial(0, 1);
SoftwareSerial HC12(7, 8);

int line = 1;
int buzzer = 9;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("Rocket Box");
  lcd.setCursor(0, 1);  
  blueToothSerial.begin(9600);
  HC12.begin(9600);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void loop() {  
  if (HC12.available()) {
    readMessage();
  }
}

void playBuzzer() {
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
}

void readMessage() {
  lcd.print("                    ");  
  lcd.setCursor(0, line);
  lcd.print(HC12.read());
  Serial.println(HC12.read());
  line++;
  if (line > 3) {
    line = 1;
  }
  lcd.setCursor(0, line);
  playBuzzer();
}

