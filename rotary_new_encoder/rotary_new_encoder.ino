#include "NewEncoder.h"
#include <AccelStepper.h>

// Setup Encoder 
const byte EncChA_Pin = 2;
const byte EncChB_Pin = 3;
const byte Enc2ChA_Pin = 20;
const byte Enc2ChB_Pin = 21;
const byte Enc3ChA_Pin = 18;
const byte Enc3ChB_Pin = 19;
const int minVal = -32767;
const int maxVal =  32767;
const int startVal = 0;
int16_t currentValue = 0;
int16_t prevEncoderValue = -1;
int16_t currentValue2 = 0;
int16_t prevEncoderValue2 = -1;
int16_t currentValue3 = 0;
int16_t prevEncoderValue3 = -1;

NewEncoder myEncoderObject(EncChA_Pin, EncChB_Pin, minVal, maxVal, startVal, FULL_PULSE);
NewEncoder myEncoderObject2(Enc2ChA_Pin, Enc2ChB_Pin, minVal, maxVal, startVal, FULL_PULSE);
NewEncoder myEncoderObject3(Enc3ChA_Pin, Enc3ChB_Pin, minVal, maxVal, startVal, FULL_PULSE);

// Setup Stepper 1
AccelStepper stepper (1, 8, 9); //pulses, clk, dir
int RotateCounter = 0;
int stepperMaxSpeed = 8000;
int stepperAcceleration = 16000;
int stepperRotationMultiplier = 1;

// Setup Stepper 2
AccelStepper stepper2 (1, 10, 11); //pulses, clk, dir
int RotateCounter2 = 0;
int stepperMaxSpeed2 = 8000;
int stepperAcceleration2 = 16000;
int stepperRotationMultiplier2 = 1;

// Setup Stepper 3
AccelStepper stepper3 (1, 12, 13); //pulses, clk, dir
int RotateCounter3 = 0;
int stepperMaxSpeed3 = 8000;
int stepperAcceleration3 = 16000;
int stepperRotationMultiplier3 = 1;

void setup() {
  NewEncoder::EncoderState myEncState;
  NewEncoder::EncoderState myEncState2;
  NewEncoder::EncoderState myEncState3;

  Serial.begin(115200);    

  // Encoder 1
  if (!myEncoderObject.begin()) {
    Serial.println("Encoder 1 Failed to Start. Check pin assignments and available interrupts. Aborting.");
    while (1) {
      yield();
    }
  } else {
    // store values of currentValue and EncoderClick into variable myEncState
    myEncoderObject.getState(myEncState);
    prevEncoderValue = myEncState.currentValue;
  }

  // Encoder 2
  if (!myEncoderObject2.begin()) {
    Serial.println("Encoder 2 Failed to Start. Check pin assignments and available interrupts. Aborting.");
    while (1) {
      yield();
    }
  } else {
    // store values of currentValue and EncoderClick into variable myEncState
    myEncoderObject2.getState(myEncState2);
    prevEncoderValue2 = myEncState2.currentValue;
  }

  // Encoder 3
if (!myEncoderObject3.begin()) {
    Serial.println("Encoder 2 Failed to Start. Check pin assignments and available interrupts. Aborting.");
    while (1) {
      yield();
    }
  } else {
    // store values of currentValue and EncoderClick into variable myEncState
    myEncoderObject3.getState(myEncState3);
    prevEncoderValue3 = myEncState3.currentValue;
  }

  // Stepper 1
  stepper.setMaxSpeed(stepperMaxSpeed);
  stepper.setAcceleration(stepperAcceleration);

  // Stepper 2
  stepper2.setMaxSpeed(stepperMaxSpeed2);
  stepper2.setAcceleration(stepperAcceleration2);

  // Stepper 3
  stepper3.setMaxSpeed(stepperMaxSpeed3);
  stepper3.setAcceleration(stepperAcceleration3);
}

