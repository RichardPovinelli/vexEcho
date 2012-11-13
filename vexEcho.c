#include <OpenVex.h>
#include <limits.h>
#include <stdio.h>
#include "vexEcho.h"

void main(void) {
  unsigned char c = 0;

  controller_init();

  //controller_in_autonomous_mode();// see Lib/master.c
  controller_begin_autonomous_mode();

  printf("\n\"Hello, world!\"\n\t - Rex the Vex\n\n");

  while (TRUE) {
     if (usartGetChar(&c)) { // If there is a character to get...
        // we're in!
        printf("\nif (usartGetChar(&c))");
        // print the character that was received
        usart_putc(c);
     }

     controller_submit_data(NO_WAIT);
  } //while
} //main

unsigned char usartDataReady(void) {
    // will return 0 or 1
    return PIR1bits.RCIF;
}

int usartGetChar(char * c) {
    // if data is ready, newdata will be 1
    unsigned char newdata = usartDataReady();
    // Debugging:
    //printf("\nIN USARTGETCHAR!");
    if (newdata) {
        // put the value of the register into c
        *c = RCREG1;
        printf("\nif: %c",(char)RCREG1);
        //printf("\nor: %c",(char)rxbyte);
        return 1;
    }
    // fail:
    return 0;
}
