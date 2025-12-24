#include <TimeLib.h>
#include <Wire.h>                    
#include <LiquidCrystal_I2C.h>        

#include "DHT.h" // 

#define light_relay_pin 2
#define kettle_relay_pin 4  // relay pins
#define fan_relay_pin 7
#define humid_relay_pin 8

#define hall_move_pin A0
#define room_move_pin A1

#define temphum_pin 3

#define light_pin A2

DHT mydht(temphum_pin, DHT11); 
LiquidCrystal_I2C lcd(0x27,20,4);

bool temp, humid; // need to make situation better? or not?

void setup() {
  pinMode(light_relay_pin, OUTPUT);
  pinMode(kettle_relay_pin, OUTPUT);
  pinMode(fan_relay_pin, OUTPUT);
  pinMode(humid_relay_pin, OUTPUT);
  
  lcd.init();                      
  lcd.backlight();  
                  
  Serial.begin(9600);
  
  setTime(8, 20, 0, 2419, 12, 2025); // 12 января 2024, 14:30:45
  
  dht.begin();
}

void loop() {
  temphum_proc();
  relay_proc(digitalRead(hall_move_pin),
             digitalRead(room_move_pin),
             temp, humid, digitalRead(light_pin));
  lcdproc();
}

void lcdproc(){ 
  lcd.setCursor(0, 0);              
  lcd.print("Temperature: "); 
  lcd.print(t);     
            
  lcd.setCursor(0, 1);             
  lcd.print("Humidity: ");
  lcd.print(h);    
  lcd.setCursor(0, 2);    
           
  lcd.print("Time: ");
  lcd.print(hour()); 
  lcd.print(':');
  lcd.print(minute());
  lcd.print(':');  
  lcd.print(second());  
}

void temphum_proc(){
  short t = dht.readTemperature();
  short h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {  
    Serial.println("Ошибка считывания");
  }
  if(t > 26){temp = 1;}else{temp = 0;}
  if(h < 35){humid = 1;}else{humid = 0;}
}

void relay_proc(bool hall_move, bool live_move, bool temp, bool humid, bool light){
  if(temp && live_move){
    digitalWrite(fan_relay_pin, 1);
  }else{
    digitalWrite(fan_relay_pin, 0);
  }
  if(humid){
    digitalWrite(humid_relay_pin, 1);
  }else{
    digitalWrite(humid_relay_pin, 0);
  }
  if(light && live_move){
    digitalWrite(light_relay_pin, 1);
  }else{
    digitalWrite(light_relay_pin, 0);
  }
  if(hall_move){
    digitalWrite(kettle_relay_pin, 1);
    delay(60000);
    digitalWrite(kettle_relay_pin, 0);
  }else{
    digitalWrite(kettle_relay_pin, 0);
  }
}
