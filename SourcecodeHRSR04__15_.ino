#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define nguongCanhbao 400 // khoang cach an toan 4m
#define nguongNguyhiem 200 // khoang cach nguy hiem 2m

LiquidCrystal_I2C lcd(0x27,16,2); //khai bao dia chi mach giao tiep i2c

// khai bao cac chan output
const int ledRed = 4;
const int ledYellow = 7;
const int ledGreen = 8;
const int trig = 2;
const int echo=3;
const int loud = 13;

void setup() {
  // khai bao chan tren HC_SR04, trig ung voi chan ouput, echo ung voi chan input
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  // khoi tao man hinh LCD
  lcd.init();
  lcd.backlight();
  //khai báo leb cảnh báo
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  //khai báo còi cảnh báo
  pinMode(loud, OUTPUT);
}

void loop() {
  //khai bao bien
  long time;
  unsigned int distance1;
  unsigned int distance2;
  // Phat xung tu chan trig
  digitalWrite(trig,LOW); // tat chan trig
  delayMicroseconds(2);
  digitalWrite(trig,HIGH); //phat xung tu chan trig
  delayMicroseconds(10);
  digitalWrite(trig,LOW); // tat chan trig

  // Tim thoi gian xung Hight o chan Echo
  time=pulseIn(echo,HIGH); // Tra ve thoi gian chan echo nhan tin hieu HIGHT den khi tin hieu xuong LOW
  distance1=int(time/2/29.412); // Tinh khoang cach dua theo toc do anh sang la 340 m/s
  //In ra man hinh lcd i2c
  lcd.setCursor(1, 0);
  lcd.print("Distance:");
  lcd.setCursor(10, 0);
  lcd.print(distance1);
  lcd.setCursor(14,0);
  lcd.print("cm");
  delay(100);
  lcd.clear();
  // Phat xung tu chan trig
  digitalWrite(trig,LOW); // tat chan trig
  delayMicroseconds(2);
  digitalWrite(trig,HIGH); //phat xung tu chan trig
  delayMicroseconds(10);
  digitalWrite(trig,LOW); // tat chan trig

  // Tim thoi gian xung Hight o chan Echo
  time=pulseIn(echo,HIGH); // Tra ve thoi gian chan echo nhan tin hieu HIGHT den khi tin hieu xuong LOW
  distance2=int(time/2/29.412); // Tinh khoang cach dua theo toc do anh sang la 340 m/s 

  // Dieu kien de dua ra canh bao nguy hiem
   if (distance2>=distance1){
    digitalWrite(ledGreen, 1);
    digitalWrite(ledYellow, 0);
    digitalWrite(ledRed, 0);
    lcd.setCursor(6, 1);
    digitalWrite(loud, 0);
    lcd.print("Safe ^ ^");

 }
  
  // Den canh bao dua theo thoi gian va cham 

 else{
  if (distance1<nguongNguyhiem){
    digitalWrite(ledGreen, 0);
    digitalWrite(ledYellow, 0);
    digitalWrite(ledRed, 1);
    lcd.setCursor(4, 1);
    digitalWrite(loud, 1);
    lcd.print("Danger !!!");
    
  }
  else if (distance1>=nguongNguyhiem && distance1<=nguongCanhbao){
    digitalWrite(ledGreen, 0);
    digitalWrite(ledYellow, 1);
    digitalWrite(ledRed, 0);
    lcd.setCursor(4, 1);
    digitalWrite(loud, 0);
    lcd.print("Watch Out");
}
 else {
    digitalWrite(ledGreen, 1);
    digitalWrite(ledYellow, 0);
    digitalWrite(ledRed, 0);
    lcd.setCursor(6, 1);
    digitalWrite(loud, 0);
    lcd.print("Safe ^ ^");
}
}
}
