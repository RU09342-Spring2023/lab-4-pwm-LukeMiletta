//Luciano Miles Miletta
//Embedded Systems
//LAB 4 PART 2



#include <msp430.h>

int count;
int color;
color = 0;
count = 0;

void TimerA3Setup();
void LEDSetup();



void main()
{

    WDTCTL = WDT_ADLY_1000;

    TimerA3Setup();
    LEDSetup();

    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM0_bits | GIE);         // Enter LPM0 w/ interrupt
    __no_operation();                           // For debugger
}


void TimerA3Setup()                             // Setup Timer 0
{
    TB3CCTL0 |= CCIE;                       // Enable TB0 CCR0 Overflow IRQ
    TB3CCR0 = 0xFFFF;                         // PWM Period
    TB3CCTL1 = OUTMOD_7;                      // CCR1 reset/set
    TB3CCR1 = 800;                            // CCR1 PWM duty cycle
    TB3CTL = TBSSEL__SMCLK | ID_3 | MC__UP | TBCLR; // SMCLK, up mode, clear TBR
}

void LEDSetup()
{
    P6DIR |= BIT0;                     // P6.0 output
    P6SEL0 |= BIT0;                     // RED
    P6SEL1 &= ~BIT0;                    // P6.0 options select
}


#pragma vector=TIMER3_B0_VECTOR
__interrupt void TIMER3_B0_ISR(void)
{
 count ++;
 if (count == 5)
 {

     //Turn off GREEN
     P6DIR &= ~BIT1;                     // P6.0 output
     P6SEL0 |= BIT1;                    // GREEN
     P6SEL1 &= ~BIT1;                    // P6.0 options select


     //Turn Off BLUE
     P6DIR &= ~BIT2;                     // P6.0 output
     P6SEL0 |= BIT2;                    // BLUE
     P6SEL1 &= ~BIT2;                    // P6.0 options select

     //Turn Off RED
     P6DIR &= ~BIT0;                     // P6.0 output
     P6SEL0 |= BIT0;                     // RED
     P6SEL1 &= ~BIT0;                    // P6.0 options select

 if (color == 0)
 {

     //Turn on RED
     P6DIR |= BIT0;                     // P6.0 output
     P6SEL0 |= BIT0;                     // RED
     P6SEL1 &= ~BIT0;                    // P6.0 options select

     color = 1;
     count = 0;
 }

     else if(color == 1)
 {
     // Turn on GREEN
     P6DIR |= BIT1;                     // P6.0 output
     P6SEL0 |= BIT1;                    // GREEN
     P6SEL1 &= ~BIT1;                    // P6.0 options select

     //Turn On RED
     P6DIR |= BIT0;                     // P6.0 output
     P6SEL0 |= BIT0;                     // RED
     P6SEL1 &= ~BIT0;                    // P6.0 options select


     color = 2;
     count = 0;
 }

     else if (color == 2)
 {
     // Turn on GREEN
     P6DIR |= BIT1;                     // P6.0 output
     P6SEL0 |= BIT1;                    // GREEN
     P6SEL1 &= ~BIT1;                    // P6.0 options select

     color = 3;
     count = 0;
 }

     else if (color == 3)
 {
     // Turn on GREEN
     P6DIR |= BIT1;                     // P6.0 output
     P6SEL0 |= BIT1;                    // GREEN
     P6SEL1 &= ~BIT1;                    // P6.0 options select

     //Turn On BLUE
     P6DIR |= BIT2;                     // P6.0 output
     P6SEL0 |= BIT2;                    // BLUE
     P6SEL1 &= ~BIT2;                    // P6.0 options select

     color = 4;
     count = 0;
 }

     else if (color == 4)
 {

     //Turn On BLUE
     P6DIR |= BIT2;                     // P6.0 output
     P6SEL0 |= BIT2;                    // BLUE
     P6SEL1 &= ~BIT2;                    // P6.0 options select

     color = 5;
     count = 0;
 }

     else if (color == 5)
 {

     //Turn On RED
     P6DIR |= BIT0;                     // P6.0 output
     P6SEL0 |= BIT0;                     // RED
     P6SEL1 &= ~BIT0;                    // P6.0 options select

     //Turn On BLUE
     P6DIR |= BIT2;                     // P6.0 output
     P6SEL0 |= BIT2;                    // BLUE
     P6SEL1 &= ~BIT2;                    // P6.0 options select

     color = 0;
     count = 0;

 }
 }

}

