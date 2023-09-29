#include <Stepper.h> 
  int Xspeed;
  int Xspeedmap1;
  int Xspeedmap2;
  int Yspeed;
  int Yspeedmap1;
  int Yspeedmap2;
  const int stepX=2;
  const int dirX=3;
   const int stepY=4;
  const int dirY=5;
   const int stepZ=6;
  const int dirZ=7;
   const int stepA=12;
  const int dirA=13;
  
  
void setup() {
  pinMode(stepX,OUTPUT);
  pinMode(dirX,OUTPUT);
  pinMode(stepY,OUTPUT);
  pinMode(dirY,OUTPUT);
  pinMode(stepZ,OUTPUT);
  pinMode(dirZ,OUTPUT);
  pinMode(stepA,OUTPUT);
  pinMode(dirA,OUTPUT);
  Serial.begin(9600);
  
}
void loop() {
  
Xspeed=analogRead(A0);
Xspeedmap1=map(Xspeed,0,1023,100,4000);
   Xspeedmap2=map(Xspeed,0,1023,4000,100);
   
   Yspeed=analogRead(A1);
Yspeedmap1=map(Yspeed,0,1023,40,4000);
   Yspeedmap2=map(Yspeed,0,1023,4000,40);
  
  if (Xspeed<510){
       digitalWrite(dirX,LOW);
       digitalWrite(stepX,LOW);  
       digitalWrite(stepX,HIGH);
       digitalWrite(dirY,HIGH);
       digitalWrite(stepY,LOW);  
       digitalWrite(stepY,HIGH);
       delayMicroseconds(Xspeedmap1);
  }
  if (Xspeed>530){
       digitalWrite(dirX,HIGH);
       digitalWrite(stepX,LOW);  
       digitalWrite(stepX,HIGH);
       digitalWrite(dirY,LOW);
       digitalWrite(stepY,LOW);  
       digitalWrite(stepY,HIGH);
       delayMicroseconds(Xspeedmap2);
      }

if (Yspeed<510){
       digitalWrite(dirZ,LOW);
       digitalWrite(stepZ,LOW);  
       digitalWrite(stepZ,HIGH);
       digitalWrite(dirA,HIGH);
       digitalWrite(stepA,LOW);  
       digitalWrite(stepA,HIGH);
       delayMicroseconds(Yspeedmap1);
      }

if (Yspeed>530){
       digitalWrite(dirZ,HIGH);
       digitalWrite(stepZ,LOW);  
       digitalWrite(stepZ,HIGH);
       digitalWrite(dirA,LOW);
       digitalWrite(stepA,LOW);  
       digitalWrite(stepA,HIGH);
       delayMicroseconds(Yspeedmap2);
      }

   
    }
     

  
  
