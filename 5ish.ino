#include "PinChangeInterrupt.h"
int xPin = A1;
int yPin = A0;
int buttonPin = 13;

int xPosition = 0;
int yPosition = 0;
int buttonState = 1;

long debouncing_time = 20; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
volatile unsigned long micros_main;
volatile unsigned long last_main_time_R=0;
volatile unsigned long last_main_time_Z=0;
volatile unsigned long last_main_micros_Y=0;
volatile unsigned long last_time;
const int Rmotor1 = 2; // the one pin of the motor attach to pin 9
const int Rmotor2 = 3; // the another pin of the motor attach to pin 10
const int Ymotor1=4;
const int Ymotor2=5;
const int Zmotor1=6;
const int Zmotor2=7;
const int Ypulse=8;
const int Ylimit=9;
const int Gmotor1=10;
const int Gmotor2=11;
const int Zlimit=16;
const int Gpulse=19;
const int Zpulse=18;
const int Rpulse=17;
const int Rlimit=12;
int R_sum;
int last_R_sum;
int Z_sum;
int last_Z_sum;
int Y_sum;
int last_Y_sum;
int all_times[56];
int all_times_Z[31];
char slider[3];
volatile unsigned long average;
volatile unsigned long average2=0;
volatile unsigned long averageZ2=0;
int del_count;
int del_count2=0;
volatile int Ypos =0; 
int i;
int x=0;
int x2=0;
int x3=0;
int x4=0;
int xb4=0;
volatile int sum=0;
volatile int Ypul;
int Ylim;
int Rlim;
int Zlim;
String ReadString;
String servo1;
int n1;
/***************************************/
void setup()
{
pinMode(Rmotor1,OUTPUT); //initialize the motorIn1 pin as output 
pinMode(Rmotor2,OUTPUT); //initialize the motorIn2 pin as output 
pinMode(Ymotor1,OUTPUT);
pinMode(Ymotor2,OUTPUT);
pinMode(Zmotor1,OUTPUT);
pinMode(Zmotor2,OUTPUT);
pinMode(Gmotor1,OUTPUT);
pinMode(Gmotor2,OUTPUT);
digitalWrite(Rmotor1,HIGH);
digitalWrite(Rmotor2,HIGH);
digitalWrite(Ymotor1,HIGH);
digitalWrite(Ymotor2,HIGH);
digitalWrite(Zmotor1,HIGH);
digitalWrite(Zmotor2,HIGH);
digitalWrite(Gmotor1,HIGH);
digitalWrite(Gmotor2,HIGH);  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(Zlimit,INPUT);
  pinMode(Rpulse,INPUT);
  pinMode(Zpulse,INPUT);
  pinMode(Gpulse,INPUT);
  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP);
  //attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(Rpulse), print_things, RISING);
  //attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(Ymotor1), Yposplus, RISING);
  //attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(Ymotor2), Yposmin, RISING);
Serial.begin(9600);
INIT();
}





int treatValue(int data)
{
  return (data * 9/1024)+48;
}
/****************************************/
void serialEvent() // A function that listens to an serial data being sent
{                  // Doesn't need to be called in the loop() function
   while(Serial.available()) // Checks if serial data is available 
   {
    delay(10);  // to avoid any discrepencies
   if (Serial.available() >0) { //Check if serial data is bigger than zero
                                // avoiding any null objects
     char c = Serial.read();  //gets one byte(one char) from serial buffer
     if(isalpha(c)||isDigit(c)) //Check if data is an alphabet or a digit
     {
     ReadString += c; //append the character to a string variable
     }                // Variable used in Serial_test_2() func.
   } 
   }
}


