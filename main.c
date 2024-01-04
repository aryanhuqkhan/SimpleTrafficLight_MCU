// Author: Aryan Huq Khan
// Carleton University
// Computer Systems Engineering
// Last Modified : Tue Jan 2 11:22pm

#include "msp.h"
#include <stdbool.h>
#include <stdint.h>
#define CCR0 8192

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


int main(){
    
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Disabling the watchdog timer
    
    //timer config
    TA0CTL &= (uint16_t)(~((1<<5) | (1<<4)));  //stop timer
    TA0CTL |= (uint16_t)(1<<8);                //choosing clk source set bit 8
    TA0CTL &= (uint16_t)(~(1<<9));             //choosing clk source clear bit 9
    TA0CTL |= (uint16_t)(1<<7);                // diving the clock by 4 set bit 7
    TA0CTL &=(uint16_t)(~(1<<6));              // diving the clock by 4 clear bit 6
    TA0CTL &= (uint16_t)(~(1<<0));             // clear interrupt flag
    TA0CCR0 =(uint16_t) (CCR0 * 5);
    TA0CTL |= (uint16_t)((1<<1));              // interrupt enable
    TA0CTL |= (uint16_t)((1<<4));              // up mode (count to CCR0)
    
    //NVIC congfig
    NVIC_SetPriority(TA0_N_IRQn, 2); // setting NVIC priority
    NVIC_ClearPendingIRQ(TA0_N_IRQn); // clearing priority register
    NVIC_EnableIRQ(TA0_N_IRQn); // enabling NVIC interrupt

    int lights = 0;
    
    
    while (1){
        if (light == 0){
                P2OUT &= (uint8_t)(~((1<<0)|(1<<1)|(1<<2))); // clear the color
                P2OUT |= (uint8_t)((1<<1)); // change to green

            }
        
        else if (light == 1){
                P2OUT &= (uint8_t)(~((1<<0)|(1<<1)|(1<<2))); // clear the color
                P2OUT |= (uint8_t)((1<<0)|(1<<1)); // change yellow

            }
        else if (light == 2){
                P2OUT &= (uint8_t)(~((1<<0)|(1<<1)|(1<<2))); // clear the color
                P2OUT |= (uint8_t)((1<<0)); // change red
            }


        }
}
