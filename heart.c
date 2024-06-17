/*
 * Program to run the Grantronics Heart.
 * Program is Copyright (c) Grantronics Pty Ltd 1999.
 * Permission is hereby granted for unrestricted personal
 * use. For commercial use of this software, except for
 * sale "as is" in a kit, please contact Grantronics Pty Ltd.
 *   info@grantronics.com.au

 * Micro/C command line: d:\mc\cc51 star.c -I -L -P -Z M=T S=:8051rlpt.asm
 *  (requires SLINK.EXE dated later than 12Mar1999)

    Last change:  LG   26 Apr 1999    9:50 pm
 */

 /* This software was written for the Dunfield Development Systems Micro/C
    compiler. See our Web site for a description of Micro/C.
	  http://www.grantronics.com.au */

#include <8051bit.h>	/* 8051 bit manipulation macros */
#include <8051reg.h>	/* 8051 SFR definitions */

#define UCHAR unsigned char

#define ROW1 P1.5
#define ROW2 P1.2
#define ROW3 P1.4
#define ROW4 P1.1
#define ROW5 P1.3
#define ROW6 P1.0

#define COL1 P1.6
#define COL2 P1.7
#define COL3 P3.7
#define COL4 P3.3
#define COL5 P3.2

/****************************************************************************/
/* set a bit to turn on a LED, bit 0 of first byte = led01, 6 bits per byte */
register UCHAR LEDs[5];
register UCHAR *TblPtr;		/* pointer into control data table */
register UCHAR *TblPtr0;	/* pointer into control data table main routine */
register UCHAR LastDelay;	/* last delay value */
register UCHAR LoopCnt;		/* loop counter */
register UCHAR *LoopStart;	/* pointer to loop start */
register UCHAR sp;			/* 'stack pointer', index into Stack */
register UCHAR *Stack[5];	/* 'subroutine' stack */
register UCHAR *Subs[32];	/* pointers to subroutines */

/****************************************************************************/
//UCHAR BitMasks[8] = {1,2,4,8,16,32,64,128};

/****************************************************************************/
/* Table to convert LED number to bit number in LEDs array */
UCHAR LedMap [] = {0x20,0x04,0x10,0x02,0x08,0x01};
/****************************************************************************/
void LedOn(UCHAR led)
{
	LEDs[led/6] |= LedMap[led%6];
}

/****************************************************************************/
void LedOff(UCHAR led)
{
	LEDs[led/6] &= ~(LedMap[led%6]);
}

/****************************************************************************/
void LEDsFill(UCHAR value)
{
	static register UCHAR i;

	for ( i=0; i<5; i++)
		LEDs[i] = value;
}

/****************************************************************************/
void MuxDly(void)
{	/* time for each LED column, about 2ms */
	static register UCHAR dly;
	for ( dly=150; dly; dly--)
		;
}

/****************************************************************************/
void Mux(void)
{	/* do 1 multiplex cycle, about 10ms */

   	P1 = (P1 & 0xc0) | ~LEDs[0];
    clrbit(COL1);	/* on */
   	MuxDly();
    setbit(COL1);	/* off */
   	P1 = (P1 & 0xc0) | ~LEDs[1];
    clrbit(COL2);	/* on */
   	MuxDly();
    setbit(COL2);	/* off */
   	P1 = (P1 & 0xc0) | ~LEDs[2];
    clrbit(COL3);	/* on */
   	MuxDly();
    setbit(COL3);	/* off */
   	P1 = (P1 & 0xc0) | ~LEDs[3];
    clrbit(COL4);	/* on */
   	MuxDly();
    setbit(COL4);	/* off */
   	P1 = (P1 & 0xc0) | ~LEDs[4];
    clrbit(COL5);	/* on */
   	MuxDly();
    setbit(COL5);	/* off */
}