void loop()
{
//clockwise(Ymotor1,Ymotor2); //rotate clockwise 
//delay(100); //wait for a second

Serial_test_2();
//Serial.println(Ylim);
buttonState=digitalRead(buttonPin);  // Check the button state 71,104,193  
  if(buttonState==0)
  {
    INIT();
    RmotMove(71);
    delay(100);
    ZmotMove(170);
    delay(100);
    clockwise(Gmotor1,Gmotor2);
    delay(1000);
    Stop(Gmotor1,Gmotor2);
    delay(100);
    YmotMove(104);
    delay(100);
    counterClockwise(Gmotor1,Gmotor2);
    delay(1200);
    Stop(Gmotor1,Gmotor2);
    delay(100);
    YmotMove(60);
    delay(100);
    RmotMove(10);
    delay(100);
    ZmotMove(420);
    delay(100);
    clockwise(Gmotor1,Gmotor2);
    delay(1000);
    Stop(Gmotor1,Gmotor2);
    delay(100);

    ZmotMove(330);
    delay(100);
    clockwise(Gmotor1,Gmotor2);
    delay(1000);
    Stop(Gmotor1,Gmotor2);
    delay(100);
    RmotMove(71);
    delay(100);
    ZmotMove(365);
    delay(100);
    YmotMove(104);
    delay(100);
    counterClockwise(Gmotor1,Gmotor2);
    delay(1200);
    YmotMove(64);
    delay(100);
    ZmotMove(330);
    delay(100);
    RmotMove(10);
    delay(100);
    YmotMove(54);
    delay(100);
    ZmotMove(350);
    delay(100);
    clockwise(Gmotor1,Gmotor2);
    delay(1000);
    ZmotMove(200);
    delay(100);
    
  }

joystick();  
  
}


///////////             GOOOOOOOOOOOOOOOOOOOOOOOOOOOO


void test_func(){
  buttonState=digitalRead(buttonPin);  // Check the button state
  if(buttonState==0)
  {
    INIT();
  ZmotMove(50);
  Z_sum=last_Z_sum+14+(last_Z_sum/5);
  Serial.println("             WE               ARE             DOING       A         WINGY");
   micros_main=micros(); // time from the initilisation position of the robot 
Serial.print("begin");
Serial.print("begin");
Serial.println(micros()-micros_main); 
last_main_time_Z=0; 
while((sum<Z_sum)&&((last_main_time_Z/Z_sum)<19.575))
{
last_micros=micros(); // time the loop takes, updates every loop
clockwise(Zmotor1,Zmotor2); 
x=digitalRead(Zpulse);   // Checking the status of the pulse every 2-3 miliseconds in order to make sure the pulse is actually high
delay(2);
x2=digitalRead(Zpulse);  // pulse taken second time
//delay(2);
//x3=digitalRead(Zpulse); // pulse taken third time
//delay(3);
//x4=digitalRead(Zpulse); // pulse taken fourth time
if(x==x2)  //&&(x2==x3)&&(x3==x4))
{
sum=sum+x; // If the pulse status is the same within the small duration (i.e. 7 mmilisecs)
           // sum is incremented by 'x' (i.e. by 1 if x is one and 0 if x is 0)
}
last_time=micros()-last_micros; 
Serial.print("last micros:      ");
average=average/del_count2;
last_main_time_Z=(micros()-micros_main)/1000;
Serial.println(last_time);
average=average+last_time;
del_count++;
last_main_time_Z=(micros()-micros_main)/1000;
}
Serial.print("Average time =  ");
Serial.print(average);
Serial.print("  |  Micros Final    ");
Serial.print(micros()-last_micros);
Serial.print("   |     Micros main final:   ");
Serial.println(last_main_time_Z);
del_count=0;
average=0;
averageZ2=averageZ2+last_main_time_Z;
del_count2++;
Serial.print("Average2:   ");
Serial.print(averageZ2);
Serial.print(" | Final Average   :  ");
Serial.println(averageZ2/del_count2);
all_times_Z[Z_sum]=averageZ2/del_count2;
Stop(Zmotor1,Zmotor2);
sum=0;
  }
}


