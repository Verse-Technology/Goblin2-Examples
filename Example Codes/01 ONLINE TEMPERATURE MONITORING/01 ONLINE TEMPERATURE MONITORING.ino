/*     EXAMPLE_UBIDOTS

  Receive the information of the sensor for protocol RS-485.
  
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 15 December 2016
  by Jorge Guillen
  -GOBLIN 2 TEAM. VERSE Technology.
 */

#include <SoftwareSerial.h>                           
#include <OneWire.h>
#include <DallasTemperature.h>

SoftwareSerial SIM5320(5, 4);                                                   //RX, TX
#define ONE_WIRE_BUS 10                                                         //PIN DS18B20


char    BUFFER_USART;                                                           //BUFFER RX 
String  token ="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";  //TOKEN UBIDOTS
String  id    ="xxxxxxxxxxxxxxxxxxxxxxxx";                                      //ID VARIABLE UBIDOTS 


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() { 
  pinMode(5, OUTPUT);                              //PIN ON SIM5320
  SIM5320.begin(9600);
  SIM5320_ON();                                    //ON SIM5320
  delay(10000);
  SETUP_SIM5320();                                 //START SIM5320
  sensors.begin();                                 
}


void loop() {

  WEB();                                           //SEND JSON UBIDOTS
  delay(15000);                                    //SAMPLE TIME
  


}
///////////////////////////////////////////////////////////////////////////
ISR (USART_RX_vect)
{
  BUFFER_USART = UDR0;                               // READ THE BUFFER RX
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WEB()                                  
{
  int LONG_JSON = 15;
  int SEND = 209;
    
  sensors.requestTemperatures(); 
  float temp = sensors.getTempCByIndex(0); 

  SIM5320.println(F("AT+CIPOPEN=0,\"TCP\",\"things.ubidots.com\",80"));  //
  delay(5000);
  
  SIM5320.print("AT+CIPSEND=0,");  //
  delay(50);
  SIM5320.println(SEND);  //
  delay(600);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
  ///////////////////////////////////////////////////////////////
  SIM5320.print("{\"value\":");
  delay(10);
  SIM5320.print(temp,2);
  delay(50);
  SIM5320.println("}");
  delay(50);
  SIM5320.write(0x1A);
  delay(5000);
  SIM5320.println(F("AT+CIPCLOSE=0"));
  delay(4000);

}

void SIM5320_ON()          
{
  digitalWrite(5, HIGH);
  delay(2000);//                            
  digitalWrite(5, LOW);
  delay(2000);
}
/////////////////////////////////////////////////////////////////////////////
void SETUP_SIM5320()
{
  SIM5320.println(F("AT+CFUN=1"));                      //SIM5320 WORKING WITH ALL THE FEATURES
  delay(250);

  SIM5320.println(F("AT+CNMP=2"));                      //AUTOMATIC MODE
  delay(250);

  SIM5320.println(F("AT+CVAUXV=61"));                   //3.0V OUTPUT VOLTAGE
  delay(250);

  SIM5320.println(F("AT+CNBP=0x0000000004000000"));     //3G 850MHZ TELCEL 0x0000000004000000 hspda     2G 1900MHZ TELCEL AT+CNBP=0x0000000000200000 edge
  delay(500);

  SIM5320.println(F("AT+CSQ"));                         //SIGNAL LEVEL
  delay(250);

  SIM5320.println(F("AT+CREG?"));          
  delay(250);

  SIM5320.println(F("AT+COPS?"));
  delay(250);
 
  SIM5320.println(F("AT+CGSOCKCONT=1,\"IP\",\"internet.itelcel.com\""));
  delay(250);

  SIM5320.println(F("AT+CNSMOD?"));                     //MUESTRA EN QUE RED ESTA TRABAJANDO
  delay(250);

  SIM5320.println(F("AT+CSOCKSETPN=1"));
  delay(250);

  SIM5320.println(F("AT+CIPMODE=0"));
  delay(250);

  SIM5320.println(F("AT+CNBP?"));
  delay(250);

  SIM5320.println(F("AT+NETOPEN"));
  delay(8000);

  SIM5320.println(F("AT+IPADDR"));                       //IP
  delay(500);

  SIM5320.println(F("AT+CGSN"));                         //IMEI
  delay(500);
}
