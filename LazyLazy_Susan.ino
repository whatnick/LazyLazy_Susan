/*
   Lazy version of a lazy susan for time-lapse photography of
   sculptures

   Dual motor control for rotation of lazy-susan
   and Driving camera slide on rails

   Analog joystick support
*/

#include <AccelStepper.h>

// The X Stepper pins
#define STEPPER1_DIR_PIN 4
#define STEPPER1_STEP_PIN 5
// The Y stepper pins
#define STEPPER2_DIR_PIN 7
#define STEPPER2_STEP_PIN 6

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);

#define ANALOG_X A0
#define ANALOG_Y A1

int x_val,y_val;
int step_size = 10;

void setup()
{
  stepper1.setMaxSpeed(100.0);
  stepper1.setAcceleration(100.0);
}

void loop()
{
  // Read values
  x_val = analogRead(ANALOG_X);
  y_val = analogRead(ANALOG_Y);

  
  if(x_val > 200 and x_val < 800)
  {
    stepper1.disableOutputs();
  }
  else
  {
    stepper1.enableOutputs();
  }
  
  if(x_val > 900)
  {
    stepper1.move(step_size);
  }

  if(x_val <100)
  {
    stepper1.move(-step_size);
  }

  if(y_val > 900)
  {
    if(step_size<30) step_size++;
  }

  if(y_val <100)
  {
    if(step_size>0) step_size--;
  }

  stepper1.run();
}
