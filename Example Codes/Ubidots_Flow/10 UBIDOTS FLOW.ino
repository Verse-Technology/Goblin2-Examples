/*     Ubidots_FLOW2
  
  This example shows an application where you can control the amount of liquid injection in milliliters from the WEB, 
  these values ​​are modified from the Internet with the UBIDOTS platform.
  
  Check more documentation and examples in http://www.verse-technology.com/goblin2/
 
  modified 20 February 2017.
  by Puxitron.
  -GOBLIN 2 TEAM. VERSE Technology.
 */
#include <SoftwareSerial.h> 
#include <Wire.h>                 
#include <LiquidCrystal_I2C.h>  
#include <avr/wdt.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
                         
SoftwareSerial SIM5320(6,4);                            // RX, TX
#define  Digitos   4
#define  Relevador 7

String   token ="xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";	 // Token ubidots
String   id    ="xxxxxxxxxxxxxxxxxxxxxxxx";		 // Id Corrosion
int      int_ubidots;                                    // Global variable

int long    MiliT  =0;
int long    Cflujo=0;                                    // Flow Meter
int long    MiliT2 =0;
//////////////////////////////////////
char    DATO_BATT[30];                    // Gets the entire string of 17 characters of the battery string 
char    BATT[5];                          // It saves only 2 characters of the 15 characters (of the corroding string) given by sensor 3
float   VBATT=0;
String  BAT_V;  
/////////////////////////////////////
int     I;
int     F;                                // Serial Records								 
int     X=0;                              // String position counter
int     Z;                                // Count parameter of BUFFER_RX array
boolean COPY;                             // Start copying
char    BUFFER_RX[90];                    // Main buffer where the strings that come from the SIM5320A
char    BUFFER_UDR0;                      // Where a character is stored at each rx interrupt
/////////////////////////////////////      
boolean   FLAG_RESPONSE=false;
int       RESPONSE_ZZ=-1;
int       RESPONSE;                  
char      RESPONSE_BUFFER[100]; 
int       UBIDOTS;                            
////////////////////////////////////

void setup() { 
  
/////////////////////////////////// 
SREG    =0x80;                                        
UCSR0B  =0x98;                                       
UCSR0C  =0x06;                                      
UBRR0H  =0x00;                                        
UBRR0L  =0x67;                                      // 67=9600  
///////////////////////////////////                        
   pinMode(Relevador,OUTPUT);                       // Output that activates the relay
   digitalWrite(Relevador,HIGH);                    // Keep the pin up

   lcd.begin(16,2);                                 
   lcd.clear();          //
   lcd.setCursor(4,0);
   lcd.print("GOBLIN2");  
   lcd.setCursor(1,1);
   lcd.print("mL. pump =");
   
   SIM5320_ON();                                    // ON SIM5320A
   SIM5320.begin(9600);                             // SERIAL SIM5320
   delay(12000);                                    // Delay
   SETUP_SIM5320();                                 // Configuration the SIM5320 
  
   pinMode(2,INPUT);                            
 
}


void loop() {
  

  Web();                                             //GET/POST ubidots
  Sf();                                   
 
}
////////////////////////////////////
ISR (USART_RX_vect)
{  
  ++X;                                                // Position counter
  BUFFER_UDR0=UDR0;                                   // Read the UDR0 record                  
  if(BUFFER_UDR0 == 10 || BUFFER_UDR0 == 13){         // Carriage return and line break
  --X;  
                                                  }
  
  if(COPY == true && X >= I && X <= F){
  Z++;                                                // BUFFER RX array position counter
  BUFFER_RX[Z]=BUFFER_UDR0;  

  if(X == F){
  COPY=false;
  X=0;                                                // Position counter
  Z=-1;                                               // Count parameter of BUFFER_RX array
  I=0;                                                // Start
  F=0;                                                // Final
               }//if 
                                        } //

  if(RESPONSE == 1 && BUFFER_UDR0 == '{'){
  UBIDOTS++;
     
  if(UBIDOTS == 4){
  FLAG_RESPONSE=true;
                      }

                                               }     
    
                    if(FLAG_RESPONSE == true){
                    RESPONSE_ZZ++;
                    RESPONSE_BUFFER[RESPONSE_ZZ]=BUFFER_UDR0;  
                                                   if(RESPONSE_BUFFER[RESPONSE_ZZ] == '}'){                                            
                                                   FLAG_RESPONSE=false;
                                                   RESPONSE_ZZ=-1;
                                                   RESPONSE=0;       
                                                   UBIDOTS=0;                
                                                                                              }
                                                                               

                                                                                            }//*/
                                        
  
  }

