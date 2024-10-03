// Include the motor shield  V1 library and servo

#include <Servo.h>
#include <AFMotor.h>

// Define the pins for control button
#define pushButton A1
#define IRpin A0
#define LEDpin A4

// Connect the DC motor to M1 on the motor control board and pump to M4
AF_DCMotor DCmotor(1);
AF_DCMotor pump(4);
Servo Servo1;

// Flag for program flow control
bool flag = false;



void setup() {
  Serial.begin (9600);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(IRpin, INPUT);
  DCmotor.setSpeed(255);
  Servo1.attach(9);
  pump.setSpeed(255);  
  pump.run(RELEASE);
}

//global variables
bool motorOn = false;
bool buttonPushed = false;
int IRval;
int servo_pos = 0;
int tubeNum = 0;


void loop() {
 
  //CHANGE THESE VARIABLES

  int tube1mL = 5;
  int tube1g = 1;

  int tube2mL = 5;
  int tube2g = 1;
 
  int tube3mL = 5;
  int tube3g = 1;

  int tube4mL = 5;
  int tube4g = 1;

  int tube5mL = 5;
  int tube5g = 1;

  int mLRate = 1000;
  int gRate = 100;


  /////////////////////
  //DO NOT EDIT BELOW//
  /////////////////////

  //setting up the variables
  int turnTime = 100;
  int tubes [5][2] = {{tube1mL,tube1g}, {tube2mL,tube2g}, {tube3mL,tube3g}, {tube4mL,tube4g}, {tube5mL,tube5g}};
 



  if((!digitalRead(pushButton)) == 1){
      buttonPushed = !buttonPushed;  
  }

  closeServo();
 
  Serial.println(digitalRead(pushButton));
 
  while(buttonPushed == true && tubeNum < 6){
    Serial.println("In wile loop");

   
    IRval = digitalRead(IRpin);
    Serial.println(IRval);

    if((!digitalRead(pushButton)) == 1){
      buttonPushed = !buttonPushed;
      break;
    }
    EMGcheck();
     
    if(IRval == 1){
      DCmotor.setSpeed(100);
      DCmotor.run(FORWARD);
      EMGcheck();
    }
    else{
      tubeNum++;

      EMGcheck();
      DCmotor.run(RELEASE);

      Dispenser(tubes[tubeNum][2], tubes[tubeNum][1]);

      EMGcheck();
      DCmotor.run(FORWARD);
      delay(1000);
    }    
  }
  Serial.println(motorOn);
}


void Dispenser(int grams, int mL){

  Serial.println("Dispensing Triggered");
  Serial.println(tubeNum);
  Serial.println(grams);
  Serial.println(mL);


  openServo();
  delay(grams*1000);
  closeServo();

  pump.setSpeed(200);
  pump.run(FORWARD);
  Serial.println("Pumping");
  delay(mL*100);
  pump.run(RELEASE);
}

void EMGcheck(){

  int inf = 0;

  if((!digitalRead(pushButton)) == 1){
    buttonPushed = !buttonPushed;
    inf = 1;
    DCmotor.setSpeed(0);
    pump.setSpeed(0);
   
    exit(1);
  }
  else 
    return;
}
void closeServo(){
  Servo1.write(0);
}
void openServo(){
  Servo1.write(180);
}
