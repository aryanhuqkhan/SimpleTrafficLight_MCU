# Timers in MCU

## Description

In this lab, I have exercised 3 things: programming interrupts and configuring/using the
timers, as well as designing the system using extended FSM (Finite State Manchine) using the Programming language C. 

## Table of Contents

- Prerequisites 
- Getting Started
- Instructions
- Additional Resources

## Prerequisites

Requirement 1: The equipment used is the Texas Instrument model: MSP432P401R MicroController, which must be set up. For more info how to set up visit Additional Reasource SECTION. 

Requirement 2: Users must have MSP432P4xx Technical Reference Manual

Requirement 3: Disable Watchdog Timer (MARS ROVER) :shipit:

## Instructions

Design and program traffic light behavior. The traffic lightmodel goes through an infinite cycle: green light for 5 seconds, yellow light for 1 second, red light for 3 seconds. Once the model is designed, implement it using aa timer-based solution. The timer ISR should keep track of the time, and when the right time comes, change the traffic light state. This information is shared with the main program, which is in charge of changing the colors.

## Design and Code

### FSM model:
"light" is a flag variable that indicates which color the LED is. light = 0 for Green, light = 1 for Yellow and light = 2 for Red.
Down below shows the modelling of the FSM that was used to code the program.

![Screen Shot 2024-01-03 at 3 40 49 PM](https://github.com/aryanhuqkhan/SimpleTrafficLight_MCU/assets/146489368/0ec25636-fcd7-40e1-84ba-05b14ff060da)

The LED OFF state represents 2 things:
- The LED OFF when transitioning from one colored state to another colored is LED is off
- The color changes in the LED can only go in this sequence: Green->Yellow->Red->Green->Yelow->Red and the cycle goes on. The logic representation is shown below:
  ```
  light = (light++)%2
  ```

The Colored states transition to LED OFF state after t seconds (Green t = 5, Yellow t = 1, Red t = 3)

Asumption: No time is passed when trasitioning from LED OFF state to any Colored state. 


## Code:

### CRR0 register and CTL register

CTL register is the Timer's control register, to control counting mode, choosing source clk, enabling interrupt and more.

CRR0's value is the number of cycles needed to cause an interrupt

CRR0 calculation:

Source Clock: 32768 Hz

Clock divider = 1/4

Source Clock after being divided: 8192 Hz

CRR0 value is choose to be 8192 so that (1*CRR0) = 1 second

Clock speed =  8192 Hz -> 1 cycle = 1 / 8192 seconds

thus, 8192 cycles-> 8192 * 1 cycle = 8192 * (1 / 8192)

```
#define CCR0 8192

TA0CTL |= (uint16_t)(1<<8); // setting clk source 32.768 Hz
TA0CTL &= (uint16_t)(~(1<<9)); // setting clk source 32.768 Hz
TA0CTL |= (uint16_t)(1<<7); //setting divder to 1/4
TA0CTL &=(uint16_t)(~(1<<6)); //setting divder to 1/4
TA0CCR0 =(uint16_t) (((CCR0) * 5 )-1)// setting to 5 seconds
```


### P2OUT control register

P2OUT's pin 0, 1, 2 control the color of the RGB LED

by changing the bit values in these 3 pins you are able to make 7 colors. And Colors green, 
yellow and red are included in the 7 colors. the bit value are :
- Green 010
- Yellow 011
- Red 001

```
 P2OUT |= (uint8_t)((1<<1)); // green
 P2OUT |= (uint8_t)((1<<0)|(1<<1)); // yellow
 P2OUT |= (uint8_t)((1<<0)|(1<<0)); // red
```

### Timer ISR

Is it is the timer's interrupt serivce routine. It executes when there is an interrupted caused in the timer. Thus it happens when
CCR0 value is reached.

The function of this ISR is set flags (to change colors) and change the CCR0 value to cause interrupts at differents intervals (after 5s, after 1s, after 3s). The changing of colors is done in the main program to spend less as possible time in the ISR.
```
void TA0_N_IRQHandler(void) {
    extern int light;
    TA0CTL &= (uint16_t)(~(1<<0));   //Clearing Interrupt Flag
    if  (light == 0){
        TA0CCR0 = CCR0;             //Setting CCRO so Interrupt will be generated after 1s
        light = 1;
    }
    else if (light == 1){
        TA0CCR0 = CCR0 * 3;             //Setting CCRO so Interrupt will be generated after 3s
        light = 2;
    }
    else if (light == 2){
        TA0CCR0 = CCR0 * 5;             //Setting CCRO so Interrupt will be generated after 5s
        light = 0;
    }
}

```
Note: Whenever the timer ISR is called we must immediately clear the Interrupt flag. This should be done in all Timer ISRs.

More info about the Register in can be found in the MSP432P4xx Technical Reference Manual

## Additional Reasources:

Tutorial to set up the MCU in Keil: https://www.youtube.com/watch?v=u5SrhXUHYu4&ab_channel=EasyElectric
















