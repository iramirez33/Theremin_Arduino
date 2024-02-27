/*                                                                                                                                                                                                                                                
 1 - Arduino pin ~9
 2 - Speaker +
 3 - GND
   4 - 5V
 5 - Arduino pin ~10
 6 - Arduino pin 13
 7 - Arduino pin ~11 
   8 - GND
*/

#include   <NewTone.h>
#include <NewPing.h>
#include <SPI.h>

#define MIN_DISTANCE   35 

NewPing sonar(5, 6, 35); 


byte   address = 0x00;
int CS= 10;

int echo = 3;                            
int   trigger = 4;

int distance;
int PotValue;

unsigned long TimeResponse;
float   distance2;
float tone1;

void setup() {
  Serial.begin(9600);   
  pinMode(trigger, OUTPUT);                     
  pinMode(echo,   INPUT);   
  pinMode (CS, OUTPUT);
  SPI.begin();

   
  digitalPotWrite(255);
   
  for (int i = 50; i <= 400; i++)
  {
    pinMode(9, OUTPUT);
    NewTone(9,i);
     delay(10);
  }
  
  delay(500);
  
  for (int i = 400; i >= 50;   i--)
  {
    pinMode(9, OUTPUT);
    NewTone(9,i);
    delay(10);
   } 
}

void loop() {  
  digitalWrite(trigger, HIGH);           
   delayMicroseconds(10);     
   digitalWrite(trigger, LOW);                   
  TimeResponse = pulseIn(echo,   HIGH);  
  distance2   = TimeResponse/58;  

  if (distance2   < MIN_DISTANCE) {  
     tone1 = 50.0*pow(2,(distance2/12.0));  
    pinMode(9, OUTPUT);
    NewTone(9,tone1);
  } else {
     pinMode(9, OUTPUT); 
    NewTone(9,0);
  }
 
  distance = sonar.ping_cm(); 

  
  int PotValue = map(distance, 0, 35, 240, 255);   

  if (distance == 0)
  {
    PotValue   = 255;
  }

  digitalPotWrite(PotValue);
  delay(10);  
}

int   digitalPotWrite(int value) {
  digitalWrite(CS, LOW); 
  SPI.transfer(address);
   SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
