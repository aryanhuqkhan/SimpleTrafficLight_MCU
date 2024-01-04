# Timers in MCU

## Description

In this lab, I have exercised 3 things: programming interrupts and configuring/using the
timers, as well as designing the system using extended FSM (Finite State Manchine) using the Programming language C. 

## Table of Contents

- Prerequisites 
- Getting Started
- Lab Instructions
- Additional Resources
- License

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






