////////////////////////////////////////////                                                                       GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG




void INIT(){
  Rlim=digitalRead(Rlimit);
  Zlim=digitalRead(Zlimit);  
  Ylim=digitalRead(Ylimit);
while(Ylim!=0)
{
  Ylim=digitalRead(Ylimit);
  counterClockwise(Ymotor1,Ymotor2);
}
while(Zlim!=1)
{
  Zlim=digitalRead(Zlimit);
  clockwise(Zmotor1,Zmotor2);
}
while(Rlim!=0)
{
  Rlim=digitalRead(Rlimit);
  clockwise(Rmotor1,Rmotor2);
  last_R_sum=0;
}
Stop(Rmotor1,Rmotor2);
  
}

void button_test()
{
    micros_main=micros(); // time from the initilisation position of the robot 
    Serial.print("begin");
    Serial.print("begin");
    Serial.println(micros()-micros_main); 
    last_main_micros_Y=0; 
    while(sum<Y_sum)         //&&((last_main_micros_Y/Y_sum)<19.575))
    {
      last_micros=micros(); // time the loop takes, updates every loop
      counterClockwise(Ymotor1,Ymotor2); 
      x=digitalRead(Ypulse);   // Checking the status of the pulse every 2-3 miliseconds in order to make sure the pulse is actually high
      delay(2);
      x2=digitalRead(Ypulse);  // pulse taken second time
      //delay(2);
      //x3=digitalRead(Zpulse); // pulse taken third time
      //delay(3);
      //x4=digitalRead(Zpulse); // pulse taken fourth time
      if(x==x2)  //&&(x2==x3)&&(x3==x4))
      {
          sum=sum+x; // If the pulse status is the same within the small duration (i.e. 7 mmilisecs)
                     // sum is incremented by 'x' (i.e. by 1 if x is one and 0 if x is 0)
      }
      last_time=micros()-last_micros; 
      Serial.print("last micros:      ");
      Serial.println(last_time);
      average=average+last_time;
      del_count++;
      last_main_micros_Y=(micros()-micros_main)/1000;
    }
    average=average/del_count2;
    last_main_micros_Y=(micros()-micros_main)/1000;
    Serial.print("Average time =  ");
    Serial.print(average);
    Serial.print("  |  Micros Final    ");
    Serial.print(micros()-last_micros);
    Serial.print("   |     Micros main final:   ");
    Serial.println(last_main_micros_Y);
    del_count=0;
    average=0;
    averageZ2=averageZ2+last_main_micros_Y;
    del_count2++;
    Serial.print("Average2:   ");
    Serial.print(averageZ2);
    Serial.print(" | Final Average   :  ");
    Serial.println(averageZ2/del_count2);
    all_times_Z[Y_sum]=averageZ2/del_count2;
    Stop(Zmotor1,Zmotor2);
    Serial.print("all time Z :");
    for(int i=0;i<=Y_sum;i++)
    {
      Serial.print(Y_sum);
      Serial.print(":  ");
      Serial.print(all_times_Z[i]);
      Serial.print(" |  ");
      if(i/5==0)
      {
        Serial.println("");
      }
    }
    sum=0;
}
/*void joystick_button()
{
  buttonState=digitalRead(buttonPin);  // Check the button state
if(buttonState==0)
{
  Rlim=digitalRead(Rlimit);
  Zlim=digitalRead(Zlimit);  
  Ylim=digitalRead(Ylimit);
while(Ylim!=0)
{
  Ylim=digitalRead(Ylimit);
  counterClockwise(Ymotor1,Ymotor2);
}
while(Zlim!=1)
{
  Zlim=digitalRead(Zlimit);
  clockwise(Zmotor1,Zmotor2);
}
while(Rlim!=0)
{
  Rlim=digitalRead(Rlimit);
  clockwise(Rmotor1,Rmotor2);
  last_R_sum=R_sum;
}
Stop(Rmotor1,Rmotor2);


RmotMove(90);
ZmotMove(175);//BREAKING POINT

clockwise(Gmotor1,Gmotor2);
delay(1000);

YmotMove(2900,'C');

delay(1000);
counterClockwise(Gmotor1,Gmotor2);
delay(1300);

YmotMove(5900,'O');
ZmotMove(200);


YmotMove(3500,'C');
clockwise(Gmotor1,Gmotor2);
delay(1000);

}
}*/
void joystick()
{
  xPosition = treatValue(analogRead(xPin)); //Read the X-value of the joystick
  yPosition = treatValue(analogRead(yPin)); //Read the Y-value of the joystick
  //  Value set to 48 to 56 using treatValue function


  if((yPosition==52)&&(xPosition==52)) // Joystick's default position, Stop all motors  
  {
    Stop(Ymotor1,Ymotor2);
    Stop(Zmotor1,Zmotor2);
    Stop(Rmotor1,Rmotor2);
    Stop(Gmotor1,Gmotor2);
  }
  else if((yPosition==56)&&(xPosition==52)){
    counterClockwise(Ymotor1,Ymotor2); // Y motor counter-clockwise
  }
  else if((yPosition==48)&&(xPosition==52))
  {
    clockwise(Ymotor1,Ymotor2); // Y motor clockwise
  }
  else if((xPosition==56)&&(yPosition==52)){
    counterClockwise(Zmotor1,Zmotor2); // Z motor counter-clockwise
  }
  else if((xPosition==48)&&(yPosition==52))
  {
    clockwise(Zmotor1,Zmotor2); // Z motor clockwise
  }
  else if((xPosition==48)&&(yPosition==56)){ // R motor counter-clockwise
    counterClockwise(Rmotor1,Rmotor2);
  }
  else if((xPosition==48)&&(yPosition==48))
  { // R motor clockwise
    clockwise(Rmotor1,Rmotor2); //open
  }
  else if((xPosition==56)&&(yPosition==56)){ // Grip close
    counterClockwise(Gmotor1,Gmotor2); //close
  }
  else if((xPosition==56)&&(yPosition==48)) // Grip open
  {
    clockwise(Gmotor1,Gmotor2);
  }
}
void clockwise(int pin1,int pin2) //Takes in the pin numbers
{
  digitalWrite(pin2,HIGH);//Set relay-2n to normally closed- connected to GND
  digitalWrite(pin1,LOW); //Set relay-1n to normally open- connected to 9V
}
void counterClockwise(int pin1,int pin2)
{
  digitalWrite(pin1,HIGH);  //Set relay-1n to normally closed- connected to GND
  digitalWrite(pin2,LOW); //Set relay-2n to normally open- connected to 9V
}
void Stop(int pin1,int pin2)
{
  digitalWrite(pin1,HIGH);//Set relay-1n to normally closed- connected to GND
  digitalWrite(pin2,HIGH);//Set relay-2n to normally closed- connected to GND
}

