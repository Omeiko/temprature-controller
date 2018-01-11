#include "math.h"
#include "Charliplexing.h"
#include "Myfont.h"
#include "Arduino.h"
#include "TaskScheduler.h"
#define SPEAKER 3


int BassTab[]={1911,1702,1516,1431,1275,1136,1012};//bass 1~7
const int B = 4275;   // B value of the thermistor
const int R0 = 100000;
float resistance;
int leng = 0;
unsigned char test[10]="00";

void setup() {
  Serial.begin(9600);
  pinInit();
  LedSign::Init();
    for(int i=0; ; i++){ //get the length of the text
    if(test[i]==0){
      leng=i;
      break;
    }
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(A3,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A1,INPUT);
  //Serial.println(getNowTemprature());
  sprintf(test,"%d",(int)getNowTemprature());
  //soundOfTemp(getNowTemprature());
  //int a=analogRead(A2);
  //Serial.println(a);
  digitalWrite(A2,0);
  pinMode(A3,INPUT);
  Myfont::Banner(leng,test);
  //Sch.dispatchTasks();

}

//function of get present temprature
float getNowTemprature() {
    int a = analogRead(A0);
    float R = 1023.0/a-1.0;
    R = R0*R;
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    Serial.print("temperature = ");
    Serial.println(temperature);
    delay(100);
    return temperature;
}
 

//function of speaker
void sound(uint8_t note_index)
{
    for(int i=0;i<100;i++)
    {
        digitalWrite(A3,HIGH);
        delayMicroseconds(BassTab[note_index]);
        digitalWrite(A3,LOW);
        delayMicroseconds(BassTab[note_index]);
    }
}

void soundOfTemp(float temp)
{
  if (temp < 27.0) {sound(1);digitalWrite(A2,LOW);}
  if (temp > 30.0) {sound(6);digitalWrite(A2,LOW);}
}

void pinInit()
{
    pinMode(A3,OUTPUT);
    digitalWrite(A3,LOW);
}
void printNowTemp()
{
    Myfont::Banner(leng,test);
}



//function
