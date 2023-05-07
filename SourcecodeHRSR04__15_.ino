#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define nguongCanhbao 2
#define nguongNguyhiem 0.6

LiquidCrystal_I2C lcd(0x27,16,2); //khai bao dia chi mach giao tiep i2c

// const int ledRed = 4;
// const int ledYellow = 7;
// const int ledGreen = 8;
const int trig = 2;
const int echo=3;
unsigned int distance1;
unsigned int distance2;

void setup() {
  // khai bao chan tren HC_SR04, trig ung voi chan ouput, echo ung voi chan input
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  // khoi tao man hinh LCD
  lcd.init();
  lcd.backlight();
  //khai bao leb canh bao
  // pinMode(ledRed, OUTPUT);
  // pinMode(ledYellow, OUTPUT);
  // pinMode(ledGreen, OUTPUT);
}

void loop() {
  //khai bao bien
  long time, deadTime;
  // Phat xung tu chan trig
  digitalWrite(trig,LOW); // tat chan trig
  delayMicroseconds(2);
  digitalWrite(trig,HIGH); //phat xung tu chan trig
  delayMicroseconds(10);
  digitalWrite(trig,LOW); // tat chan trig

  // Tim thoi gian xung Hight o chan Echo
  time=pulseIn(echo,HIGH); // Tra ve thoi gian chan echo nhan tin hieu HIGHT den khi tin hieu xuong LOW
  distance2=int(time/2/29.412); // Tinh khoang cach dua theo toc do anh sang la 340 m/s
  deadTime=distance2/((distance1-distance2)*10); // Du doan thoi gian va cham

// Den canh bao dua theo thoi gian va cham 
 if (deadTime<nguongNguyhiem){
    // digitalWrite(ledGreen, 0);
    // digitalWrite(ledYellow, 0);
    // digitalWrite(ledRed, 1);
    lcd.setCursor(4, 1);
    lcd.print("Danger !!!");
 }
 else if (deadTime>=nguongNguyhiem && deadTime<=nguongCanhbao){
    // digitalWrite(ledGreen, 0);
    // digitalWrite(ledYellow, 1);
    // digitalWrite(ledRed, 0);
    lcd.setCursor(4, 1);
    lcd.print("Watch Out");
}
else {
    // digitalWrite(ledGreen, 1);
    // digitalWrite(ledYellow, 0);
    // digitalWrite(ledRed, 0);
    lcd.setCursor(6, 1);
    lcd.print("Safe ^ ^");
}

//In ra man hinh lcd i2c
  
  lcd.setCursor(1, 0);
  lcd.print("Distance:");
  lcd.setCursor(10, 0);
  lcd.print(distance2);
  lcd.setCursor(14,0);
  lcd.print("cm");
  delay(1000);
  lcd.clear();
  distance1=distance2;
}