/****************************************************************************/
#define ON		0x00+	/* turn a LED on (1..30) */
#define	OFF 	0x20+	/* turn a LED off (1..30) */
#define ONDEL	0x40+	/* turn a LED on and delay */
#define OFFDEL	0x60+	/* turn a LED off and delay */
#define SUB		0x80+	/* define subroutine start, 0x60..0x6f = 0..15 (value - 0x60) */
#define CALL	0xA0+	/* subroutine call */
#define LOOPCNT 0xC0+	/* define loop start, 0x41..0x4f = 1..15, count = value - 0x40 */
#define LOOP	0xC0	/* back to loop start */
// 0xd0..0xdf spare, maybe 0xc8..0xcf?
#define DELAY   0xe0+	/* DELAY 0: use last delay value, max = 15, 50ms steps */
// 0xf0..0xfb spare
#define RET		0xfc	/* end of subroutine */
#define ALLON   0xfd	/* all LEDs on */
#define ALLOFF  0xfe	/* all LEDs off */
#define END     0xff	/* end of pattern data */

#define FLASH2 0
#define RAND_ON 1
#define RAND_OFF 2
#define DN_OUTER_ON 3
#define DN_OUTER_OFF 4
#define DN_INNER_ON 5
#define DN_INNER_OFF 6
#define UP_OUTER_ON 7
#define UP_OUTER_OFF 8
#define UP_INNER_ON 9
#define UP_INNER_OFF 10
#define ZIGZAG_ON 11
#define ZIGZAG_OFF 12
#define INNER_ON 13
#define OUTER_ON 14
#define THROB 15
#define WORM_LED1 16
#define WORM_LED2 17
#define WORM_LED15 18
#define WORM_LED18 19
#define WORM_OUTER_CW_RT 20
#define WORM_OUTER_CCW_RT 21
#define WORM_OUTER_CCW_LF 22
#define WORM_OUTER_CW_LF 23
#define WORM_INNER_CW_RT 24
#define WORM_INNER_CCW_RT 25
#define WORM_INNER_CCW_LF 26
#define WORM_INNER_CW_LF 27
#define POUR_DN_ON 28
#define POUR_DN_OFF 29


