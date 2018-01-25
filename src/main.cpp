#include <mbed.h>

// Create the LEDs and functions for on and off.
DigitalOut green(LED_GREEN);
DigitalOut red(LED_RED);
DigitalOut blue(LED_BLUE);

void  on(DigitalOut led) { led.write(0); }
void off(DigitalOut led) { led.write(1); }

// Creates a ticker called pit
Ticker  pit;

// Global variables - period and duration can be passed to functions
unsigned int period = 200; // How long LED will be off
unsigned int duration = 100; // How long LED will be on

// Interrupt function
void centisecond(void) {
  // Creates an int that will remember its value.
  static unsigned int cs=0;

  // Count the flashes. Remebers its value
  static unsigned int counter = 0;

  // Flash the LED at different times
  if(counter == 400) {
    period = 100;
    duration = 50;
  }
  if(counter == 600) {
    period = 50;
    duration = 25;
  }
  if(counter == 800) {
    period = 25;
    duration = 13;
  }
  // Turns all lights on for a second
  if(counter == 1000) {
    on(LED_RED);
    on(LED_BLUE);
    period = 200;
    duration = 100;
  }
  // Reset the counter to 0
  if(counter == 1200) counter = 0;


  // Count up by 1 every time the function is called
  cs = (cs+1) % period ;
  
  // LED turns off when count reaches duration
  if( cs<duration )  on(LED_GREEN);
  else {
    off(LED_GREEN);
    off(LED_RED);
    off(LED_BLUE);
  }
  counter++;
}

int main(void) {
  pit.attach_us(centisecond, 10000);

  // Turn the blue and red LED off initially.
  off(LED_BLUE);
  off(LED_RED);

  while(1) {}

}