void Yposplus(){
  sum=sum+!Ypul;
  Ypos++;
  Serial.print("sum :     ");
  Serial.print(sum);
  Serial.print("   |     Ypos :    ");
  Serial.println(Ypos);
}
void Yposmin(){
  sum=sum-!Ypul;
  Ypos--;
  Serial.print("sum :     ");
  Serial.print(sum);
  Serial.print("   |     Ypos :    ");
  Serial.println(Ypos);
}

void RmotMove(int R_sum){
int sign=R_sum-last_R_sum;
last_R_sum=R_sum;
R_sum=abs(sign);
micros_main=micros(); // time from the initilisation position of the robot 
Serial.print("begin");
Serial.println(micros()-micros_main); 
last_main_time_R=0; 
while((sum<R_sum)&&((last_main_time_R/R_sum)<34.56))
{
  if(sign<0)
  {
    clPulsing(Rmotor1,Rmotor2);
  }
  else
  {
    counterclPulsing(Rmotor1,Rmotor2);
  }
}
average=average/del_count;
last_main_time_R=(micros()-micros_main)/1000;
Serial.print("Average time =  ");
Serial.print(average);
Serial.print("  |  Micros Final    ");
Serial.print(micros()-last_micros);
Serial.print("   |     Micros main final:   ");
Serial.println(last_main_time_R);
del_count=0;
average=0;
average2=average2+last_main_time_R;
del_count2++;
Serial.print("Average2:   ");
Serial.print(average2);
Serial.print(" | Final Average   :  ");
Serial.println(average2/del_count2);
all_times[R_sum]=average2/del_count2;
Stop(Rmotor1,Rmotor2);
sum=0;
}

