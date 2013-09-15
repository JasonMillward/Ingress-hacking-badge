/**
 *      ATtiny 85/45
 *          _____
 * RESET  -|*    |-  VCC
 *        -|     |-  LED 2
 *        -|     |-  LED 1
 *   GND  -|_____|-  LED 3
 *
 */

#include <Charlieplex.h>
#include <avr/sleep.h>


const int ledpin1 = 2; 
const int ledpin2 = 1; 
const int ledpin3 = 0;

const int pwmDelay = 1;
const int displayDelay = 5350;

uint8_t mcucr1, mcucr2;

#define NUMBER_OF_PINS  3
#define BODS            7
#define BODSE           2


//define pins in the order you want to adress them
byte pins[] = {ledpin1, ledpin2, ledpin3};

//initialize object
Charlieplex charlieplex = Charlieplex(pins , NUMBER_OF_PINS);

//individual 'pins' , adress charlieplex pins as you would adress an array
charliePin led1 = { 0 , 1 }; 
charliePin led2 = { 1 , 2 }; 
charliePin led3 = { 2 , 0 };
charliePin led4 = { 0 , 2 };
charliePin led5 = { 2 , 1 }; 
charliePin led6 = { 1 , 0 };


void setup() {

    // Start the circular led animation
    startAnimation();  

    // Count down ~5 minutes
    countDown();
  
}

void loop() {
    // sleep forever
    PRR |= (1 << PRTIM1) | (1 << PRTIM0) | (1 << PRUSI) | (1 << PRADC);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
     
    sleep_enable(); 

    disable_adc();
    disable_ac();
    disable_watchdog();
    sleep_cpu(); 
    disable_brown_out_detector();
    sleep_disable(); 
    sleep_bod_disable(); 
     
}

void startAnimation() {
    int delSpin = 50;
    
    for( int i = 3; i < displayDelay; i-- ) {
      charlieplex.charlieWrite(led1, HIGH);
      delay( delSpin );
      charlieplex.clear();

      charlieplex.charlieWrite(led2, HIGH);
      delay( delSpin );
      charlieplex.clear();
      
      charlieplex.charlieWrite(led3, HIGH);
      delay( delSpin );
      charlieplex.clear();
      
      charlieplex.charlieWrite(led4, HIGH);
      delay( delSpin );
      charlieplex.clear();
      
      charlieplex.charlieWrite(led5, HIGH);
      delay( delSpin );
      charlieplex.clear();
      
      charlieplex.charlieWrite(led6, HIGH);
      delay( delSpin );
      charlieplex.clear();
       
    }
}

void countDown() {
    for( int i = 6; i < displayDelay; i-- ) {
        displayLED(i);     
    }
}

void displayLED( int ledCount ) {
    for( int i = 0; i < displayDelay; i++ ) {   
        if( ledCount > 5 ) {
            charlieplex.charlieWrite(led6, HIGH);
            delay( pwmDelay );
            charlieplex.clear();
        } else {
            delay( pwmDelay );
        }

        if( ledCount > 4 ) {  
            charlieplex.charlieWrite(led5, HIGH);
            delay( pwmDelay );
            charlieplex.clear();
        } else {
            delay( pwmDelay );
        }

        if( ledCount > 3 ) {
            charlieplex.charlieWrite(led4, HIGH);
            delay( pwmDelay );
            charlieplex.clear();
        } else {
            delay( pwmDelay );
        }

        if( ledCount > 2 ) {
            charlieplex.charlieWrite(led3, HIGH);
            delay( pwmDelay );
            charlieplex.clear();
        } else {
            delay( pwmDelay );
        }

        if( ledCount > 1 ) {
            charlieplex.charlieWrite(led2, HIGH);
            delay( pwmDelay );
            charlieplex.clear();
        } else {
            delay( pwmDelay );
        }

        if( ledCount > 0 ) {
            charlieplex.charlieWrite(led1, HIGH);
            delay( pwmDelay );
            charlieplex.clear();
        } else {
            delay( pwmDelay );
        }
    }  
}

void disable_adc() { 
    cbi(ADCSRA,ADEN); 
}    

void disable_ac() { 
    sbi(ACSR,ACD); 
} 

void disable_watchdog() { 
    cbi(WDTCR,WDIE); 
} 

void disable_brown_out_detector() { 
    mcucr1 = MCUCR | _BV(BODS) | _BV(BODSE); 
    mcucr2 = mcucr1 & ~_BV(BODSE); 
    MCUCR = mcucr1; 
    MCUCR = mcucr2; 
} 