void loop() {
  NewEncoder::EncoderState myCurrentEncoderState;
  NewEncoder::EncoderState myCurrentEncoderState2;
  NewEncoder::EncoderState myCurrentEncoderState3;

  // Encoder 1
  // store actual values into variable myCurrentEncoderState
  if (myEncoderObject.getState(myCurrentEncoderState)) {
    currentValue = myCurrentEncoderState.currentValue;

    // if currentValue has REALLY changed print new currentValue
    if (currentValue != prevEncoderValue) {

      switch (myCurrentEncoderState.currentClick) {
        case NewEncoder::UpClick:
          RotateCounter = RotateCounter + stepperRotationMultiplier;
          break;
        case NewEncoder::DownClick:
          RotateCounter = RotateCounter - stepperRotationMultiplier;
          break;

        default: break;        
      }
      prevEncoderValue = currentValue;
      RotateStepper();

    } else
      switch (myCurrentEncoderState.currentClick) {
        case NewEncoder::UpClick:
          Serial.println("at upper limit.");
          break;

        case NewEncoder::DownClick:
          Serial.println("at lower limit.");
          break;

        default:
          break;
      }
  }

  // Encoder 2
  // store actual values into variable myCurrentEncoderState2
  if (myEncoderObject2.getState(myCurrentEncoderState2)) {
    currentValue2 = myCurrentEncoderState2.currentValue;

    // if currentValue has REALLY changed print new currentValue
    if (currentValue2 != prevEncoderValue2) {

      switch (myCurrentEncoderState2.currentClick) {
        case NewEncoder::UpClick:
          RotateCounter2 = RotateCounter2 + stepperRotationMultiplier2;
          break;
        case NewEncoder::DownClick:
          RotateCounter2 = RotateCounter2 - stepperRotationMultiplier2;
          break;

        default: break;        
      }
      prevEncoderValue2 = currentValue2;
      RotateStepper2();

    } else
      switch (myCurrentEncoderState2.currentClick) {
        case NewEncoder::UpClick:
          Serial.println("at upper limit.");
          break;

        case NewEncoder::DownClick:
          Serial.println("at lower limit.");
          break;

        default:
          break;
      }
  }

  // Encoder 3
  // store actual values into variable myCurrentEncoderState3
  if (myEncoderObject3.getState(myCurrentEncoderState3)) {
    currentValue3 = myCurrentEncoderState3.currentValue;

    if (currentValue3 != prevEncoderValue3) {

      switch (myCurrentEncoderState3.currentClick) {
        case NewEncoder::UpClick:
          RotateCounter3 = RotateCounter3 + stepperRotationMultiplier3;
          break;
        case NewEncoder::DownClick:
          RotateCounter3 = RotateCounter3 - stepperRotationMultiplier3;
          break;

        default: break;        
      }
      prevEncoderValue3 = currentValue3;
      RotateStepper3();

    } else
      switch (myCurrentEncoderState3.currentClick) {
        case NewEncoder::UpClick:
          Serial.println("at upper limit.");
          break;

        case NewEncoder::DownClick:
          Serial.println("at lower limit.");
          break;

        default:
          break;
      }
  }
}


void RotateStepper()
{
    stepper.enableOutputs();
    stepper.moveTo(RotateCounter);
    while(stepper.distanceToGo() != 0)
    {
      stepper.runToNewPosition(RotateCounter);
    }
}

void RotateStepper2()
{
    stepper2.enableOutputs();
    stepper2.moveTo(RotateCounter2);
    while(stepper2.distanceToGo() != 0)
    {
      stepper2.runToNewPosition(RotateCounter2);
    }
}

void RotateStepper3()
{
    stepper3.enableOutputs();
    stepper3.moveTo(RotateCounter3);
    while(stepper3.distanceToGo() != 0)
    {
      stepper3.runToNewPosition(RotateCounter3);
    }
}