void ZmotMove(int Z_sum){
  int sign=Z_sum-last_Z_sum; // positive or negative decides the direction
  last_Z_sum=Z_sum; // Stores the orovided Z_sum value for later use
  Z_sum=abs(sign); //Sets Z-sum as the difference of provided(Z_sum)& last(Z_sum)
  if(sign<0) //Checks the direction to move to (i.e. UP/DOWN)
  { //If direction is UP, adds a value to Z_sum as work is done against gravity
    // So Z_sum value for UP and DOWN deviates
    Z_sum=Z_sum+14+(Z_sum/6);
  }
  micros_main=micros(); // time from the initilisation position of the robot 
Serial.print("begin");
Serial.print("begin");
Serial.println(micros()-micros_main); 
last_main_time_Z=0; 
while((sum<Z_sum)&&((last_main_time_Z/Z_sum)<19.575))
{
  last_micros=micros(); // time the loop takes, updates every loop
if(sign<0) // Positive or negative value decides the direction
{
  clockwise(Zmotor1,Zmotor2); 
}
else
{
 counterClockwise(Zmotor1,Zmotor2);  
}
x=digitalRead(Zpulse);   // Checking the status of the pulse every 2-3 
                  //miliseconds in order to make sure the pulse is actually high
delay(2);
x2=digitalRead(Zpulse);  // pulse taken second time
if(x==x2)  //&&(x2==x3)&&(x3==x4))
{
sum=sum+x; // If the pulse status is the same within the small duration (i.e. 7 mmilisecs)
           // sum is incremented by 'x' (i.e. by 1 if x is one and 0 if x is 0)
}
last_time=micros()-last_micros; 
Serial.print("last micros:      ");
Serial.println(last_time);
average=average+last_time;
del_count++;
last_main_time_Z=(micros()-micros_main)/1000;
}
average=average/del_count2;
last_main_time_Z=(micros()-micros_main)/1000;
Serial.print("Average time =  ");
Serial.print(average);
Serial.print("  |  Micros Final    ");
Serial.print(micros()-last_micros);
Serial.print("   |     Micros main final:   ");
Serial.println(last_main_time_Z);
del_count=0;
average=0;
averageZ2=averageZ2+last_main_time_Z;
del_count2++;
Serial.print("Average2:   ");
Serial.print(averageZ2);
Serial.print(" | Final Average   :  ");
Serial.println(averageZ2/del_count2);
all_times_Z[Z_sum]=averageZ2/del_count2;
Stop(Zmotor1,Zmotor2);
sum=0;
}
void YmotMove(int Y_sum)
{
  float divider=52.53;
  int sign=Y_sum-last_Y_sum;
  last_Y_sum=Y_sum;
  Y_sum=abs(sign);
  if(sign<0)
  {
    Y_sum=Y_sum+5;
    divider=57.44;
  }
 micros_main=micros(); // time from the initilisation position of the robot 
    Serial.print("begin");
    Serial.print("begin");
    Serial.println(micros()-micros_main); 
    last_main_micros_Y=0; 
    while((sum<Y_sum)&&((last_main_micros_Y/Y_sum)<divider))
    {
      last_micros=micros(); // time the loop takes, updates every loop
      if(sign<0)
      {
        counterClockwise(Ymotor1,Ymotor2);
      }
      else
      {
        clockwise(Ymotor1,Ymotor2); 
      }
      x=digitalRead(Ypulse);   // Checking the status of the pulse every 2-3 miliseconds in order to make sure the pulse is actually high
      delay(2);
      x2=digitalRead(Ypulse);  // pulse taken second time
      //delay(2);
      //x3=digitalRead(Zpulse); // pulse taken third time
      //delay(3);
      //x4=digitalRead(Zpulse); // pulse taken fourth time
      if(x==x2)  //&&(x2==x3)&&(x3==x4))
      {
          sum=sum+x; // If the pulse status is the same within the small duration (i.e. 7 mmilisecs)
                     // sum is incremented by 'x' (i.e. by 1 if x is one and 0 if x is 0)
      }
      last_time=micros()-last_micros; 
      Serial.print("last micros:      ");
      Serial.println(last_time);
      average=average+last_time;
      del_count++;
      last_main_micros_Y=(micros()-micros_main)/1000;
    }
    average=average/del_count2;
    last_main_micros_Y=(micros()-micros_main)/1000;
    Serial.print("Average time =  ");
    Serial.print(average);
    Serial.print("  |  Micros Final    ");
    Serial.print(micros()-last_micros);
    Serial.print("   |     Micros main final:   ");
    Serial.println(last_main_micros_Y);
    del_count=0;
    average=0;
    averageZ2=averageZ2+last_main_micros_Y;
    del_count2++;
    Serial.print("Average2:   ");
    Serial.print(averageZ2);
    Serial.print(" | Final Average   :  ");
    Serial.println(averageZ2/del_count2);
    all_times_Z[Y_sum]=averageZ2/del_count2;
    Stop(Ymotor1,Ymotor2);
    Serial.print("all time Z :");
    for(int i=0;i<=Y_sum;i++)
    {
      Serial.print(Y_sum);
      Serial.print(":  ");
      Serial.print(all_times_Z[i]);
      Serial.print(" |  ");
      if(i/5==0)
      {
        Serial.println("");
      }
    }
    sum=0;

}

