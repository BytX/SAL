/*
================================================================================
SimpleAVRLogger
Version : 0.45b
Code by Patryk Pietrzak, Wiktor Tkaczyński
================================================================================
Program odczytuje dane z czujników typu DHT oraz fotorezystora. Następnie wysyła
poprez komunikacje szeregową wyniki do komputera.

Wymagania sprzętowe:
================
Dowolne Arduino z AtMega 328p lub 168.

Dodatkowo:
=======================
Dowolny czujnik DHT (DHT11,DHT22,DHT21)

Fotorezystor
================================================================================
Szkic korzysta z biblioteki DHT adafruit:

https://github.com/adafruit/DHT-sensor-library

================================================================================
*/

#include "DHT.h"

#define DHTPIN 2

#define DHTTYPE DHT22

float temperature = 0;
float humidity = 0;
int light = 0;

unsigned long time;
unsigned long last_time;
long delay_time;

uint8_t acc = 13;

DHT dht(DHTPIN, DHTTYPE);


void setup () {
  Serial.begin(9600);
  pinMode(A0, INPUT); //pin fotorezystora
  Serial.println("SimpleAVRLogger ver. 0.45b by Patryk Pietrzak, Wiktor Tkaczyński");
}

void loop() {

  last_time = millis();
  time = last_time / 1000;

  humidity = dht.readHumidity(); 
  temperature = dht.readTemperature();
  light = analogRead(A0);

  if (isnan(temperature) || isnan(humidity)) {
    char buf[128];
    sprintf(buf, "ERR|%d|%d", 0, time);

    Serial.print(buf);
  }
  else { 
    digitalWrite(acc, HIGH);
    char buf[128];
    
    char time_a[20];
    char temperature_a[5];
    char humidity_a[5];
    char light_a[5];
    
    dtostrf(time, 1, 2, time_a);
    dtostrf(temperature, 1, 2, temperature_a);
    dtostrf(humidity, 1, 2, humidity_a);
    dtostrf(light, 1, 2, light_a);
    
    
    sprintf(buf, "LOGED|%s|%s|%s|%s", time_a, temperature_a, humidity_a, light_a);

    Serial.print(buf); 
    digitalWrite(acc, LOW);
  }

  delay_time = 1000 - (millis() - last_time);
  
  if (delay_time > 0)
    delay(delay_time);

}
