/* RECEIVER

   THIS PROGRAM RECEIVE THE VALUE THE TEMPERATURE OF THE SENSOR THE ARDUINO UNO
   FOR RADIOFRECUENCY AND THE GOBLIN 2 SENDS THE VALUE TO UBIDOTS.

  Hardware SPI.
  Pins shield:
  
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 * CE -> 9
 * CSN -> 10
 
  modified 26 Diciembre 2016
  by Rafael Cortés
  -GOBLIN 2 TEAM. VERSE Technology.

 */
 
#include <SoftwareSerial.h>                          // LIBRERY                                      
#include <SPI.h>                                     // LIBRERY
#include <Mirf.h>                                    // LIBRERY
#include <nRF24L01.h>                                // LIBRERY
#include <MirfHardwareSpiDriver.h>                   // LIBRERY

SoftwareSerial SIM5320(5, 4);                        // RX, TX
float dato[32];  

char    BUFFER_USART;                                                           // BUFFER RX 
String  token ="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";  // TOKEN UBIDOTS
String  id    ="XXXXXXXXXXXXXXXXXXXXXXXX";                                      // UBIDOTS VARIABLE ID 

void setup() { 
  pinMode(5, OUTPUT);                              // PIN ON SIM5320
  SIM5320.begin(9600);
  SIM5320_ON();                                    // ON SIM
  delay(10000);
  SETUP_SIM5320();                                 // BEGIN SIM5320
  Mirf.csnPin = 10;
  Mirf.cePin = 9;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"RAFA1");
  Mirf.payload =32;
  Mirf.channel = 100;
  Mirf.config();
}

void loop() {
 if(!Mirf.isSending() && Mirf.dataReady()){
      Mirf.getData((byte *) &dato);
}
  WEB();                                           // SEND JSON TO UBIDOTS
  delay(8000);                                     // SAMPLE TIME
}

ISR (USART_RX_vect)
{
  BUFFER_USART = UDR0;                             // READ THE BUFFER RX
}

void WEB()                                  
{
  int LONG_JSON = 15;
  int SEND = 238;

  SIM5320.println(F("AT+CIPOPEN=0,\"TCP\",\"things.ubidots.com\",80"));  
  delay(5000); 
  SIM5320.print("AT+CIPSEND=0,");  
  delay(50);
  SIM5320.println(SEND);  
  delay(600);
  SIM5320.print(F("POST /api/v1.6/variables/"));
  delay(50);
  SIM5320.print(id);
  delay(50);
  SIM5320.println(F("/values  HTTP/1.1"));
  delay(50);
  SIM5320.println(F("Content-Type: application/json"));
  delay(50);
  SIM5320.print(F("Content-Length:"));
  delay(50);
  SIM5320.println(LONG_JSON);
  delay(50);
  SIM5320.print(F("X-Auth-Token: "));
  delay(50);
  SIM5320.println(token);
  delay(50);
  SIM5320.println(F("Host: things.ubidots.com"));
  delay(50);
  SIM5320.println("");
  SIM5320.print("{\"value\":");
  delay(10);
  SIM5320.print(dato[0],2);
  delay(50);
  SIM5320.println("}");
  delay(50);
  SIM5320.write(0x1A);
  delay(5000);
  SIM5320.println(F("AT+CIPCLOSE=0"));
  delay(4000);
}

void SIM5320_ON()                                        // ON SIM5320
{
  digitalWrite(5, HIGH);
  delay(2000);                            
  digitalWrite(5, LOW);
  delay(2000);
}

void SETUP_SIM5320()
{
  SIM5320.println(F("AT+CFUN=1"));                       // SIM5320 WORKING WITH ALL THE FUNCTIONALITIES
  delay(250);
  SIM5320.println(F("AT+CNMP=2"));                       // AUTOMATIC MODE
  delay(250);
  SIM5320.println(F("AT+CVAUXV=61"));                    // VOLTAGE OUTPUT 3.0V
  delay(250);
  SIM5320.println(F("AT+CNBP=0x0000000004000000"));      // 3G 850MHZ TELCEL 0x0000000004000000 hspda, 2G 1900MHZ TELCEL AT+CNBP=0x0000000000200000 edge
  delay(500);
  SIM5320.println(F("AT+CSQ"));                          // SIGNAL LEVEL
  delay(250);
  SIM5320.println(F("AT+CREG?"));          
  delay(250);
  SIM5320.println(F("AT+COPS?"));
  delay(250);
  SIM5320.println(F("AT+CGSOCKCONT=1,\"IP\",\"internet.itelcel.com\""));
  delay(250);
  SIM5320.println(F("AT+CNSMOD?"));                       // RED
  delay(250);
  SIM5320.println(F("AT+CSOCKSETPN=1"));
  delay(250);
  SIM5320.println(F("AT+CIPMODE=0"));
  delay(250);
  SIM5320.println(F("AT+CNBP?"));
  delay(250);
  SIM5320.println(F("AT+NETOPEN"));
  delay(8000);
  SIM5320.println(F("AT+IPADDR"));                        // IP
  delay(500);
  SIM5320.println(F("AT+CGSN"));                          // IMEI
  delay(500);
}