void counterclPulsing(int a,int b)
{
last_micros=micros(); // time the loop takes, updates every loop
counterClockwise(a,b); 
x=digitalRead(Rpulse);   // Checking the status of the pulse every 2-3 miliseconds in order to make sure the pulse is actually high
delay(2);
x2=digitalRead(Rpulse);  // pulse taken second time
delay(2);
x3=digitalRead(Rpulse); // pulse taken third time
delay(3);
x4=digitalRead(Rpulse); // pulse taken fourth time
if((x==x2)&&(x2==x3)&&(x3==x4))
{
sum=sum+x; // If the pulse status is the same within the small duration (i.e. 7 mmilisecs)
           // sum is incremented by 'x' (i.e. by 1 if x is one and 0 if x is 0)
}
last_time=micros()-last_micros; 
Serial.print("last micros:      ");
Serial.println(last_time);
average=average+last_time;
del_count++;
last_main_time_R=(micros()-micros_main)/1000;
}

void clPulsing(int a,int b)
{
last_micros=micros(); // time the loop takes, updates every loop
clockwise(a,b); 
x=digitalRead(Rpulse);   // Checking the status of the pulse every 2-3 miliseconds in order to make sure the pulse is actually high
delay(2);
x2=digitalRead(Rpulse);  // pulse taken second time
delay(2);
x3=digitalRead(Rpulse); // pulse taken third time
delay(3);
x4=digitalRead(Rpulse); // pulse taken fourth time
if((x==x2)&&(x2==x3)&&(x3==x4))
{
sum=sum+x; // If the pulse status is the same within the small duration (i.e. 7 mmilisecs)
           // sum is incremented by 'x' (i.e. by 1 if x is one and 0 if x is 0)
}
last_time=micros()-last_micros; // time taken for every loop
Serial.print("last micros:      ");
Serial.println(last_time);
average=average+last_time;
del_count++;
last_main_time_R=(micros()-micros_main)/1000; // total time take for a given value of Z_sum
}

