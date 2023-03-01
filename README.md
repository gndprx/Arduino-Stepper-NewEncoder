# Arduino-Stepper-NewEncoder

This sketch combines the NewEncoder library with the AccelStepper to control stepper motors with a manual pulse generator.

## Libraries Needed

* NewEncoder library from gfvalvo from here: https://github.com/gfvalvo/NewEncoder
* AccelStepper library from the Arduino library manager

## The Problem

Existing implementations of encoder-to-stepper control were causing my combination of hardware to be jittery, missed steps or occasionally run up a lot of steps when only turning a single notch on the wheel. A combination of pull-up resistors and filter capacitors were used on the hardware side to combat some of the noise but ultimately it seemed the signal from the cheap encoder wheel was just not perfect.

## The Solution

I ran across the NewEncoder library by gfvalvo which already had code in place for things like debounce and state management. You can read more about this library on that project's github page but ultimately someone had already invented a better wheel so I added it to my solution.

NewEncoder became the base that when combined with the stepper library significantly smoothed out the interaction between the encoder and the stepper. 

You will need to play with the stepperMaxSpeed and stepperAcceleration values to suit your hardware configuration. The speed and acceleration go hand-in-hand and will vary based on how you have configured your micro-stepping on the driver. The values in my version are for a Nema 23 configured for 1/2 step or 400 steps per revolution.

stepperRotationMultiplier was added as a means to amplify the number of steps per pulse without changing your micro stepping. A default multiplier of 1 will rotate your chosen micro step amount for a single click of the encoder wheel. Upping the value to 2 will rotate 2 micro steps per single click, etc... 

## Known Limitations

When using the Arduino Uno, you are limited to only using a single encoder wheel based on the number of available interrupt pins on the board. This means you can only control one stepper or you would have to provide a means of switching outputs to manually select additional motors to control with the same wheel.

I have not tested but upgraindg to an ATMega may allow more than one. It's on my future to-do list to try. The Mega should support 6 external interrupt pins which means in theory it could handle up to 3 encoder wheels at a time.
