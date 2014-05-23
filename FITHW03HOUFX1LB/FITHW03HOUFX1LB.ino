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

#define DHTPIN 2     // pin od czujnika

#define DHTTYPE DHT22 // typ czujnika

float t = 0;
float h = 0;
unsigned long czas;
uint8_t acc = 13;
//char* s ="|"; //szajs

DHT dht(DHTPIN, DHTTYPE);

void setup () {
  Serial.begin(9600);
  pinMode(A0, INPUT); //pin fotorezystora
  Serial.println("SimpleAVRLogger ver. 0.45b by Patryk Pietrzak, Wiktor Tkaczyński");
  Serial.println("TYPE time t*C h% light");
}

void loop() {

  unsigned long last_time = millis();
  czas = last_time / 1000;

  float h = dht.readHumidity(); //wilgotnosc
  float t = dht.readTemperature(); //temperatura
  int l = analogRead(A0); //swiatlo

  if (isnan(t) || isnan(h)) { //suma kontrolna, jesli wystapi blad
    Serial.print("ERR|0"); //0 - bład połączenia/pomiaru
    Serial.print("|");
    Serial.println(czas);
  }
  else { //jesli wszystko ok, przeslij pomiary
    digitalWrite(acc, HIGH);
    char buf[128];
    sprintf(buf, "LOGED|%d|%f|%f|%d", czas, t, h, l);
    //String returned_data = czas + s + t + s + h + s + l; //szajs

    Serial.println(buf); // wysyłanie pomiarow

    digitalWrite(acc, LOW);
  }

  delay_time = 1000 - (millis() - last_time); // wait 1s minus elapsed time 

  delay(delay_time); //Wykonuj pomiar co 1 sek.

}
