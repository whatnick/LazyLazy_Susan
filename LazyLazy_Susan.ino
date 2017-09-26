/*
   Lazy version of a lazy susan for time-lapse photography of
   sculptures

   Dual motor control for rotation of lazy-susan
   and Driving camera slide on rails

   Analog joystick support
*/

#include <AccelStepper.h>


// The Lazy susan stepper pins
#define STEPPER1_DIR_PIN 4
#define STEPPER1_STEP_PIN 5
#define STEPPER1_ENABLE_PIN 8


// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);

//Analog inputs
#define ANALOG_X A0
#define ANALOG_Y A1

//Switch to capture joystick press
#define SWITCH_PIN 3

int x_val,y_val;
float step_speed = 100.0;
const float max_speed = 200.0;
const float min_speed = 10.0;

void setup()
{
  stepper1.setMaxSpeed(step_speed*2.0);
  stepper1.setAcceleration(200.0);
  //stepper1.setEnablePin(STEPPER1_ENABLE_PIN);
  //stepper1.setPinsInverted(false, false, true);

  pinMode(STEPPER1_ENABLE_PIN,OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  // Read values
  x_val = analogRead(ANALOG_X);
  if(x_val > 200 and x_val < 800)
  {
    stepper1.stop();
    stepper1.disableOutputs();
    digitalWrite(STEPPER1_ENABLE_PIN,HIGH);
  }
  else
  {
    digitalWrite(STEPPER1_ENABLE_PIN,LOW);
    stepper1.enableOutputs();
  }
  
  if(x_val > 900)
  {
    stepper1.move(10);
    stepper1.run();
    return;
  }

  if(x_val <100)
  {
    stepper1.move(-10);
    stepper1.run();
    return;
  }
  
  y_val = analogRead(ANALOG_Y);

  if(y_val > 900)
  {
    if(step_speed < max_speed) step_speed+=0.1;
  }

  if(y_val <100)
  {
    if(step_speed > min_speed) step_speed-=0.1;
  }

  int cont_run = digitalRead(SWITCH_PIN);
  
  if(cont_run==0)
  {
    digitalWrite(STEPPER1_ENABLE_PIN,LOW);
    stepper1.enableOutputs();
    stepper1.setSpeed(step_speed);
    stepper1.runSpeed();
    return;
  }
  else
  {
    stepper1.stop();
    digitalWrite(STEPPER1_ENABLE_PIN,HIGH);
    stepper1.disableOutputs();
  }
}
