/*
  PUSH_THE_BUTTON_AND_CALL_EXAMPLE2
  
  Produces one call when you push the button.
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 29 October 2016
  by Rafael Cortés
  -GOBLIN 2 TEAM. VERSE Technology.
 */
 
#include <SoftwareSerial.h>                // Library SoftwareSerial
SoftwareSerial SIM5320A(6, 4);             // RX, TX. Configure the serial port in the SIM5320A for our GOBLIN 2
int buttonPin = 12;                        // Botton
int LEDGOBLIN2 = 13;                       // LED of Goblin 2

void setup(){ 
      SIM5320A.begin(9600);                // Set serial port speed for SIM5320A
      SIM5320Apower();                     // ON SIM5320A for software
      delay(10000);                        // Time to find a RED (DEPENDS OF YOUR POSITION)
      pinMode(LEDGOBLIN2, OUTPUT);         // initialize the LED pin as an output:
      pinMode(buttonPin, INPUT);           // initialize the pushbutton pin as an input:
   }
 
void loop(){
int reading = digitalRead(buttonPin);      // Read pin 12
 
  if(reading==HIGH){                       // If you push the button
    digitalWrite(LEDGOBLIN2,HIGH);         // Turn ON the the LED of GOBLIN 2
    call();                                // Function CALL
    }
    if(reading==LOW);                      // If you don't push the button
    {
      digitalWrite(LEDGOBLIN2,LOW);        // LED OFF
      }
        
}

void SIM5320Apower(){                      // Function for to turn ON the SIM5320A
  digitalWrite(5, HIGH);                   // This is the pin for to turn ON the SIM5320A for sofTtware
  delay(2000);                             // Wait 2 seconds
  digitalWrite(5, LOW);                    // This is the pin for to turn OFF the SIM5320A for software
  delay(2000);                             // Wait 2 seconds
}
 
void call(){
  SIM5320A.println("ATDXXXXXXXXXX;");      // This instruction makes the call, PUT THE CELLPHONE NUMBER IN THE XXXXXXXXXX 
  delay(100);                              // Wait 100 mS
  SIM5320A.println();                      // Time CALL
  delay(20000);                            // Wait 20 seconds
  SIM5320A.println("ATH");                 // This instruction it's for finish the call
  delay(100);                              // Wait 100 mS
}
