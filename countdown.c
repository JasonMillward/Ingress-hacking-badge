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

#define NUMBER_OF_PINS 3

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


void setup(){

    // Start the circular led animation
    startAnimation();  

    // Count down ~5 minutes
    countDown();
  
}

void loop(){

   // sleep forever
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
   sleep_enable();
   sleep_cput();
   sleep_disable();
}

void startAnimation() {
    int delSpin = 50;
    
    for( int i = 3; i < displayDelay; i-- ) {

      charlieplex.charlieWrite(led1, HIGH);
      delay(delSpin);
      charlieplex.clear();

      charlieplex.charlieWrite(led2, HIGH);
      delay(delSpin);
      charlieplex.clear();
      
      charlieplex.charlieWrite(led3, HIGH);
      delay(delSpin);
      charlieplex.clear();
      
      charlieplex.charlieWrite(led4, HIGH);
      delay(delSpin);
      charlieplex.clear();
      
      charlieplex.charlieWrite(led5, HIGH);
      delay(delSpin);
      charlieplex.clear();
      
      charlieplex.charlieWrite(led6, HIGH);
      delay(delSpin);
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

    if(ledCount>4) {  
      charlieplex.charlieWrite(led5, HIGH);
      delay(pwmDelay);
      charlieplex.clear();
    } else {
      delay(pwmDelay);
    }
    if(ledCount>3) {
      charlieplex.charlieWrite(led4, HIGH);
      delay(pwmDelay);
      charlieplex.clear();
    } else {
      delay(pwmDelay);
    }
    if(ledCount>2) {
      charlieplex.charlieWrite(led3, HIGH);
      delay(pwmDelay);
      charlieplex.clear();
    } else {
      delay(pwmDelay);
    }
    if(ledCount>1) {
      charlieplex.charlieWrite(led2, HIGH);
      delay(pwmDelay);
      charlieplex.clear();
    } else {
      delay(pwmDelay);
    }
    if(ledCount>0) {
      charlieplex.charlieWrite(led1, HIGH);
      delay(pwmDelay);
      charlieplex.clear();
    } else {
      delay(pwmDelay);
    }
  }
  
}
