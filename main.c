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
#pragma config MCLRE = OFF       // GP3/MCLR pin function select (GP3/MCLR pin function is GP3)
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
    
    TRISIO = 0b0001000; //Set 0001000. This means GP3 is input, the others are output.
    
    return;
}

int main(int argc, char** argv) {
    
    // Initialize PIC
    PIC_init();
    /*
     * GP0: B
     * GP1: C
     * GP2: D
     * GP4: A
     * Comment: 2104 => DCBA => e.g) LLLL
     */
    unsigned char gpio[10] = {
        0b000000, // LLLL => 0
        0b010000, // LLLH => 1
        0b000001, // LLHL => 2
        0b010001, // LLHH => 3
        0b000010, // LHLL => 4
        0b010010, // LHLH => 5
        0b000011, // LHHL => 6
        0b010011, // LHHH => 7
        0b000100, // HLLL => 8 Note: GP3 is input
        0b010100, // HLLH => 9
    };
    unsigned int counter = 0;
    GPIO = gpio[counter];
    
    while(1){
        if (GP3 == 1){
            counter = (counter + 1) % 10;
            GPIO = gpio[counter];
            GPIO += 0b100000; // Set GP5 = H means turn on the external light
            // delay for the next detection
            __delay_ms(5000);
        }
        else{
            GPIO = gpio[counter];
            __delay_ms(100);
        }
   }
    return (EXIT_SUCCESS);
}
