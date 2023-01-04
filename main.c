/*
 * File:   main.c
 * Author: Junnosuke Kado
 *
 * Created on November 23, 2022, 12:23 AM
 */



// PIC12F629 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO     // Oscillator Selection bits (RC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, RC on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON      // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <stdio.h>
#include <stdlib.h>
#include <pic.h>
#include <xc.h>

#define _XTAL_FREQ 4000000 // for delay

/**
 * Initialize PIC
 */
void PIC_init(){
    OSCCAL = 0x80; //oscillator center
    PCON &= 0x00; //enable POR BOD
    
    CMCON = 0x07; //disable comparator
    
    TRISIO = 0x08; //Set 00001000. This means GP3 is input, the others are output.
    
    return;
}

int main(int argc, char** argv) {
    
    // Initialize PIC
    PIC_init();
    
    while(1){
        GPIO = 0x01; // Set GP0 high
        __delay_ms(500);
        GPIO = 0x00; // Set All GPIO low
        __delay_ms(500);
   }
    return (EXIT_SUCCESS);
}