UCHAR data[] = {

/* subroutines */
				SUB FLASH2,
                /* flashes */
				LOOPCNT 2,
				ALLOFF,DELAY 8,
				ALLON,DELAY 15,
				LOOP,
				RET,

				SUB RAND_ON,
				/* Random on */
				ALLOFF,
				5,DELAY 2,
                ONDEL 24,
				ONDEL 13,
				ONDEL 2,
				ONDEL 21,
				ONDEL 10,
				ONDEL 29,
				ONDEL 18,
				ONDEL 7,
				ONDEL 26,
				ONDEL 15,
				ONDEL 4,
				ONDEL 23,
				ONDEL 12,
				ONDEL 1,
				ONDEL 20,
				ONDEL 9,
				ONDEL 28,
				ONDEL 17,
				ONDEL 6,
				ONDEL 25,
				ONDEL 14,
				ONDEL 3,
				ONDEL 22,
				ONDEL 11,
				ONDEL 30,
				ONDEL 19,
				ONDEL 8,
				ONDEL 27,
				ONDEL 16,
				DELAY 10,
				DELAY 10,
				/* now all on */
				RET,

				SUB RAND_OFF,
				/* Random off */
				OFF 4,DELAY 2,
				OFFDEL 23,
				OFFDEL 12,
				OFFDEL 1,
				OFFDEL 20,
				OFFDEL 9,
				OFFDEL 28,
				OFFDEL 17,
				OFFDEL 6,
				OFFDEL 25,
				OFFDEL 14,
				OFFDEL 3,
				OFFDEL 22,
				OFFDEL 11,
				OFFDEL 30,
				OFFDEL 19,
				OFFDEL 8,
				OFFDEL 27,
				OFFDEL 16,
				OFFDEL 5,
				OFFDEL 24,
				OFFDEL 13,
				OFFDEL 2,
				OFFDEL 21,
				OFFDEL 10,
				OFFDEL 29,
				OFFDEL 18,
				OFFDEL 7,
				OFFDEL 26,
				OFFDEL 15,
				DELAY 15,
				/* now all off */
				RET,

				SUB DN_OUTER_ON,
				/* cascade outer on */
				2,DELAY 4,
				29,ONDEL 4,
				30,ONDEL 6,
				28,ONDEL 8,
				26,ONDEL 10,
				24,ONDEL 12,
				22,ONDEL 14,
				20,ONDEL 16,
				ONDEL 18,
				/* now all outer on */
				RET,

				SUB DN_OUTER_OFF,
				/* Heart outer off */
				OFF 2,DELAY 4,
				OFF 29,OFFDEL 4,
				OFF 30,OFFDEL 6,
				OFF 28,OFFDEL 8,
				OFF 26,OFFDEL 10,
				OFF 24,OFFDEL 12,
				OFF 22,OFFDEL 14,
				OFF 20,OFFDEL 16,
				OFFDEL 18,
				/* now all outer off */
				RET,

				SUB DN_INNER_ON,
				/* Heart inner on */
				1,DELAY 4,
				27,ONDEL 3,
				25,ONDEL 5,
				23,ONDEL 7,
				21,ONDEL 9,
				19,ONDEL 11,
				17,ONDEL 13,
				ONDEL 15,
				/* now all inner on */
				RET,

				SUB DN_INNER_OFF,
				/* Heart inner off */
				OFF 1,DELAY 4,
				OFF 27,OFFDEL 3,
				OFF 25,OFFDEL 5,
				OFF 23,OFFDEL 7,
				OFF 21,OFFDEL 9,
				OFF 19,OFFDEL 11,
				OFF 17,OFFDEL 13,
				OFFDEL 15,
				/* now all inner off */
				RET,

				SUB UP_OUTER_ON,
				/* fountain outer on */
				18,DELAY 4,
				20,ONDEL 16,
				22,ONDEL 14,
				24,ONDEL 12,
				26,ONDEL 10,
				28,ONDEL 8,
				30,ONDEL 6,
				29,ONDEL 4,
				ONDEL 2,
				/* now all outer on */
				RET,

				SUB UP_OUTER_OFF,
				/* fountain outer off */
				OFF 18,DELAY 4,
				OFF 20,OFFDEL 16,
				OFF 22,OFFDEL 14,
				OFF 24,OFFDEL 12,
				OFF 26,OFFDEL 10,
				OFF 28,OFFDEL 8,
				OFF 30,OFFDEL 6,
				OFF 29,OFFDEL 4,
				OFFDEL 2,
				/* now all outer off */
				RET,

				SUB UP_INNER_ON,
				/* Heart inner on */
				15,DELAY 4,
				17,ONDEL 13,
				19,ONDEL 11,
				21,ONDEL 9,
				23,ONDEL 7,
				25,ONDEL 5,
				27,ONDEL 3,
				ONDEL 1,
				/* now all inner on */
				RET,

				SUB UP_INNER_OFF,
				/* Heart inner off */
				OFF 15,DELAY 4,
				OFF 17,OFFDEL 13,
				OFF 19,OFFDEL 11,
				OFF 21,OFFDEL 9,
				OFF 23,OFFDEL 7,
				OFF 25,OFFDEL 5,
				OFF 27,OFFDEL 3,
				OFFDEL 1,
				/* now all inner on */
				RET,

				SUB ZIGZAG_ON,
				/* zig-zag on, assumes all off, top to bottom */
				1,DELAY 4,
				ONDEL 2,
				3,ONDEL 27,
				4,ONDEL 29,
				5,ONDEL 25,
				6,ONDEL 30,
				8,ONDEL 28,
				7,ONDEL 23,
				10,ONDEL 26,
				9,ONDEL 21,
				12,ONDEL 24,
				11,ONDEL 19,
				14,ONDEL 22,
				13,ONDEL 17,
				16,ONDEL 20,
				ONDEL 15,
				18,DELAY 10,DELAY 10,
				RET,

				SUB ZIGZAG_OFF,
				/* zig-zag off, assumes all on, top to bottom */
				OFF 1,DELAY 4,
				OFFDEL 2,
				OFF 3,OFFDEL 27,
				OFF 4,OFFDEL 29,
				OFF 5,OFFDEL 25,
				OFF 6,OFFDEL 30,
				OFF 8,OFFDEL 28,
				OFF 7,OFFDEL 23,
				OFF 10,OFFDEL 26,
				OFF 9,OFFDEL 21,
				OFF 12,OFFDEL 24,
				OFF 11,OFFDEL 19,
				OFF 14,OFFDEL 22,
				OFF 13,OFFDEL 17,
				OFF 16,OFFDEL 20,
				OFFDEL 15,
				OFF 18,DELAY 10,
				RET,

				SUB INNER_ON,
				/* Heart all inner on */
				1,3,5,7,9,11,13,15,17,19,21,23,25,27,
				/* now all inner on */
				RET,

				SUB OUTER_ON,
				/* Heart all outer on */
				2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,29,
				/* now all outer on */
				RET,

				SUB THROB,
				/* 4 throbs, assumes all on at start */
				/* don't call from within a loop */
				LOOPCNT 4,
				ALLOFF,
				DELAY 10,
				CALL INNER_ON,		/* inner on */
				DELAY 6,
				CALL OUTER_ON,		/* outer on */
				DELAY 14,
				LOOP,
				RET,

/* worms are half only, assume it may have come from any other half */
/* To jump from inner to outer or outer to inner, you must turn on
    the first LED using one of the following WORM_LEDx subroutines */
				SUB WORM_LED2,
				OFF 28,OFF 5,OFF 25,OFF 8,ONDEL 2,
				RET,

				SUB WORM_LED1,
				OFF 7,OFF 23,OFF 6,OFF 30,ONDEL 1,
				RET,

				SUB WORM_LED15,
				OFF 14,OFF 22,OFF 21,OFF 9,ONDEL 15,
				RET,

				SUB WORM_LED18,
				OFF 12,OFF 24,OFF 11,OFF 19,ONDEL 18,
				RET,

				SUB WORM_OUTER_CW_RT,
				OFF 30,OFF 3,OFF 27,ONDEL 4,
				OFF 29,OFF 1,ONDEL 6,
				OFF 2,ONDEL 8,
				OFF 4,ONDEL 10,
				OFF 6,ONDEL 12,
				OFF 8,ONDEL 14,
				OFF 10,ONDEL 16,
				CALL WORM_LED18,
				RET,

				SUB WORM_OUTER_CCW_RT,
				OFF 13,OFF 17,OFF 22,ONDEL 16,
				OFF 20,OFF 15,ONDEL 14,
				OFF 18,ONDEL 12,
				OFF 16,ONDEL 10,
				OFF 14,ONDEL 8,
				OFF 12,ONDEL 6,
				OFF 10,ONDEL 4,
				CALL WORM_LED2,
				RET,

				SUB WORM_OUTER_CW_LF,
				OFF 14,OFF 13,OFF 17,ONDEL 20,
				OFF 16,OFF 15,ONDEL 22,
				OFF 18,ONDEL 24,
				OFF 20,ONDEL 26,
				OFF 22,ONDEL 28,
				OFF 24,ONDEL 30,
				OFF 26,ONDEL 29,
				CALL WORM_LED2,
				RET,

				SUB WORM_OUTER_CCW_LF,
				OFF 6,OFF 3,OFF 27,ONDEL 29,
				OFF 1,OFF 4,ONDEL 30,
				OFF 2,ONDEL 28,
				OFF 29,ONDEL 26,
				OFF 30,ONDEL 24,
				OFF 28,ONDEL 22,
				OFF 26,ONDEL 20,
				CALL WORM_LED18,
				RET,

				SUB WORM_INNER_CW_RT,
				OFF 25,OFF 29,OFF 4,ONDEL 3,
				OFF 27,OFF 2,ONDEL 5,
				OFF 1,ONDEL 7,
				OFF 3,ONDEL 9,
				OFF 5,ONDEL 11,
				OFF 7,ONDEL 13,
				CALL WORM_LED15,
				RET,

				SUB WORM_INNER_CCW_RT,
				OFF 19,OFF 20,OFF 16,ONDEL 13,
				OFF 18,OFF 17,ONDEL 11,
				OFF 15,ONDEL 9,
				OFF 13,ONDEL 7,
				OFF 11,ONDEL 5,
				OFF 9,ONDEL 3,
				CALL WORM_LED1,
				RET,

				SUB WORM_INNER_CW_LF,
				OFF 11,OFF 16,OFF 20,ONDEL 17,
				OFF 13,OFF 18,ONDEL 19,
				OFF 15,ONDEL 21,
				OFF 17,ONDEL 23,
				OFF 19,ONDEL 25,
				OFF 21,ONDEL 27,
				CALL WORM_LED1,
				RET,

				SUB WORM_INNER_CCW_LF,
				OFF 5,OFF 4,OFF 29,ONDEL 27,
				OFF 2,OFF 3,ONDEL 25,
				OFF 1,ONDEL 23,
				OFF 27,ONDEL 21,
				OFF 25,ONDEL 19,
				OFF 23,ONDEL 17,
				CALL WORM_LED15,
				RET,

				SUB POUR_DN_ON,
				/* pour on down */
				30,29,4,6,DELAY 5,
                25,27,2,3,ONDEL 5,
                28,23,1,7,ONDEL 8,
                26,21,9,ONDEL 10,
                24,19,11,ONDEL 12,
                22,17,13,ONDEL 14,
                20,15,ONDEL 16,
                18,DELAY 10,DELAY 10,
				RET,

				SUB POUR_DN_OFF,
				/* pour off down */
				OFF 30,OFF 29,OFF 4,OFF 6,DELAY 5,
                OFF 25,OFF 27,OFF 2,OFF 3,OFFDEL 5,
                OFF 28,OFF 23,OFF 1,OFF 7,OFFDEL 8,
                OFF 26,OFF 21,OFF 9,OFFDEL 10,
                OFF 24,OFF 19,OFF 11,OFFDEL 12,
                OFF 22,OFF 17,OFF 13,OFFDEL 14,
                OFF 20,OFF 15,OFFDEL 16,
                OFF 18,DELAY 10,
				RET,

//#define OUTER_OFF 8
//				SUB OUTER_OFF,
//				/* Heart all outer off */
//				OFF 2,OFF 4,OFF 6,OFF 8,OFF 10,OFF 12,OFF 14,OFF 16,
//				OFF 18,OFF 20,OFF 22,OFF 24,OFF 26,OFF 28,OFF 30,OFF 29,
//				/* now all outer off */
//				RET,

//#define INNER_OFF 10
//				SUB INNER_OFF,
//				/* Heart all inner off */
//				OFF 1,OFF 3,OFF 5,OFF 7,OFF 9,OFF 11,OFF 13,OFF 15,
//				OFF 17,OFF 19,OFF 21,OFF 23,OFF 25,OFF 27,
//				/* now all inner off */
//				RET,

/* End of subroutines (first instruction after RET is not SUB x) */
/*********************************************************************/
/* Main run-time loop */
				CALL RAND_ON,       /* Random on */
                CALL FLASH2,        /* 2 flashes */
				/* now all on */

				CALL DN_OUTER_OFF,	/* outer off */
				CALL UP_INNER_OFF,	/* inner off */
				CALL DN_OUTER_ON,	/* outer on */
				CALL UP_INNER_ON,	/* inner on */
				/* now all on */
				DELAY 15,

				CALL THROB,	        /* throbs, leaves all on */

				CALL UP_OUTER_OFF,	/* outer off */
				CALL DN_INNER_OFF,	/* inner off */
				CALL UP_OUTER_ON,	/* outer on */
				CALL DN_INNER_ON, 	/* inner on */
				/* now all on */
				DELAY 15,

				CALL ZIGZAG_OFF,
				/* now all off */

				/* speed changing worm */
				DELAY 4,			/* set delay for all following worms */
				LOOPCNT 1,
				CALL WORM_OUTER_CCW_LF,
                CALL WORM_OUTER_CCW_RT,
				LOOP,
				DELAY 3,			/* set delay for all following worms */
				LOOPCNT 2,
				CALL WORM_OUTER_CCW_LF,
                CALL WORM_OUTER_CCW_RT,
				LOOP,
				DELAY 2,			/* set delay for all following worms */
				LOOPCNT 3,
				CALL WORM_OUTER_CCW_LF,
                CALL WORM_OUTER_CCW_RT,
				LOOP,
				DELAY 1,			/* set delay for all following worms */
				LOOPCNT 4,
				CALL WORM_OUTER_CCW_LF,
                CALL WORM_OUTER_CCW_RT,
				LOOP,
				DELAY 2,			/* set delay for all following worms */
				LOOPCNT 3,
				CALL WORM_OUTER_CCW_LF,
                CALL WORM_OUTER_CCW_RT,
				LOOP,
				DELAY 3,			/* set delay for all following worms */
				LOOPCNT 2,
				CALL WORM_OUTER_CCW_LF,
                CALL WORM_OUTER_CCW_RT,
				LOOP,
				DELAY 4,			/* set delay for all following worms */
				LOOPCNT 1,
				CALL WORM_OUTER_CCW_LF,
                CALL WORM_OUTER_CCW_RT,
				LOOP,
				OFFDEL 8,				/* make tail disappear */
				OFFDEL 6,
				OFFDEL 4,
				OFF 2,DELAY 8,
				/* now all off */

				/* Clockwise draw */
				LOOPCNT 2,
				/* outside first, then inside */
				2,DELAY 3,
				ONDEL 4,
				ONDEL 6,
				ONDEL 8,
				ONDEL 10,
				ONDEL 12,
				ONDEL 14,
				ONDEL 16,
				ONDEL 18,
				ONDEL 20,
				ONDEL 22,
				ONDEL 24,
				ONDEL 26,
				ONDEL 28,
				ONDEL 30,
				ONDEL 29,       	/* all outside on */
				ONDEL 1,
				ONDEL 3,
				ONDEL 5,
				ONDEL 7,
				ONDEL 9,
				ONDEL 11,
				ONDEL 13,
				ONDEL 15,
				ONDEL 17,
				ONDEL 19,
				ONDEL 21,
				ONDEL 23,
				ONDEL 25,
				27,DELAY 15,
				/* now all on */

				/* Clockwise erase */
				/* outside first, then inside */
				OFF 2,DELAY 3,
				OFFDEL 4,
				OFFDEL 6,
				OFFDEL 8,
				OFFDEL 10,
				OFFDEL 12,
				OFFDEL 14,
				OFFDEL 16,
				OFFDEL 18,
				OFFDEL 20,
				OFFDEL 22,
				OFFDEL 24,
				OFFDEL 26,
				OFFDEL 28,
				OFFDEL 30,
				OFFDEL 29,	/* all outside on */
				OFFDEL 1,
				OFFDEL 3,
				OFFDEL 5,
				OFFDEL 7,
				OFFDEL 9,
				OFFDEL 11,
				OFFDEL 13,
				OFFDEL 15,
				OFFDEL 17,
				OFFDEL 19,
				OFFDEL 21,
				OFFDEL 23,
//				OFFDEL 25,
//				OFFDEL 27, //DELAY 10,
				CALL WORM_LED1,
				CALL WORM_INNER_CW_RT,
				CALL WORM_INNER_CW_LF,
				CALL WORM_INNER_CW_RT,
				CALL WORM_INNER_CW_LF,
				OFFDEL 23,				/* make tail disappear */
				OFFDEL 25,
				OFFDEL 27,
				OFF 1,DELAY 10,
				LOOP,
				/* now all off */

//				LOOPCNT 2,
				CALL POUR_DN_ON,
				CALL THROB,
				CALL POUR_DN_OFF,
//				LOOP,
				/* now all off */

				CALL ZIGZAG_ON,     /* zig-zag on */
				CALL THROB,
				CALL RAND_OFF,		/* Random off */
				/* now all off */

				/* light chaser or worm */
				DELAY 3,			/* set delay for all following worms */
				LOOPCNT 2,
				CALL WORM_OUTER_CW_RT,
				CALL WORM_LED15,
				CALL WORM_INNER_CCW_RT,
				CALL WORM_INNER_CCW_LF,
				CALL WORM_LED18,
				CALL WORM_OUTER_CW_LF,
				CALL WORM_LED1,
				CALL WORM_INNER_CW_RT,
				CALL WORM_LED18,
				CALL WORM_OUTER_CCW_RT,
				CALL WORM_LED1,
				CALL WORM_INNER_CCW_LF,
				CALL WORM_LED18,
				CALL WORM_OUTER_CW_LF,	/* last so the tail disappears correctly */
				LOOP,
				OFFDEL 28,				/* make tail disappear */
				OFFDEL 30,
				OFFDEL 29,
				OFF 2,DELAY 8,
				/* now all off */

//                CALL FLASH2,     /* 2 flashes */
				CALL POUR_DN_ON,
				CALL THROB,	            /* throbs */

				CALL UP_OUTER_OFF,
				CALL UP_INNER_OFF,
				CALL UP_INNER_ON,
				CALL DN_OUTER_ON,
				DELAY 15,
				CALL POUR_DN_OFF,
				CALL DN_INNER_ON,
				CALL DN_OUTER_ON,
				DELAY 15,
				CALL THROB,	            /* throbs */
				CALL ZIGZAG_OFF,    	/* zig-zag off */

				END     				/* end of data */
                };


