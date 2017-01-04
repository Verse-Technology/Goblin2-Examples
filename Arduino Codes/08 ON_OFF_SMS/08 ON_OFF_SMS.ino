/*   SMS TURN ON/OFF THE LIGHT BULB

  SENDS SMS TO GOBLIN 2:
  
  "On" -> TURN ON THE LIGHT BULB
  "Off" -> TURN OFF THE LIGHT BULB
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 27 December 2016
  by Puxitron
  -GOBLIN 2 TEAM. VERSE Technology.
*/

#include <SoftwareSerial.h>             
SoftwareSerial SIM5320A(6, 4);
int LEDGOBLIN = 13; 

int     I;
int     F;                              // SERIAL RECORDS								 
int     X=0;                            // STRING PISITION COUNTER
int     Z;                              // BUFFER RX ARRAY POSITION COUNTER
boolean COPY;                           // BEGIN COPY
char    BUFFER_RX[100];                 // MAIN BUFFER WHERE THE STRINGS THAT COME FROM THE SIM5320A
char    BUFFER_UDR0;                    // BUFFER RX

void setup()
{
 
SREG    =0x80;                           // INT GLOBAL ONLY ACTIVATES THE UART
UCSR0B  =0x98;                           // ACTIVE TX & RX & INT RX
UCSR0C  =0x06;                           // CONFIGURE 8BITS OF SERIAL DATA
UBRR0H  =0x00;                           // VALUE THAT IS CHARGED TO REGISTRY HIGH 0
UBRR0L  =0x67;                           // VALUE CHARGED TO LOW REGISTRY 0x67 THAT IS EQUAL TO 103 FOR 9600
 
  pinMode(LEDGOBLIN, OUTPUT);
  digitalWrite(LEDGOBLIN, LOW);
  
  SIM5320Apower(); 
  SIM5320A.begin(9600);
  delay(10000);  
  SIM5320A.println("AT+CMGF=1");          // SET SMS MODE TEXT
  delay(1000);
  SIM5320A.println("AT+CNMI=2,2,0,0,0");  // CONTENTS OF NEW SMS UPON RECEIPT TO THE GSM
  delay(1000);
}
 
void SIM5320Apower(){
  digitalWrite(5, HIGH);
  delay(2000);
  digitalWrite(5, LOW);
  delay(2000);
}
 
void loop() 
{
int sms=0;  
COPIA_SERIAL(45,47);
while(sms < 100){
delay(100);
sms++;


    if(strcasestr(BUFFER_RX,"On")) { 
    digitalWrite(LEDGOBLIN,HIGH);
    sms=0;
    break;
                                                  
                                                  }
    if(strcasestr(BUFFER_RX,"Off")) { 
    digitalWrite(LEDGOBLIN,LOW);
    sms=0;
    break;
                                                  }                                                  


                }                  
}

///////////////////////////////////////////////////////////////////////////
ISR (USART_RX_vect)
{  
  ++X;                                          // POSITION COUNTER
  BUFFER_UDR0=UDR0;                             // READ UDR0                    
  if(BUFFER_UDR0 == 10 || BUFFER_UDR0 == 13){   // CARRIAGE RETURN AND LINE BREAK
  --X;  
                                            }
  
  if(COPY == true && X >= I && X <= F){
  Z++;                                          // POSITION COUNTER ARRAY BUFFER_RX
  BUFFER_RX[Z]=BUFFER_UDR0;  

  if(X == F){
  COPY=false;
  X=0;                                          // POSITION COUNTER
  Z=-1;                                         // POSITION COUNTER ARRAY BUFFER_RX
  I=0;                                          // BEGIN
  F=0;                                          // FINAL
               }
                                       } 
  
}


void COPIA_SERIAL(int Inicio,int Final)         // VARIABLE INTERRUPTION SERIAL
{
  COPY=true;                                 
  X=0;
  Z=-1;
            for (int i=0; i<=99;i++){
                      BUFFER_RX[i]=NULL;}       // CLEAN BUFFER RX
  I=Inicio; 
  F=Final;
}

