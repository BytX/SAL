/*
================================================================================
SimpleAVRLogger
Version : 0.4b
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
  Serial.println("SimpleAVRLogger ver. 0.4b by Patryk Pietrzak, Wiktor Tkaczyński");
  Serial.println("time t*C h% light");
}

void loop() {

  czas = millis() / 1000;

  float h = dht.readHumidity(); //wilgotnosc
  float t = dht.readTemperature(); //temperatura
  int l = analogRead(A0); //swiatlo

  if (isnan(t) || isnan(h)) { //suma kontrolna, jesli wystapi blad
    Serial.print(czas);
    Serial.print(" ");
    Serial.println("ERR|0"); //0 - bład połączenia/pomiaru
  }
  else { //jesli wszystko ok, przeslij pomiary
    digitalWrite(acc, HIGH);
    char buf[128];
    sprintf(buf, "%d|%f|%f|%d", czas, t, h, l);
    //String returned_data = czas + s + t + s + h + s + l; //szajs

    Serial.println(buf); // wysyłanie pomiarow

    digitalWrite(acc, LOW);
  }
  delay(1000); //Wykonuj pomiar co 1 sek.

}