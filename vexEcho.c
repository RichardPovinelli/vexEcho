#include <OpenVex.h>
#include <limits.h>
#include <stdio.h>
#include "vexHeartBeat.h"
#define MAX_COUNT 20
#define MAX_HEARTBEAT_DELAY 39063 //ticks/s, 10000/256 * 1000
#define HEART_BEAT 'X' //0x00

void main(void) {
  unsigned char c = 0;
  unsigned long lastHeartBeat = 0;
  unsigned long ticksPerMs = 10000 / 16;

  vex_init();
  usart_init();

  DPRINTF("\nStarting Autonomous mode\n");
  master_begin_autonomous_mode();

  /*
    DPRINTF("Set up timer0\n");
   */
  timer0_set_prescale(TIMER0_PRESCALE_256);
  timer0_mode16();
  //timer0_interrupts_on();
  timer0_start();

  while (TRUE) {
    //DPRINTF("Putting a char to usart\n");
    /*
        delay_sec(1);
     */

    //usart_putc('_'); //debug

    /*
            if (usart_ready()) {
              usart_gets(&c, 1);
              lastHeartBeat = TIMER0_ELAPSED_MS();
              //processInput(c);
            } //if
     */
    printf("T0CON = %X\n", T0CON);
    if (needHeartBeat(lastHeartBeat)) {
      usart_putc(HEART_BEAT);
      //fflush();
      lastHeartBeat = timer0_read32();
    }//if
    delay_msec(100);
  } //while
  /*
      master_end_autonomous_mode();
      DPRINTF("Ending Autonomous mode.\n");
   */
} //main

unsigned char needHeartBeat(unsigned long lastHeartBeat) {
  unsigned long delay = 0;
  unsigned long currentTime = timer0_read32();
  if (currentTime < lastHeartBeat) { //timer wrapped around
    delay = UINT_MAX - lastHeartBeat + currentTime;
  }
  else {
    delay = currentTime - lastHeartBeat;
  } //else

  return MAX_HEARTBEAT_DELAY < delay;
} //needHeartBeat