void Web()                                  
{
  String S_ubidots;
  char   Value_ubidots[10];
  int    Puntos=0;
  int    Response_while=0;
  int    Send=124;   //238
  int    Tcp=0;
  char   Cipopen[5];
  int    Cipopen_int;
  int    Close=0;
  boolean x=false;
   

  COPIA_SERIAL(1,70);
  SIM5320.println("AT+CIPOPEN=0,\"TCP\",\"things.ubidots.com\",80");  // things.ubidots.com
  
  while(Tcp <= 70){
  Tcp++;
  delay(500); 

  if (strcasestr(BUFFER_RX,"+CIPOPEN: 0,0")) { 
  break;                                                }

    if (strcasestr(BUFFER_RX,"+CIPOPEN: 0,1")) { 
  SIM5320_ON();
  software_Reboot();                                               
                                                          }
    if (strcasestr(BUFFER_RX,"+CIPOPEN: 0,2")) { 
  SIM5320_ON();
  software_Reboot();                                               
                                                          }   
    if (strcasestr(BUFFER_RX,"+CIPOPEN: 0,3")) { 
  SIM5320_ON();
  software_Reboot();                                               
                                                          }      
    if (strcasestr(BUFFER_RX,"+CIPOPEN: 0,4")) { 
  SIM5320_ON();
  software_Reboot();                                               
                                                          }                                                                                                                                                                 
  
    if (strcasestr(BUFFER_RX,"+CIPOPEN: 0,11")) { 
  SIM5320_ON();
  software_Reboot();                                               
                                                          }

                                                          
  if (Tcp == 50) {//timeout 
  software_Reboot(); 
  break; ;
                                     }                           
                                      
                                                                                } // while
                                      

  
  SIM5320.print("AT+CIPSEND=0,");  //
  delay(50);
  SIM5320.println(Send);  //
  delay(600);
  SIM5320.println("GET /api/v1.6/variables/586449587625420bc9556bba?token=sHUXf1ZMGphgNO37H5PF3Jxr2nMVhr HTTP/1.1"); //Accept: */* 
  delay(100);
  SIM5320.println("Host: things.ubidots.com");
  delay(100);
  SIM5320.println("");
  SIM5320.write(0x1A);
  
  RESPONSE_WEB();
  while (Response_while<=33) {
  Response_while++;                                               
  delay(1000);                                                                                                       
 
                                                            if (strcasestr(RESPONSE_BUFFER,"value")) { 
                                                            for(int w=0;w <= 89;w++){
                                                            if(RESPONSE_BUFFER[w] == ':'){
                                                            Puntos++;      
                                                                                                   }

                                                            if(Puntos == 2){
                                                            for(int z=0;z <= Digitos-1;z++){
                                                                if(RESPONSE_BUFFER[w+z+2] == '.'){
                                                                    RESPONSE_BUFFER[w+z+2]=0x00;
                                                                                                      }
                                                            Value_ubidots[z]=RESPONSE_BUFFER[w+z+2];  
                                                            
                                                                                                }
                                                            Puntos=-1;
                                                                                                    }                                        
                                                                                    
                                                                                    
                                                                                              }//for                                   
                                                            break;  
                                                                                                                 }//IF
//                                                  
                                                            if (Response_while == 30) {//timeout 
                                                            RESPONSE=0;
                                                                                                              }                                                                                                
                                                                      
                                                                 
                                                                                                                        } //WHILE*/
  S_ubidots=Value_ubidots;
  int_ubidots=S_ubidots.toInt();

  lcd.setCursor(11,1);
  lcd.print(int_ubidots); 
  lcd.print("     "); 
     
  SIM5320.println("AT+CIPCLOSE=0");    // Close the connection
  delay(1500);

}

