#include "lib.h"
#include  <msp430x20x3.h>

#define gpio1_out(p) P1DIR |= ~(p)
#define gpio1_high(p) P1OUT |= (p)
#define gpio1_low(p) P1OUT &= ~(p)
#define LATCH (1<<2)
#define CLK (1<<1)
#define DATA (1<<0)
#define NXT_L (1<<3)
#define RST_L (1<<4)

static int line = 0;

void next_row(void)
{	
    if (++line == NUM_ROWS)
    {
	gpio1_high(RST_L);
	gpio1_low(RST_L);
	line = 0;
	return;
    }

//    gpio1_high(NXT_L);
//    gpio1_low(NXT_L);
}

void fill_row(void)
{
    int x, y;

    y = line + 1 < NUM_ROWS ? line + 1 : 0;

    gpio1_low(LATCH | NXT_L);

    for (x = NUM_COLS-1; x >= 0; x--)
    {
	  gpio1_low(CLK);
	  
	  if (point(x, y)) 
	    gpio1_high(DATA);
	  else 
	    gpio1_low(DATA);
	    
	  gpio1_high(CLK);
    } 
    gpio1_high(NXT_L);
    gpio1_high(LATCH);
}

void main(void)
{	
    int position_time = 0;

    WDTCTL = WDTPW + WDTHOLD; /* Stop watchdog timer */
    gpio1_out(DATA);
    gpio1_out(CLK);
    gpio1_out(LATCH);
    gpio1_out(NXT_L);
    gpio1_out(RST_L);
    gpio1_low(NXT_L);
    gpio1_low(RST_L);

    for (;;)
    {	
	  fill_row();
	  next_row();
	  if (position_time++ > 40 && line == 0)
	  {
	    update();
	    position_time = 0;
	  }	    
    }
}
