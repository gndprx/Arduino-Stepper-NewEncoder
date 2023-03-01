#include "NewEncoder.h"
#include <AccelStepper.h>

// Setup Encoder 
const byte EncChA_Pin = 2;
const byte EncChB_Pin = 3;
const int minVal = -32767;
const int maxVal =  32767;
const int startVal = 0;
int16_t currentValue = 0;
int16_t prevEncoderValue = -1;

// Pins 2 and 3 should work for many processors, including Uno. See README for meaning of constructor arguments.
// Use FULL_PULSE for encoders that produce one complete quadrature pulse per detnet, such as: https://www.adafruit.com/product/377
// Use HALF_PULSE for endoders that produce one complete quadrature pulse for every two detents, such as: https://www.mouser.com/ProductDetail/alps/ec11e15244g1/?qs=YMSFtX0bdJDiV4LBO61anw==&countrycode=US&currencycode=USD
NewEncoder myEncoderObject(EncChA_Pin, EncChB_Pin, minVal, maxVal, startVal, FULL_PULSE);

// Setup Stepper
AccelStepper stepper (1, 8, 9); //pulses, clk, dir
int RotateCounter = 0;
int stepperMaxSpeed = 8000;
int stepperAcceleration = 16000;
int stepperRotationMultiplier = 1;

void setup() {
  // myEncState is a variable of type EncoderState
  // EncoderState is a structured variable that has two "simple" variables
  // .currentValue which is type int16_t
  // (16 bit signed integer valuerange -36767 to 36767)
  // currentValue counts up / down with each pulse created through rotating the encoder
  // and
  // .currentClick which is of type "EncoderClick"
  // the variable type "EncoderClick" can have just 3 values
  // NoClick, DownClick, UpClick where "click" means a "pulse" created through rotating the encoder
  NewEncoder::EncoderState myEncState;

  Serial.begin(115200);    

  if (!myEncoderObject.begin()) {
    Serial.println("Encoder Failed to Start. Check pin assignments and available interrupts. Aborting.");
    while (1) {
      yield();
    }
  } else {
    // store values of currentValue and EncoderClick into variable myEncState
    myEncoderObject.getState(myEncState);
    prevEncoderValue = myEncState.currentValue;
  }

  stepper.setMaxSpeed(stepperMaxSpeed);
  stepper.setAcceleration(stepperAcceleration);
}

void loop() {
  NewEncoder::EncoderState myCurrentEncoderState;

  // store actual values into variable myCurrentEncoderState
  if (myEncoderObject.getState(myCurrentEncoderState)) {
    currentValue = myCurrentEncoderState.currentValue;

    // if currentValue has REALLY changed print new currentValue
    if (currentValue != prevEncoderValue) {

      switch (myCurrentEncoderState.currentClick) {
        case NewEncoder::UpClick:
          RotateCounter = RotateCounter + stepperRotationMultiplier; // Encoder registered an UpClick so increase the rotation counter
          break;
        case NewEncoder::DownClick:
          RotateCounter = RotateCounter - stepperRotationMultiplier; // Encoder registered a DownClick so decrease the rotation counter
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


