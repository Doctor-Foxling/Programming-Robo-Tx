import processing.serial.*;
import java.text.*;
import java.util.*;
import controlP5.*;
PImage photo;

Knob myKnobB;
Bang Z_up;
Slider Slider_Y;
Slider Slider_Z;

ControlP5 cp5;
Serial myPort;
int myColorBackground = color(0, 0, 0);
int sld=0;
int R_sld;
int Z_sld;
char[] sld_str;
char[] R_sld_str;
char[] Z_sld_str;
char[] cv;
boolean mouse[]={false,false,false,false};

color[] col = new color[] {
  color(100), color(150), color(200), color(250)
};
char dab[]={'a','b','c','d'};

void setup() {
  size(1200, 815); //Define the size of the application window
   printArray(Serial.list()); // print a list of available ports
  myPort = new Serial(this, Serial.list()[0], 9600); //Serial object for 
  // for communicating with the port (Com04) connected with Arduino
  photo=loadImage("Robo.jpg"); // PImage object to upload image
  noStroke();  // No Outline to the widgets 
  cp5 = new ControlP5(this); // ControlP5 objects to call its functions and widgets
  Slider_Y=   cp5.addSlider("sliderValue") // Add a ControlP5 Slider object
     .setPosition(400,150) // Set objects position
     .setRange(0,180) // Set the range of values provided by the slider
     .setSize(150,20) // Set Slider size
     .setColorForeground(color(255,0,255,80))// Foreground colour when inactive
     .setColorBackground(color(0, 160, 100,100))// Background colour
     .setColorActive(color(255,255,0,170))// Foreground colour when Active (i.e. used)
     ;
    
   myKnobB = cp5.addKnob("knobValue")
             .setRange(0,255)
             .setValue(0)
             .setPosition(134,175)
             .setRadius(70) 
             .setNumberOfTickMarks(10) // Set number of tick-marks (as in a clock)
             .setTickMarkLength(4)
             .snapToTickMarks(false) // Whether to snap to tick marks or fluid motion
             .setColorForeground(color(255,0,255,80))
             .setColorBackground(color(0, 160, 100,100))
             .setColorActive(color(255,255,0,100))
             .setDragDirection(Knob.HORIZONTAL) // Direction in which to drag the dial
             ;
  
    Slider_Z=  cp5.addSlider("sliderTicks1")
     .setPosition(190,450)
     .setSize(30,200)
     .setRange(500,0)
     .setValue(0)
     .setNumberOfTickMarks(50)
     .setColorForeground(color(255,0,255,80))
     .setColorBackground(color(0, 160, 100,100))
     .setColorActive(color(255,255,0,170))
     ;
     
  
  
  //for (int i=0;i<col.length;i++) {
    cp5.addBang("bang1")
       .setPosition(720, 60)
       .setSize(410, 90)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
 //600 200
  cp5.addBang("StopIt")
       .setPosition(893, 420)
       .setSize(72, 200)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
 Z_up=  cp5.addBang("bangZup")
       .setPosition(893, 272)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
   cp5.addBang("bangZdown")
       .setPosition(893, 663)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
   cp5.addBang("bangRco")
       .setPosition(778, 352)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
   cp5.addBang("bangRcl")
       .setPosition(1008, 352)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
   cp5.addBang("bangYfr")
       .setPosition(738, 467)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
   cp5.addBang("bangYbk")
       .setPosition(1048, 467)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
   cp5.addBang("bangGO")
       .setPosition(778, 585)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
   cp5.addBang("bangGC")
       .setPosition(1008, 585)
       .setSize(72, 72)
       .setLabel("")
       .setColorForeground(color(0, 160, 100,20))
       .setColorBackground(color(0, 160, 100,100))
       .setColorActive(color(0, 0, 100,100))
       ;
  // change the trigger event, by default it is PRESSED.
  /*cp5.addBang("bang")
     .setPosition(40, 300)
     .setSize(280, 40)
     .setTriggerEvent(Bang.RELEASE)
     .setLabel("changeBackground")
     ;*/
   
           
}

