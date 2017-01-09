/*     GOBLIN2_COMUNICATION RS-485

  Receive the information of the sensor for protocol RS-485.
  
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 20 December 2016
  by Antonio Reyes
  -GOBLIN 2 TEAM. VERSE Technology.
 */

#include <SoftwareSerial.h>                 // Library SoftwareSerial

char DATO_TEMP[8];                          // Gets the full 8-character sensor response
char TEMP[4];                               // It saves only 4 characters of the 8 characters given by the sensor 
int x=0;                                    // Count the positions of the string of 8 characters (you get one by one)

SoftwareSerial RS485(8,7);                  //(RX=8,TX=7) Assign the serial by software

void setup() { 

   Serial.begin(9600);                        
   RS485.begin(9600);                        // Sensor transmission speed
}

void loop() {

   delay(500);  
   RS485.write("#01");                       // Send # 01 to Serial by software (PIN7 and PIN8)
   RS485.write(13);                          // Send "ENTER" (ascii = 13) after # 01 to get sensor response  
 
   while(RS485.available()>0){               // Detects the information or response back, by the sensor  
     for(int x=0;x<8;x++){       
     
       DATO_TEMP[x]=RS485.read();            // Saves the sensor response in the variable DATO_TEMP 
       TEMP[0]=DATO_TEMP[4];                 // Save to position 0 of the TEMP string - the position 4 of the string DATO_TEMP
       TEMP[1]=DATO_TEMP[5];                 // Save to position 1 of the TEMP string - the position 5 of the string DATO_TEMP
       TEMP[2]=DATO_TEMP[6];                 // Save to position 2 of the TEMP string - the position 6 of the string DATO_TEMP  
       TEMP[3]=DATO_TEMP[7];                 // Save to position 3 of the TEMP string - the position 7 of the string DATO_TEMP
    
  }               
  
    if(DATO_TEMP[0] == '>'){
      
    Serial.print("\n");       
    Serial.print("DATO_TEMP = ");            // Prints the string DATO_TEMP
    Serial.println(DATO_TEMP);  
    Serial.print("TEMP = ");                 // Prints the string DATO_TEMP
    Serial.println(TEMP);
    }     
  }   
}