void SIM5320_ON()                         
{
  digitalWrite(5, HIGH);
  delay(2000);                                                
  digitalWrite(5, LOW);                   // ON the SIM5320A
  delay(2000);
}
/////////////////////////////////////////////////////////////////////////////
void SETUP_SIM5320()
{

  SIM5320.println(F("AT+CFUN=1"));        // SIM5320 WORKING WITH ALL THE FEATURES
  delay(250);

  SIM5320.println(F("AT+CNMP=2"));        // AUTOMATIC MODE
  delay(250);

  SIM5320.println(F("AT+CVAUXV=61"));     // OUTPUT VOLTAGE 3.0V
  delay(250);

  SIM5320.println(F("AT+CNBP=0x0000000004000000"));  //3G 850MHZ TELCEL 0x0000000004000000 hspda     2G 1900MHZ TELCEL AT+CNBP=0x0000000000200000 edge
  delay(500);

  //SIM5320.println(F("AT+IPREX=9600"));
  //delay(4000);

  SIM5320.println(F("AT+CSQ"));            // SIGNAL LEVEL
  delay(250);

  SIM5320.println(F("AT+CREG?"));         
  delay(250);

  SIM5320.println(F("AT+COPS?"));
  delay(250);
 
  SIM5320.println(F("AT+CGSOCKCONT=1,\"IP\",\"internet.itelcel.com\""));
  delay(250);

  SIM5320.println(F("AT+CNSMOD?"));        // SAMPLE IN WHICH NETWORK IS WORKING
  delay(250);

  SIM5320.println(F("AT+CSOCKSETPN=1"));
  delay(250);

  SIM5320.println(F("AT+CIPMODE=0"));
  delay(250);

  SIM5320.println(F("AT+CNBP?"));
  delay(500);

  COPIA_SERIAL(13,25);
  SIM5320.println(F("AT+NETOPEN"));
  while(true){
  delay(100);  
  if (strcasestr(BUFFER_RX,"+NETOPEN: 0")) {
  break;  
                                                }



                                                        } //while

  SIM5320.println(F("AT+IPADDR"));          // IP
  delay(500);

  SIM5320.println(F("AT+CGSN"));            // IMEI
  delay(500);
}

////////////////////////////////////////////////////////////
void COPIA_SERIAL(int Inicio,int Final)        // Serial interrupt variables
{
  COPY=true;                                 
  X=0;
  Z=-1;
            for (int i=0; i<=89;i++){
                      BUFFER_RX[i]=NULL;}     // Clean the buffer rx
  I=Inicio; 
  F=Final;
    }
void RESPONSE_WEB()                              // 
{
  RESPONSE=1;
             for (int i=0; i<=99;i++){
                 RESPONSE_BUFFER[i]=NULL;}       //

              } 

void software_Reboot()
{
  wdt_enable(WDTO_500MS);
  while(1)
  {
  }
} 

void Sf(){
  
  attachInterrupt(digitalPinToInterrupt(2),Flow, RISING); 
  Cflujo=0; 
  MiliT=0;
while(true){    
  
  if(int_ubidots == MiliT2){ 
  break;  
                                        }
//  lcd.setCursor(12,0);
//  lcd.print(MiliT); 
//  lcd.print("     ");                                         

  MiliT=Cflujo*2.5;
  digitalWrite(Relevador,LOW);                                        
 
  if(int_ubidots <= MiliT){ 
  MiliT2=int_ubidots;
  digitalWrite(Relevador,HIGH);  
  MiliT=0;  
  break;                  
                                        } 
}                   
                     
 detachInterrupt(2);
}

void Flow(){       
Cflujo++;
              
    }
         
