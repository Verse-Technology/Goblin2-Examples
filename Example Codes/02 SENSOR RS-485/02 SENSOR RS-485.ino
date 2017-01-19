/*     GOBLIN2_COMUNICATION RS-485

  Receive the information of the sensor for protocol RS-485.
  
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 20 December 2016
  by Antonio Reyes
  -GOBLIN 2 TEAM. VERSE Technology.
 */

#include <SoftwareSerial.h>                 // Library SoftwareSerial

char DATO_TEMP[10];                         // Gets the full 8-character sensor response
char TEMP[10];                              // It saves only 4 characters of the 8 characters given by the sensor 
SoftwareSerial RS485(8,7);                  //(RX=8,TX=7) Assign the serial by software

void setup() { 

   Serial.begin(9600);                        
   RS485.begin(9600);                       // Sensor transmission speed
   pinMode(8, INPUT);                       // RS-485 PIN
   pinMode(7, OUTPUT);                      // RS-485 PIN
   
}

void loop(){
   RS485.listen();
   RS485.print("#01");                      // Send # 01 to Serial by software (PIN7 and PIN8)
   RS485.write(0x0D);                       // Send "ENTER" (ascii = 13) after # 01 to get sensor response 
   delay(1000);                             // Delay
   while(RS485.available()>0){              // Detects the information or response back, by the sensor  
     for(int x=0;x<=7;x++){         
     DATO_TEMP[x]=RS485.read();             // Saves the sensor response in the variable DATO_TEMP 
                                 }
     for(int x=0;x<=7;x++){ 
     TEMP[x]=DATO_TEMP[x+4];  
                                 }                   
                                    
    if(DATO_TEMP[0] == '>'){
      
    Serial.print("\n");       
    Serial.print("DATO_TEMP=");              // Prints the string DATO_TEMP
    Serial.println(DATO_TEMP);  
    Serial.print("TEMP=");                   // Prints the string DATO_TEMP
    Serial.println(TEMP);
    }     
                                 }           // While   
}
 
