/* EMITTER1

   THIS PROGRAM SENDS THE VALUE THE DS18B20 TEMPERATURE SENSOR TO GOBLIN 2
   FOR RADIOFREQUENCY.

  Hardware SPI.
  Pins:
 * MISO -> 12 ARDUINO
 * MOSI -> 11 ARDUINO
 * SCK -> 13 ARDUINO
 * CE -> 9 ARDUINO
 * CSN -> 10 ARDUINO
 
  modified 26 Diciembre 2016
  by Rafael Cortés
  -GOBLIN 2 TEAM. VERSE Technology.

 */
 
#include <OneWire.h>                            // LIBRARY
#include <DallasTemperature.h>                  // LIBRARY
#include <SPI.h>                                // LIBRARY
#include <Mirf.h>                               // LIBRARY
#include <nRF24L01.h>                           // LIBRARY
#include <MirfHardwareSpiDriver.h>              // LIBRARY
#define Pin 2                                   // SENSOR PIN 2 DS18B20 DATA
OneWire ourWire(Pin);                           // PIN DECLARED AS BUS FOR OneWire communication
DallasTemperature sensors(&ourWire);            // LIBRARY DallasTemperature

void setup(){
  Serial.begin(9600);                           // Serial.begin 
  Mirf.csnPin = 10;                             // CSN -> 10 ARDUINO
  Mirf.cePin = 9;                               // CE -> 9 ARDUINO 
  Mirf.spi = &MirfHardwareSpi;                  // CONFIGURATION
  Mirf.init();                                  // INIT LIBRARY MIRF 
  Mirf.setRADDR((byte *)"JORGE");               // CONFIGURE THIS DEVICE WITH THE NAME JORGE
  Mirf.payload =32;                             // PAYLOAD 32
  Mirf.channel = 100;                           // CHANNEL 21 
  Mirf.config();                                // MIRF CONFIG
  Serial.println("Beginning...");               // PRINT Beginning IN THE SERIAL
  sensors.begin();                              // BEGIN SENSOR
}

void loop(){
  sensors.requestTemperatures();                   // PREPARE THE SENSOR FOR READ
  float TEMPERATURA1=sensors.getTempCByIndex(0);   // GET THE TEMPERATURE AND SAVE IN TEMPERATURA1
  Mirf.setTADDR((byte *)"RAFA1");                  // CONFIGURE FOR TO SEND TO RAFA1
  Mirf.send((byte *)&TEMPERATURA1);                // SEND TEMPERATURA1 TO RAFA1   
  while(Mirf.isSending()){                         
  }
  Serial.println(TEMPERATURA1);                    // PRINT THE VALUE TEMPERATURA1 IN THE SERIAL 
  delay(10);                                       // DELAY 10 ms 
} 
  
  

