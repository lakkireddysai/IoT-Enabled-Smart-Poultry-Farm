#include "DHT.h"
#include <Servo.h>
#define  DHTPIN D0
#define DHTTYPE DHT11
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SSD1306_LCDHEIGHT 64   
DHT dht(DHTPIN, DHTTYPE);
int temp_led=D7;
#define echopin D3
#define trigpin D4
Servo myservo;
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif  
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(temp_led,OUTPUT);
  pinMode(D3,INPUT);
pinMode(D4,OUTPUT);
myservo.attach(D2);
dht.begin();
  delay(2000);
display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
// display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,20);
  display.print("Smart Poultry Farm");
  // update display with all of the above graphics
  display.display();
  Serial.begin(9600);
}

void loop() {
  //gas sensor start
  int analogSensor = analogRead(A0);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  delay(500);
    if (analogSensor >45)
  {
    Serial.println("danger");  }
  else
  {

  }
  delay(100);
  //gas sensor end
  //dht11 start
  float t = dht.readTemperature();
  Serial.println(t);
  delay(500);
  if(t>35)
  {
    Serial.println("temp is very high");
    digitalWrite(temp_led,HIGH);
    delay(200);
  }
  else if(t<25)
  {
    Serial.println("temp is very low");
  }
else
{
  digitalWrite(temp_led,LOW);
}
//dht11 end
//ultrasoinc start
digitalWrite(D4,HIGH);
delay(1000);
digitalWrite(D4,LOW);
int duration = pulseIn(echopin,HIGH);
int distance = (duration/2)*0.0343;
 Serial.println(distance);
 delay(500);
 if(distance<5)
 {
  Serial.println("NO water for hens");
 delay(500);
 }
 else if(distance>10)
 {
  Serial.println("Water overflow");
 delay(500);
 }
 else
 {
  }
 //ultrasoinc end
  //servo start
myservo.write(90);
delay(2000);
myservo.write(0);                           
  //servo end
  delay(100);
  
}
