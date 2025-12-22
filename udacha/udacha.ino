
#include "DHT.h"
#include <DHT.h>

#define light_relay_pin 2
#define kettle_relay_pin 4  // relay pins
#define fan_relay_pin 7
#define humid_relay_pin 8

#define hall_move_pin A0
#define room_move_pin A1

#define temphum_pin 3

DHT mydht(temphum_pin, DHT11); 

bool temp, humid; // need to make situation better? or not?

short light_limit;

void setup() {
  pinMode(light_relay_pin, OUTPUT);
  pinMode(kettle_relay_pin, OUTPUT);
  pinMode(fan_relay_pin, OUTPUT);
  pinMode(humid_relay_pin, OUTPUT);

  dht.begin();
}

void loop() {
}

void temphum_proc(){
  t = dht.readTemperature();
  h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {  
    Serial.println("Ошибка считывания");
  }
  if(t > 26){temp = 1;}else{temp = 0;}
  if(h < 35){humid = 1;}else{humid = 0;}
}

void relay_proc(bool hall_move, bool live_move, bool temp, bool humid, bool light){
  if(temp && live_move){digitalWrite(fan_relay_pin, 1);}else{digitalWrite(fan_relay_pin, 0);} // вентилятор если жарко и в комнате кто-то есть
  if(humid){digitalWrite(humid_relay_pin, 1);}else{digitalWrite(humid_relay_pin, 0);} // увлажнитель в комнате если влажно
  if(light){digitalWrite(light_relay_pin, 1);}else{digitalWrite(light_relay_pin, 1);} // свет в комнате
  // остался только чайник. еще надо написать меню для лсд, обработку времени, и (несложно) света.
}