void draw() {
  //background(0);
  image(photo, 0, 0);
  hover(100,135,180,210,0);
  hover(300,130,300,60,1);
  hover(170,420,100,300,2);
  It_appears();
  
}

public void bang() {
  int theColor = (int)random(255);
  myColorBackground = color(theColor);
  println("### bang(). a bang event. setting background to "+theColor);
}

public void bangRcl(){ 
  myPort.write("R2"); //When button for clockwise rotation is pressed
}//Send The string 'R2' to the serial port
public void bangRco(){
  myPort.write("R1");// '1' means counter clockwise
}

public void bangZup(){
  myPort.write("Z2");// 'Z' for Z-axis, 2 for UP
}

public void bangZdown(){
  myPort.write("Z1"); //'Z' for Z-axis, 1 for DOWN
}

public void bangYfr(){
  myPort.write("Y1");
}

public void bangYbk(){
  myPort.write("Y2");
}

public void bangGO(){
  myPort.write("G2");
}

public void bangGC(){
  myPort.write("G1");
}  

public void controlEvent(ControlEvent theEvent) {
  /*if(theEvent.getController().getName().equals("sliderValue"))
    {
      sld=Math.round(theEvent.controller().getValue());
      /*if(sld/100<1)
      {
        sld_str[0]='0';
        char[] temp=(""+sld).toCharArray();
        for(int j=1;j<=2;j++)
        {     
        sld_str[j]=temp[j-1];
        }
      }
       println("Hello"+sld);
      sld_str=(""+sld).toCharArray();
    }*/
    if (theEvent.getController().getName().equals("bang1")) 
    {  //If 'Send Data' button is pressed send widget values to arduino board 
      println(dab[0]); 
      println(sld_str); // for testing purpose
      println(cv); 
      StringBuilder sb = new StringBuilder(64); // declare a String builder object
              // to store the widget values in a single string 
      sb.append(dab[0]); // append a separator
      sb.append(R_sld_str); //append R_motor's dial value
      sb.append(dab[1]); //append a separator
      sb.append(sld_str); // append Y_motor's slider value
      sb.append(dab[2]); // append a separator
      sb.append(Z_sld_str);//append Z_motor's slider value
      cv=sb.toString().toCharArray(); //put the string in a character array 
      for(int f=0;f<cv.length;f++) // run a loop for the length of the char array
      {
      myPort.write(cv[f]); // send each character separately to arduino
      println(cv[f]); // check the values being sent, in the Console  
      }
    }
    
  println(
  "## controlEvent / id:"+theEvent.controller().getId()+
    " / name:"+theEvent.controller().getName()+
    " / value:"+theEvent.controller().getValue()
    );
}

void sliderTicks1(float Value)//Called evertime slider1 value is changed
{
  Z_sld=Math.round(Value); //Gets the value of the slider and rounds it an integer
  println("Z_sld"+Z_sld);
  Z_sld_str=(""+Z_sld).toCharArray();//convert the rounded value to a Char Array
  
}

void sliderValue(float theValue) {//Called evertime slider2 value is changed
   sld=Math.round(theValue);//Gets the value of the slider and rounds it an integer
    println("Hello"+sld);
   sld_str=(""+sld).toCharArray();//convert the rounded value to a Char Array
}

void knobValue(float theVal)//Called evertime dial1 value is changed
{
  R_sld=Math.round(theVal);//Gets the value of the dial and rounds it an integer
  println("Yo"+R_sld);
  R_sld_str=(""+R_sld).toCharArray();//convert the rounded value to a Char Array
}

void hover(int x, int y, int w, int h, int e) { 
    // Left edge is x, Right edge is x + w
    if (mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h ) {
      mouse[e] = true;
    } else {
      mouse[e] = false;
    }
  }

void It_appears()
{
   if(mouse[0])
  {
    myKnobB.setPosition(134,175);
  }
   else if(mouse[1])
  {
    Slider_Y.setPosition(400,150);
  }
  else if(mouse[2])
  {
    Slider_Z.setPosition(190,450);
  }
   else
  {
    myKnobB.setPosition(1300,900);
    Slider_Y.setPosition(1300,900);
    Slider_Z.setPosition(1300,900);
  } 
}  
