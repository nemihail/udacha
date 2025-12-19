// ко выводит на lcd теипературу, влажность и время




#include <TimeLib.h>
#include <Wire.h>                    
#include <LiquidCrystal_I2C.h>        
LiquidCrystal_I2C lcd(0x27,20,4);
#include "DHT.h"
#define DHTPIN 3 
DHT dht(DHTPIN, DHT11);     
                                     
void setup(){                         
    lcd.init();                      
    lcd.backlight();                  
    Serial.begin(9600);
  dht.begin();
  setTime(10, 40, 0, 19, 12, 2025); // 12 января 2024, 14:30:45
}                                     
                                      
void loop(){
  delay(1000); 
  int h = dht.readHumidity(); 
  int t = dht.readTemperature();   
lcd.setCursor(0, 0);              
    lcd.print("Temperature: "); 
    lcd.print(t);               
    lcd.setCursor(0, 1);             
    lcd.print("Humidity: ");
    lcd.print(h);    
    lcd.setCursor(0, 2);             
    lcd.print("Time:");
    lcd.print(hour()); 
    lcd.print(':');
    lcd.print(minute());
    lcd.print(':');  
    lcd.print(second());   
 

}

