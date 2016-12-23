/*     GOBLIN2_LABVIEW_EXAMPLE1
  
  Send the value of the potentiometer for the serial port
  and we can see this value in one interface in LABVIEW.
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 15 Noviembre 2016
  by Rafael Cortés
  -GOBLIN 2 TEAM. VERSE Technology.
 */
 
#include <SoftwareSerial.h>                          // Library SoftwareSerial
SoftwareSerial SIM5320A(6, 4);                       // RX, TX. Configure the serial port in the SIM5320A for our GOBLIN 2

int POT = A0;                                        // Select the input pin for the potentiometer

void setup() {                        
  Serial.begin(9600);                                // Serial 9600
}

void loop() {
  int POT = analogRead(A0);                          // Read the value the potentiometer
  Serial.println(POT);                               // Print value the AD0 (This value we can see in the interface of LABVIEW)
  delay(100);                                        // Wait 100 mS
}