void Serial_test_R()
{
  String servo1;
  Ylim=digitalRead(Ylimit);
Rlim=digitalRead(Rlimit);
Zlim=digitalRead(Zlimit);
x=digitalRead(Rpulse);
Serial.println(ReadString[0]);
if(ReadString.length()>0)
{
  if(ReadString[0]=='a')
  {
  servo1=ReadString.substring(1,ReadString.length());
  char carray1[ReadString.length()-1]; //magic needed to convert string to a number 
  Serial.print("printing out the servo1");
  Serial.println(servo1);
  servo1.toCharArray(carray1, sizeof(carray1)+1);
  Serial.print("Printing out the carray1");
  Serial.println(carray1[2]);
  n1 = atoi(carray1);
  Serial.print("printing out the n1");
  Serial.println(n1);
  RmotMove(n1);
  }
  else if(ReadString[0]=='b')
  {
     servo1=ReadString.substring(1,ReadString.length());
    char carray1[ReadString.length()-1]; //magic needed to convert string to a number 
      Serial.print("printing out the servo1");
      Serial.println(servo1);
       servo1.toCharArray(carray1, sizeof(carray1)+1);
        Serial.print("Printing out the carray1");
         Serial.println(carray1[2]);
         n1 = atoi(carray1);
         Serial.print("printing out the n1");
         Serial.println(n1);
    ZmotMove(n1);
  }
}
ReadString="";
}
//2607

