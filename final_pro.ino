#include "math.h"
#include "Charliplexing.h"
#include "Myfont.h"
#include "Arduino.h"
#include "TaskScheduler.h"
#define SPEAKER 3

int BassTab[]={1911,1702,1516,1431,1275,1136,1012};//bass 1~7
const int B = 3975;   // B value of the thermistor
float resistance;
int leng = 0;
unsigned char test[10]="00";

void setup() {
  Serial.begin(9600);
  
//  Sch.init();
//  Sch.addTask(getNowTemprature,0,1000,1);
//  Sch.addTask(soundOfTemp,20,500,1);
//  Sch.addTask(printNowTemp,30,500,1);
//  Sch.start();
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
  Serial.println(getNowTemprature());
  sprintf(test,"%d",(int)getNowTemprature());
  soundOfTemp(getNowTemprature());
  pinMode(A3,INPUT);
  Myfont::Banner(leng,test);
  //Sch.dispatchTasks();

}

//function of get present temprature
float getNowTemprature() {
  int tempInput = analogRead(A1);
  resistance=(float)(1023-tempInput)*10000/tempInput; //get the resistance of the sensor;
  float temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;
  Serial.print("Current temperature is ");
  Serial.println(temperature);
  Serial.println(tempInput);
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
  if (temp>11.0 && temp<12.0) sound(1);
  if (temp>12.0 && temp<15.0) sound(4);
  if (temp>15.0 && temp<20.0) sound(7);
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