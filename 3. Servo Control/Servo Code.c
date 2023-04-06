#include <msp430.h>

#define SERVO_PIN BIT1  // Pin 4.1

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer


P4DIR |= SERVO_PIN; // Set servo pin as output
P4OUT &= ~SERVO_PIN; // Set servo pin to low initially

P2DIR &= ~BIT3; // Set P2.3 as input
P2REN |= BIT3;  // Enable pullup/pulldown resistor for P2.3
P2OUT |= BIT3;  // Set P2.3 pullup resistor

P4DIR &= ~BIT1; // Set P4.1 as input
P4REN |= BIT1;  // Enable pullup/pulldown resistor for P4.1
P4OUT |= BIT1;  // Set P4.1 pullup resistor

// Loop forever
while(1) 
{
    // Check if left button is pressed
    if ((P4IN & BIT1) == 0X00) 
    {
        // Turn servo counterclockwise
        P4OUT |= SERVO_PIN; // Set servo pin to high
        __delay_cycles(10000); // Wait for servo to move
        P4OUT &= ~SERVO_PIN; // Set servo pin to low
        __delay_cycles(40000); // Wait for servo to stop moving
    }
    // Check if right button is pressed
    else if ((P2IN & BIT3) == 0X00) 
    {
        // Turn servo clockwise
        P4OUT |= SERVO_PIN; // Set servo pin to high
        __delay_cycles(20000); // Wait for servo to move
        P4OUT &= ~SERVO_PIN; // Set servo pin to low
        __delay_cycles(40000); // Wait for servo to stop moving
    }
}
