# Arduino-Stepper-NewEncoder
This sketch combines the NewEncoder library with the AccelStepper to control stepper motors with a manual pulse generator.

## Libraries Needed
* NewEncoder library from gfvalvo from here: https://github.com/gfvalvo/NewEncoder
* AccelStepper library from the Arduino library manager

## Problem Statement
Existing implementations of encoder-to-stepper control were causing my combination of hardware to be jittery, missed steps or occasionally run up a lot of steps when only turning a single notch on the wheel. A combination of pull-up resistors and filter capacitors were used on the hardware side to combat some of the noise but ultimately it seemed the signal from the cheap encoder wheel was just not perfect.

## The Solution

I ran across the NewEncoder library by gfvalvo which already had code in place for things like debounce and state management. You can read more about this library on that project's github page but ultimately someone had already invented a better wheel so I added it to my solution.

NewEncoder became the base that when combined with the stepper library significantly smoothed out the interaction between the encoder and the stepper. 

MPG or manual pulse generator. These are quadrature step encoders that are cheap and easy to implement. Using a 5v source they output a 2 phase square wave (A and B outputs) with an offset that creates 4 possible states: 00, 10, 11, 01 for CW rotation and 00, 01, 11, 10 for CCW rotation.

Using the wave output below you would read Left to Right for clockwise rotation and Right to Left for counter-clockwise rotation to generate each of the 4 states. 

![image](https://user-images.githubusercontent.com/8764001/222147994-58a1b3f9-5a52-44f4-a8d6-bc03bf1c56e9.png)

Image credit https://commons.wikimedia.org/w/index.php?curid=22725391


## Hardware Used for this Project
See the Wiki page for relevant project hardware
