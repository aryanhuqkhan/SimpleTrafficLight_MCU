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

Design and program traffic light behavior. The traffic light
model goes through an infinite cycle: green light for 5 seconds, yellow light for 1
second, red light for 3 seconds. Once the model is designed, implement it using a
a timer-based solution. The timer ISR should keep track of the time, and when the
right time comes, change the traffic light state. This information is shared with the
main program, which is in charge of changing the colors.

## Design and Programming Timer 

### FSM model:
light is flag variable which 

<img width="500" alt="Screen Shot 2023-12-31 at 3 46 12 AM" src="https://github.com/aryanhuqkhan/SimpleTrafficLight_MCU/assets/146489368/6b5d0024-f78b-4a81-a19f-56a029920db4">

### Example Code

```
```





















