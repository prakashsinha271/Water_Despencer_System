#include <LiquidCrystal.h>

int trigPin = 8;    // Trigger
int echoPin = 9;    // Echo
long duration, cm, inches;
int ledR = 6; //Red LED
int ledG = 7; //Green LED
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int buzzer = 10; //buzzer to arduino pin 10
const int sensor=A1;
float tempc;
float tempf;
float vout;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(sensor,INPUT);
}
 
void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  lcd.setCursor(0, 1);
  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  //temprature calculation
  vout=analogRead(sensor);
  vout=(vout*500)/1023;


 if(cm<=10)
  {
    lcd.clear();
    lcd.print("Water Filled!!");
    lcd.setCursor(0, 1);
    lcd.print(vout);
    lcd.print(" - warm");
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    tone(buzzer, 3000); // Send 1KHz sound signal...
    delay(3000);
    lcd.clear();
    /*digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    lcd.print("Water Filled!!");
    lcd.print("Celcious");*/
  }
  
  else if(cm>10 && cm<=30 )
  {
    lcd.clear();
    lcd.print("Filling Water.....");
    lcd.setCursor(0, 1);
    lcd.print(vout);
    lcd.print(" - warm");
    digitalWrite(ledG, HIGH);
    digitalWrite(ledR, HIGH);
    tone(buzzer, 1000, 500);     // Stop sound...
    delay(1000);
    noTone(buzzer);
    lcd.clear();
   /* digitalWrite(ledG, HIGH);
    digitalWrite(ledR, HIGH);
    lcd.print("Filling Water.....");
    tone(buzzer, 1000, 500);  */
    
  }
 else if(cm>30 && cm<40)
  {
    lcd.clear();
    lcd.print("Waiting");
    lcd.setCursor(0, 1);
    lcd.print("for container...");
    digitalWrite(ledG, HIGH);
    digitalWrite(ledR, LOW);
    noTone(buzzer);
    delay(1000);
    noTone(buzzer);
    lcd.clear();
   /* digitalWrite(ledG, HIGH);
    digitalWrite(ledR, LOW);
    lcd.print("Waiting");
    lcd.setCursor(0, 1);
    lcd.print("for container...");*/
  }
  else
  {
    lcd.clear();
    lcd.print("Welcome to smart");
    lcd.setCursor(0, 1);
    lcd.print("water system..");
    /*lcd.print("Nothing");*/
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    noTone(buzzer);
  }

  delay(250);
}
