/*     PUSH_THE_BOTTON_AND_SEND_A_SMS_EXAMPLE1
  
  Send a SMS when you push the botton.
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 1 Noviembre 2016
  by Rafael Cortés
  -GOBLIN 2 TEAM. VERSE Technology.
 */
 
#include <SoftwareSerial.h>                          // Library SoftwareSerial
SoftwareSerial SIM5320A(6, 4);                       // RX, TX. Configure the serial port in the SIM5320A for our GOBLIN 2
int buttonPin = 12;                                  // Button
int Ledgoblin2 = 13;                                 // LED of Goblin 2

void setup(){ 
    SIM5320A.begin(9600);                            // Set serial port speed for SIM5320A
    SIM5320Apower();                                 // ON SIM5320A for software
    delay(10000);                                    // Time to find a RED (DEPENDS OF YOUR POSITION)
    pinMode(buttonPin, INPUT);                       // Pin the signal of button
    pinMode(Ledgoblin2, OUTPUT);                     // Pin the LED of Goblin 2
 }
 
void loop(){
 int reading = digitalRead(buttonPin);                // Read pin 12
  if(reading==HIGH)                                   // If you push the botton
  {
    digitalWrite(Ledgoblin2,HIGH);                    // Turn ON the the LED of GOBLIN 2
    delay(1500);                                      // Wait 1500 mS
    SMS();                                            // Function SMS
    }
    if(reading==LOW);                                 // If you don't push the botton
    {
    digitalWrite(Ledgoblin2,LOW);                     // LED OFF
   }
}

void SIM5320Apower(){                                 // Function for to turn ON the SIM5320A
  digitalWrite(5, HIGH);                              // This is the pin for to turn ON the SIM5320A for sofTtware
  delay(2000);                                        // Wait 2 seconds
  digitalWrite(5, LOW);                               // This is the pin for to turn OFF the SIM5320A for software
  delay(2000);                                        // Wait 2 seconds
}
 
void SMS(){
  SIM5320A.println("AT+CMGF=1");                      // Set GSM to text mode
  delay(1500);                                        // Wait 1500 mS
  SIM5320A.println("AT+CMGS=\"XXXXXXXXXX\"");         // Phone number to which you want to send sms, PUT THE CELLPHONE NUMBER IN THE XXXXXXXXXX 
  delay(1000);                                        // Wait 1000 mS
  SIM5320A.println("GOBLIN 2");                       // SMS body 
  delay(1000);                                        // Wait 1000 mS
  SIM5320A.write(0x1A);                               // Sends ctrl+z end of message 
}
 