/****************************************************************************/
UCHAR GetByte (void)
{
	return (*(UCHAR*)TblPtr++);	/* force pointer to access code memory */
}

/****************************************************************************/
main()
{
	static register UCHAR c;	/* byte from data table */
	static register UCHAR i;	/* loop counter */

    LEDsFill(0x00);     /* clear LEDs array */
	LastDelay = 1;
	sp = 0;

	TblPtr = data;	/* start reading from the table */
	/* scan for subroutines */
	while ( 1 )
	{   /* A SUB must be the first byte or the first byte after a RET */
		c = GetByte();		/* increments TblPtr */
		if ( (c & 0xe0) == 0x80 )
		{	/* start of a SUB */
			Subs[c & 0x1f] = TblPtr;	/* save subroutine address + 1 */
    		/* scan for the RET */
			while (	RET != (c = GetByte()) )	/* increments TblPtr */
				;
		}
		else
		{	/* must be first byte after SUBs */
			TblPtr0 = --TblPtr; /* point back to this byte */
			break;			/* go to normal run-time loop */
		}
	}

	while ( 1 )
	{	/* main data processing loop */
		c = GetByte();		/* increments TblPtr */

		/* test for specific values first */
		if ( !c )
			continue;	/* ignore byte = 0 */

		if ( c == LOOP )
        {
			if ( --LoopCnt )
    		    TblPtr = LoopStart;
			continue;
		}

		if ( c == ALLON )
		{
            LEDsFill(0x3f);         /* only low 6 bits used */
			continue;
		}

		if ( c == ALLOFF )
		{
            LEDsFill(0x00);         /* only low 6 bits used */
			continue;
		}

		if ( c == END )
        {
		    TblPtr = TblPtr0;		/* back to the start */
			continue;
		}

		if ( c == RET )
        {
			TblPtr = Stack[--sp];	/* fetch 'return' address */
			continue;
		}

		/* now test for block values */
		/* test for 0x00 to 0x1f */
    	if ( !(c & 0xe0) )
    	{	/* turn a LED on */
    		LedOn(--c);
    		continue;
    	}
        /* test for 0x00 to 0x3f but 00 to 1f already tested */
    	if ( !(c & 0xc0) )
    	{	/* turn a LED off */
    		LedOff((--c)&0x1f);
    		continue;
    	}
        /* test for 0x00..0x1f and 0x40..0x5f but 00..1f already tested */
    	if ( !(c & 0xa0) )
    	{	/* turn a LED on and delay */
    		LedOn((--c)&0x1f);
			goto DoDelay;
    	}
        /* test for 0x00..0x7f but 00..5f already tested */
    	if ( !(c & 0x80) )
    	{	/* turn a LED off and delay */
    		LedOff((--c)&0x1f);
			goto DoDelay;
    	}

    	if ( (c & 0xf0) == LOOP )
    	{	/* loop start */
			LoopCnt = c & 0x0f;
            LoopStart = TblPtr;		/* TblPtr already updated */
    		continue;
    	}

    	if ( (c & 0xe0) == 0xA0 )
    	{	/* subroutine call */
			Stack[sp++] = TblPtr;	/* save 'return' address */
			TblPtr = Subs[c & 0x1f]; /* load new code address */
			/* should validate TblPtr ( > data) */
    		continue;
    	}

		/* all defined values decoded now except delay */
		if ( c & 0x80 )
		{	/* must be delay count */
			/* if the delay is 0 (0xe0), use last known delay value */
			if ( c != 0xe0 )
    			LastDelay = c&0x0f;
DoDelay:
			for ( i=LastDelay*5; i; i--)
			{
    			Mux();	/* do a mux cycle */
			}
			continue;
		}
	}	/* end of main loop */
}

/****************************************************************************/

