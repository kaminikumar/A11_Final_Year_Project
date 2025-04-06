#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <ultrasonic.h>
#include <LiquidCrystal.h>

#define BUZZER 4
#define RELAY 5
#define VIBRATION A1
#define TRIG_PIN 7
#define ECHO_PIN 6

char pydata;
const String PHONE_NUMBER = "9445365881";
const uint8_t PIN_MP3_RX = 2, PIN_MP3_TX = 3;

char pychar = 'x';
int distance, vib, dis;

SoftwareSerial ss(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
ULTRASONIC ultrasonic;

void sendSMS(const String& number, const String& message);
void receiveData();

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  ultrasonic.begin(TRIG_PIN, ECHO_PIN);

  if (player.begin(ss)) {
    Serial.println("DFPlayer Mini Initialized");
  }
  else
  {
    Serial.println("DFPlayer Mini Not-Initialized");
  }

  lcd.begin(16, 2);
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(VIBRATION, INPUT);

  digitalWrite(RELAY, HIGH);
  digitalWrite(BUZZER, LOW);

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Animal detection");
  delay(2000);
}

void loop() {
  dis = ultrasonic.ultra();
  vib = digitalRead(VIBRATION);
  distance = abs(dis);
  Serial.println(distance);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DISTANCE: " + String(distance));
  lcd.setCursor(0, 1);
  lcd.print("Vibration: " + String(vib));

  if (vib == 1) {
    sendSMS(PHONE_NUMBER, "Animal damaging the kit");
    Serial.print("Msg, Send Successfully");
  }

  if (distance < 40) {
    digitalWrite(RELAY, LOW);
    delay(4000);
    digitalWrite(RELAY, HIGH);
  } else if (distance > 41 && distance < 200) {
    serialEvent();
    Serial.print("J");
  } else if (distance > 201) {
    digitalWrite(BUZZER, HIGH);
    delay(50);
    digitalWrite(BUZZER, LOW);
    delay(50);
  } else {
    digitalWrite(RELAY, HIGH);
    digitalWrite(BUZZER, LOW);
  }
  delay(1000);
}

void serialEvent()
{
  while (Serial.available() > 0) {
    pydata = Serial.read();
    Serial.println("pydata:" + String(pydata));
    if (pychar != pydata) {
      pychar = pydata;
      switch (pychar) {

        case 'A':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Buffalo Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(1);
          delay(1000);
          pychar = 'x';
          break;

        case 'B':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Elephant Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(2);
          delay(1000);
          pychar = 'x';
          break;

        case 'C':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Rhino Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(30);
          player.play(3);
          delay(1000);
          pychar = 'x';
          break;

        case 'D':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Zebra Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(4);
          delay(1000);
          pychar = 'x';
          break;

        case 'E':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Cheetah Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(5);
          delay(1000);
          pychar = 'x';
          break;

        case 'F':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Fox Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(4);
          delay(1000);
          pychar = 'x';
          break;

        case 'G':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Jaguar Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(3);
          delay(1000);
          pychar = 'x';
          break;

        case 'H':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Tiger Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(4);
          delay(1000);
          pychar = 'x';
          break;

        case 'I':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Lion Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(5);
          delay(1000);
          pychar = 'x';
          break;

        case 'J':
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Panda Detected");
          lcd.setCursor(0, 1);
          lcd.print(String(distance));
          player.volume(50);
          player.play(4);
          delay(1000);
          pychar = 'x';
          break;
      }
    }
  }
}
void sendSMS(const String& number, const String& message) {
  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.print("AT+CMGS=\"+91" + number + "\"\r");
  delay(1000);
  Serial.println(message);
  delay(200);
  Serial.write(26);
}