void Serial_test_2()
{
  String servo2;
  String servo1;
  String servo3;
  int n2;
  int n3;
if(ReadString.length()>0)
{
  if(ReadString.length()==2)
  {
    int a;
    Serial.println(ReadString[1]);
    switch(ReadString[0])
    {
      case 'R':
         Move_a_bit(Rmotor1,Rmotor2);
      break;

      case 'Z':
        Move_a_bit(Zmotor1,Zmotor2);
      break;

      case 'Y':
        Move_a_bit(Ymotor1,Ymotor2);
        break;

      case 'G':
        Move_a_bit(Gmotor1,Gmotor2);
        break;
    }
  }
else
  {
  if(ReadString.length()<=11)
  {
  if((ReadString[3]=='b')&&(ReadString[7]=='c'))
  {
  servo1=ReadString.substring(1,3);
  servo2=ReadString.substring(4,7);
  servo3=ReadString.substring(8,ReadString.length());
  char carray1[2]; //magic needed to convert string to a number 
  char carray2[3];
  char carray3[ReadString.length()-7];
  Serial.print("printing out the servo1");
  Serial.println(servo1);
  Serial.println(servo2);
  servo1.toCharArray(carray1,sizeof(carray1)+1);
  servo2.toCharArray(carray2,sizeof(carray2)+1);
  servo3.toCharArray(carray3,sizeof(carray3)+1);
  Serial.print("Printing out the carray1");
  Serial.println(carray1[2]);
  n1 = atoi(carray1);
  n2 =atoi(carray2);
  n3 =atoi(carray3); 
  Serial.print("printing out the n1");
  Serial.println(n1);
  RmotMove(n1);
  YmotMove(n2);
  ZmotMove(n3);
  }
  else if((ReadString[3]=='b')&&(ReadString[6]=='c'))
  {
    servo1=ReadString.substring(1,3);
  servo2=ReadString.substring(4,6);
  servo3=ReadString.substring(7,ReadString.length());
  char carray1[2]; //magic needed to convert string to a number 
  char carray2[2];
  char carray3[ReadString.length()-6];
  Serial.print("printing out the servo1");
  Serial.println(servo1);
  Serial.println(servo2);
  servo1.toCharArray(carray1,sizeof(carray1)+1);
  servo2.toCharArray(carray2,sizeof(carray2)+1);
  servo3.toCharArray(carray3,sizeof(carray3)+1);
  Serial.print("Printing out the carray1");
  Serial.println(carray1[2]);
  n1 = atoi(carray1);
  n2 =atoi(carray2);
  n3 =atoi(carray3); 
  Serial.print("printing out the n1");
  Serial.println(n1);
  RmotMove(n1);
  YmotMove(n2);
  ZmotMove(n3);
  }
  else if((ReadString[4]=='b')&&(ReadString[6]=='c'))
  {
     servo1=ReadString.substring(1,4);
    servo2=ReadString.substring(5,6);
    servo3=ReadString.substring(7,ReadString.length());
  char carray1[3]; //magic needed to convert string to a number 
  char carray2[2];
  char carray3[ReadString.length()-6];
  Serial.print("printing out the servo1");
  Serial.println(servo1);
  Serial.println(servo2);
  servo1.toCharArray(carray1, sizeof(carray1)+1);
  servo2.toCharArray(carray2,sizeof(carray2)+1);
  servo3.toCharArray(carray3,sizeof(carray3)+1);
  Serial.print("Printing out the carray1");
  Serial.println(carray1[2]);
  n1 = atoi(carray1);
  n2 =atoi(carray2);
  n3=atoi(carray3);
  Serial.print("printing out the n1");
  Serial.println(n1);
  RmotMove(n1);
  ZmotMove(n3);
  YmotMove(n2);
  }
  else if((ReadString[4]=='b')&&(ReadString[7]=='c'))
  {
     servo1=ReadString.substring(1,4);
    servo2=ReadString.substring(5,7);
    servo3=ReadString.substring(8,ReadString.length());
  char carray1[3]; //magic needed to convert string to a number 
  char carray2[3];
  char carray3[ReadString.length()-7];
  Serial.print("printing out the servo1");
  Serial.println(servo1);
  Serial.println(servo2);
  servo1.toCharArray(carray1, sizeof(carray1)+1);
  servo2.toCharArray(carray2,sizeof(carray2)+1);
  servo3.toCharArray(carray3,sizeof(carray3)+1);
  Serial.print("Printing out the carray1");
  Serial.println(carray1[2]);
  n1 = atoi(carray1);
  n2 =atoi(carray2);
  n3=atoi(carray3);
  Serial.print("printing out the n1");
  Serial.println(n1);
  RmotMove(n1);
  ZmotMove(n3);
  YmotMove(n2);
  }
  
  }
  else
  {
   servo1=ReadString.substring(1,4);
    servo2=ReadString.substring(5,7);
    servo3=ReadString.substring(8,ReadString.length());
  char carray1[3]; //magic needed to convert string to a number 
  char carray2[3];
  char carray3[ReadString.length()-7];
  Serial.print("printing out the servo1");
  Serial.println(servo1);
  Serial.println(servo2);
  servo1.toCharArray(carray1, sizeof(carray1)+1);
  servo2.toCharArray(carray2,sizeof(carray2)+1);
  servo3.toCharArray(carray3,sizeof(carray3)+1);
  Serial.print("Printing out the carray1");
  Serial.println(carray1[2]);
  n1 = atoi(carray1);
  n2 =atoi(carray2);
  n3=atoi(carray3);
  Serial.print("printing out the n1");
  Serial.println(n1);
  RmotMove(n1);
  ZmotMove(n3);
  YmotMove(n2);
  }
  }
}
ReadString="";
}

void Move_a_bit(int a,int b)
{
   if(ReadString[1]=='1')
      {
          counterClockwise(a,b);
          delay(100);
      }
      if(ReadString[1]=='2')
      {
        clockwise(a,b);
        delay(100);
    }
}
