class Heart {
  lastDelay = 1;

  constructor(svg) {
    this.svg = svg;
  }

  async OFF(n) {
    this.svg.getElementById(n).style.fill = "none";
  }

  async ON(n) {
    this.svg.getElementById(n).style.fill = "red";
  }

  async ALLOFF() {
    for (let i = 1; i <= 30; i++) {
      await this.OFF(i);
    }
  }

  async ALLON() {
    for (let i = 1; i <= 30; i++) {
      await this.ON(i);
    }
  }

  async DELAY(n) {
    if (n != 0) {
      this.lastDelay = n;
    }
    await this.sleep(this.lastDelay * 30);
  }

  async OFFDEL(n) {
    await this.OFF(n);
    await this.DELAY(0);
  }

  async ONDEL(n) {
    await this.ON(n);
    await this.DELAY(0);
  }

  async FLASH2() {
    for (let i = 0; i < 2; i++) {
      await this.ALLOFF();
      await this.DELAY(8);
      await this.ALLON();
      await this.DELAY(15);
    }
  }

  async RAND_ON() {
    await this.ALLOFF(5);
    await this.DELAY(2);
    await this.ONDEL(24);
    await this.ONDEL(13);
    await this.ONDEL(2);
    await this.ONDEL(21);
    await this.ONDEL(10);
    await this.ONDEL(29);
    await this.ONDEL(18);
    await this.ONDEL(7);
    await this.ONDEL(26);
    await this.ONDEL(15);
    await this.ONDEL(4);
    await this.ONDEL(23);
    await this.ONDEL(12);
    await this.ONDEL(1);
    await this.ONDEL(20);
    await this.ONDEL(9);
    await this.ONDEL(28);
    await this.ONDEL(17);
    await this.ONDEL(6);
    await this.ONDEL(25);
    await this.ONDEL(14);
    await this.ONDEL(3);
    await this.ONDEL(22);
    await this.ONDEL(11);
    await this.ONDEL(30);
    await this.ONDEL(19);
    await this.ONDEL(8);
    await this.ONDEL(27);
    await this.ONDEL(16);
    await this.ONDEL(5); // THIS IS A BUG IN THE ORIGINAL CODE?
    await this.DELAY(10);
  }

  async RAND_OFF() {
    await this.OFF(4);
    await this.DELAY(2);
    await this.OFFDEL(23);
    await this.OFFDEL(12);
    await this.OFFDEL(1);
    await this.OFFDEL(20);
    await this.OFFDEL(9);
    await this.OFFDEL(28);
    await this.OFFDEL(17);
    await this.OFFDEL(6);
    await this.OFFDEL(25);
    await this.OFFDEL(14);
    await this.OFFDEL(3);
    await this.OFFDEL(22);
    await this.OFFDEL(11);
    await this.OFFDEL(30);
    await this.OFFDEL(19);
    await this.OFFDEL(8);
    await this.OFFDEL(27);
    await this.OFFDEL(16);
    await this.OFFDEL(5);
    await this.OFFDEL(24);
    await this.OFFDEL(13);
    await this.OFFDEL(2);
    await this.OFFDEL(21);
    await this.OFFDEL(10);
    await this.OFFDEL(29);
    await this.OFFDEL(18);
    await this.OFFDEL(7);
    await this.OFFDEL(26);
    await this.OFFDEL(15);
    await this.DELAY(15);
  }

  async DN_OUTER_ON() {
    await this.ON(2);
    await this.DELAY(4);
    await this.ON(29);
    await this.ONDEL(4);
    await this.ON(30);
    await this.ONDEL(6);
    await this.ON(28);
    await this.ONDEL(8);
    await this.ON(26);
    await this.ONDEL(10);
    await this.ON(24);
    await this.ONDEL(12);
    await this.ON(22);
    await this.ONDEL(14);
    await this.ON(20);
    await this.ONDEL(16);
    await this.ONDEL(18);
  }

  async DN_OUTER_OFF() {
    await this.OFF(2);
    await this.DELAY(4);
    await this.OFF(29);
    await this.OFFDEL(4);
    await this.OFF(30);
    await this.OFFDEL(6);
    await this.OFF(28)
    await this.OFFDEL(8)
    await this.OFF(26);
    await this.OFFDEL(10);
    await this.OFF(24);
    await this.OFFDEL(12);
    await this.OFF(22);
    await this.OFFDEL(14);
    await this.OFF(20);
    await this.OFFDEL(16);
    await this.OFFDEL(18);
  }

  async DN_INNER_ON() {
    await this.ON(1);
    await this.DELAY(4);
    await this.ON(27);
    await this.ONDEL(3);
    await this.ON(25);
    await this.ONDEL(5);
    await this.ON(23);
    await this.ONDEL(7);
    await this.ON(21);
    await this.ONDEL(9);
    await this.ON(19);
    await this.ONDEL(11);
    await this.ON(17);
    await this.ONDEL(13);
    await this.ONDEL(15);
  }

  async DN_INNER_OFF() {
    await this.OFF(1)
    await this.DELAY(4)
    await this.OFF(27)
    await this.OFFDEL(3)
    await this.OFF(25)
    await this.OFFDEL(5)
    await this.OFF(23)
    await this.OFFDEL(7)
    await this.OFF(21)
    await this.OFFDEL(9)
    await this.OFF(19)
    await this.OFFDEL(11)
    await this.OFF(17)
    await this.OFFDEL(13)
    await this.OFFDEL(15)
  }

  async UP_OUTER_ON() {
    await this.ON(18);
    await this.DELAY(4);
    await this.ON(20);
    await this.ONDEL(16);
    await this.ON(22);
    await this.ONDEL(14);
    await this.ON(24);
    await this.ONDEL(12);
    await this.ON(26);
    await this.ONDEL(10);
    await this.ON(28);
    await this.ONDEL(8);
    await this.ON(30);
    await this.ONDEL(6);
    await this.ON(29);
    await this.ONDEL(4);
    await this.ONDEL(2);
  }

  async UP_OUTER_OFF() {
    await this.OFF(18);
    await this.DELAY(4);
    await this.OFF(20);
    await this.OFFDEL(16);
    await this.OFF(22);
    await this.OFFDEL(14);
    await this.OFF(24);
    await this.OFFDEL(12);
    await this.OFF(26);
    await this.OFFDEL(10);
    await this.OFF(28);
    await this.OFFDEL(8);
    await this.OFF(30);
    await this.OFFDEL(6);
    await this.OFF(29);
    await this.OFFDEL(4);
    await this.OFFDEL(2);
  }

  async UP_INNER_ON() {
    await this.ON(15);
    await this.DELAY(4);
    await this.ON(17);
    await this.ONDEL(13);
    await this.ON(19);
    await this.ONDEL(11);
    await this.ON(21);
    await this.ONDEL(9);
    await this.ON(23);
    await this.ONDEL(7);
    await this.ON(25);
    await this.ONDEL(5);
    await this.ON(27);
    await this.ONDEL(3);
    await this.ONDEL(1);
  }

  async UP_INNER_OFF() {
    await this.OFF(15);
    await this.DELAY(4);
    await this.OFF(17);
    await this.OFFDEL(13);
    await this.OFF(19);
    await this.OFFDEL(11);
    await this.OFF(21);
    await this.OFFDEL(9);
    await this.OFF(23);
    await this.OFFDEL(7);
    await this.OFF(25);
    await this.OFFDEL(5);
    await this.OFF(27);
    await this.OFFDEL(3);
    await this.OFFDEL(1);
  }

  async ZIGZAG_ON() {
    await this.ON(1);
    await this.DELAY(4);
    await this.ONDEL(2);
    await this.ON(3);
    await this.ONDEL(27);
    await this.ON(4);
    await this.ONDEL(29);
    await this.ON(5);
    await this.ONDEL(25);
    await this.ON(6);
    await this.ONDEL(30);
    await this.ON(8);
    await this.ONDEL(28);
    await this.ON(7);
    await this.ONDEL(23);
    await this.ON(10);
    await this.ONDEL(26);
    await this.ON(9);
    await this.ONDEL(21);
    await this.ON(12);
    await this.ONDEL(24);
    await this.ON(11);
    await this.ONDEL(19);
    await this.ON(14);
    await this.ONDEL(22);
    await this.ON(13);
    await this.ONDEL(17);
    await this.ON(16);
    await this.ONDEL(20);
    await this.ONDEL(15);
    await this.ON(18);
    await this.DELAY(10);
    // removed extra delay?
  }

  async ZIGZAG_OFF() {
    await this.OFF(1);
    await this.DELAY(4);
    await this.OFFDEL(2);
    await this.OFF(3);
    await this.OFFDEL(27);
    await this.OFF(4);
    await this.OFFDEL(29);
    await this.OFF(5);
    await this.OFFDEL(25);
    await this.OFF(6);
    await this.OFFDEL(30);
    await this.OFF(8);
    await this.OFFDEL(28);
    await this.OFF(7);
    await this.OFFDEL(23);
    await this.OFF(10);
    await this.OFFDEL(26);
    await this.OFF(9);
    await this.OFFDEL(21);
    await this.OFF(12);
    await this.OFFDEL(24);
    await this.OFF(11);
    await this.OFFDEL(19);
    await this.OFF(14);
    await this.OFFDEL(22);
    await this.OFF(13);
    await this.OFFDEL(17);
    await this.OFF(16);
    await this.OFFDEL(20);
    await this.OFFDEL(15);
    await this.OFF(18);
    await this.DELAY(10);
  }

  async INNER_ON() {
    await this.ON(1);
    await this.ON(3);
    await this.ON(5);
    await this.ON(7);
    await this.ON(9);
    await this.ON(11);
    await this.ON(13);
    await this.ON(15);
    await this.ON(17);
    await this.ON(19);
    await this.ON(21);
    await this.ON(23);
    await this.ON(25);
    await this.ON(27);
  }

  async OUTER_ON() {
    await this.ON(2);
    await this.ON(4);
    await this.ON(6);
    await this.ON(8);
    await this.ON(10);
    await this.ON(12);
    await this.ON(14);
    await this.ON(16);
    await this.ON(18);
    await this.ON(20);
    await this.ON(22);
    await this.ON(24);
    await this.ON(26);
    await this.ON(28);
    await this.ON(30);
    await this.ON(29);
  }

  async THROB() {
    for (let i = 0; i < 4; i++) {
      await this.ALLOFF();
      await this.DELAY(10);
      await this.INNER_ON();
      await this.DELAY(6);
      await this.OUTER_ON();
      await this.DELAY(14);
    }
  }

  async WORM_LED2() {
    await this.OFF(28);
    await this.OFF(5);
    await this.OFF(25);
    await this.OFF(8);
    await this.ONDEL(2);
  }

  async WORM_LED1() {
    await this.OFF(7);
    await this.OFF(23);
    await this.OFF(6);
    await this.OFF(30);
    await this.ONDEL(1);
  }

  async WORM_LED15() {
    await this.OFF(14);
    await this.OFF(22);
    await this.OFF(21);
    await this.OFF(9);
    await this.ONDEL(15);
  }

  async WORM_LED18() {
    await this.OFF(12);
    await this.OFF(24);
    await this.OFF(11);
    await this.OFF(19);
    await this.ONDEL(18);
  }

  async WORM_OUTER_CW_RT() {
    await this.OFF(30);
    await this.OFF(3);
    await this.OFF(27);
    await this.ONDEL(4);
    await this.OFF(29);
    await this.OFF(1);
    await this.ONDEL(6);
    await this.OFF(2);
    await this.ONDEL(8);
    await this.OFF(4);
    await this.ONDEL(10);
    await this.OFF(6);
    await this.ONDEL(12);
    await this.OFF(8);
    await this.ONDEL(14);
    await this.OFF(10);
    await this.ONDEL(16);
    await this.WORM_LED18();
  }

  async WORM_OUTER_CCW_RT() {
    await this.OFF(13);
    await this.OFF(17);
    await this.OFF(22);
    await this.ONDEL(16);
    await this.OFF(20);
    await this.OFF(15);
    await this.ONDEL(14);
    await this.OFF(18);
    await this.ONDEL(12);
    await this.OFF(16);
    await this.ONDEL(10);
    await this.OFF(14);
    await this.ONDEL(8);
    await this.OFF(12);
    await this.ONDEL(6);
    await this.OFF(10);
    await this.ONDEL(4);
    await this.WORM_LED2();
  }

  async WORM_OUTER_CW_LF() {
    await this.OFF(14);
    await this.OFF(13);
    await this.OFF(17);
    await this.ONDEL(20);
    await this.OFF(16);
    await this.OFF(15);
    await this.ONDEL(22);
    await this.OFF(18);
    await this.ONDEL(24);
    await this.OFF(20);
    await this.ONDEL(26);
    await this.OFF(22);
    await this.ONDEL(28);
    await this.OFF(24);
    await this.ONDEL(30);
    await this.OFF(26);
    await this.ONDEL(29);
    await this.WORM_LED2();
  }

  async WORM_OUTER_CCW_LF() {
    await this.OFF(6);
    await this.OFF(3);
    await this.OFF(27);
    await this.ONDEL(29);
    await this.OFF(1);
    await this.OFF(4);
    await this.ONDEL(30);
    await this.OFF(2);
    await this.ONDEL(28);
    await this.OFF(29);
    await this.ONDEL(26);
    await this.OFF(30);
    await this.ONDEL(24);
    await this.OFF(28);
    await this.ONDEL(22);
    await this.OFF(26);
    await this.ONDEL(20);
    await this.WORM_LED18();
  }

  async WORM_INNER_CW_RT() {
    await this.OFF(25);
    await this.OFF(29);
    await this.OFF(4);
    await this.ONDEL(3);
    await this.OFF(27);
    await this.OFF(2);
    await this.ONDEL(5);
    await this.OFF(1);
    await this.ONDEL(7);
    await this.OFF(3);
    await this.ONDEL(9);
    await this.OFF(5);
    await this.ONDEL(11);
    await this.OFF(7);
    await this.ONDEL(13);
    await this.WORM_LED15();
  }

  async WORM_INNER_CCW_RT() {
    await this.OFF(19);
    await this.OFF(20);
    await this.OFF(16);
    await this.ONDEL(13);
    await this.OFF(18);
    await this.OFF(17);
    await this.ONDEL(11);
    await this.OFF(15);
    await this.ONDEL(9);
    await this.OFF(13);
    await this.ONDEL(7);
    await this.OFF(11);
    await this.ONDEL(5);
    await this.OFF(9);
    await this.ONDEL(3);
    await this.WORM_LED1();
  }

  async WORM_INNER_CW_LF() {
    await this.OFF(11);
    await this.OFF(16);
    await this.OFF(20);
    await this.ONDEL(17);
    await this.OFF(13);
    await this.OFF(18);
    await this.ONDEL(19);
    await this.OFF(15);
    await this.ONDEL(21);
    await this.OFF(17);
    await this.ONDEL(23);
    await this.OFF(19);
    await this.ONDEL(25);
    await this.OFF(21);
    await this.ONDEL(27);
    await this.WORM_LED1();
  }

  async WORM_INNER_CCW_LF() {
    await this.OFF(5);
    await this.OFF(4);
    await this.OFF(29);
    await this.ONDEL(27);
    await this.OFF(2);
    await this.OFF(3);
    await this.ONDEL(25);
    await this.OFF(1);
    await this.ONDEL(23);
    await this.OFF(27);
    await this.ONDEL(21);
    await this.OFF(25);
    await this.ONDEL(19);
    await this.OFF(23);
    await this.ONDEL(17);
    await this.WORM_LED15();
  }

  async POUR_DN_ON() {
    await this.ON(30);
    await this.ON(29);
    await this.ON(4);
    await this.ON(6);
    await this.DELAY(5);
    await this.ON(25);
    await this.ON(27);
    await this.ON(2);
    await this.ON(3);
    await this.ONDEL(5);
    await this.ON(28);
    await this.ON(23);
    await this.ON(1);
    await this.ON(7);
    await this.ONDEL(8);
    await this.ON(26);
    await this.ON(21);
    await this.ON(9);
    await this.ONDEL(10);
    await this.ON(24);
    await this.ON(19);
    await this.ON(11);
    await this.ONDEL(12);
    await this.ON(22);
    await this.ON(17);
    await this.ON(13);
    await this.ONDEL(14);
    await this.ON(20);
    await this.ON(15);
    await this.ONDEL(16);
    await this.ON(18);
    await this.DELAY(10);
    await this.DELAY(10);
  }

  async POUR_DN_OFF() {
    await this.OFF(30);
    await this.OFF(29);
    await this.OFF(4);
    await this.OFF(6);
    await this.DELAY(5);
    await this.OFF(25);
    await this.OFF(27);
    await this.OFF(2);
    await this.OFF(3);
    await this.OFFDEL(5);
    await this.OFF(28);
    await this.OFF(23);
    await this.OFF(1);
    await this.OFF(7);
    await this.OFFDEL(8);
    await this.OFF(26);
    await this.OFF(21);
    await this.OFF(9);
    await this.OFFDEL(10);
    await this.OFF(24);
    await this.OFF(19);
    await this.OFF(11);
    await this.OFFDEL(12);
    await this.OFF(22);
    await this.OFF(17);
    await this.OFF(13);
    await this.OFFDEL(14);
    await this.OFF(20);
    await this.OFF(15);
    await this.OFFDEL(16);
    await this.OFF(18);
    await this.DELAY(10);
  }

  sleep = async (timeout) => {
    return new Promise((resolve, reject) => {
      setTimeout(() => resolve(), timeout)
    });
  }

  async go() {
    while (1) {
      await this.RAND_ON();
      await this.FLASH2();
      await this.DN_OUTER_OFF();
      await this.UP_INNER_OFF();
      await this.DN_OUTER_ON();
      await this.UP_INNER_ON();
      await this.DELAY(15);
      await this.THROB();
      await this.UP_OUTER_OFF();
      await this.DN_INNER_OFF();
      await this.UP_OUTER_ON();
      await this.DN_INNER_ON();
      await this.DELAY(15);
      await this.ZIGZAG_OFF();

      await this.DELAY(4);
      // why LOOPCNT 1?
      await this.WORM_OUTER_CCW_LF();
      await this.WORM_OUTER_CCW_RT();

      await this.DELAY(3);
      for (let i = 0; i < 2; i++) {
        await this.WORM_OUTER_CCW_LF();
        await this.WORM_OUTER_CCW_RT();
      }

      await this.DELAY(2);
      for (let i = 0; i < 3; i++) {
        await this.WORM_OUTER_CCW_LF();
        await this.WORM_OUTER_CCW_RT();
      }

      await this.DELAY(1);
      for (let i = 0; i < 4; i++) {
        await this.WORM_OUTER_CCW_LF();
        await this.WORM_OUTER_CCW_RT();
      }

      await this.DELAY(2);
      for (let i = 0; i < 3; i++) {
        await this.WORM_OUTER_CCW_LF();
        await this.WORM_OUTER_CCW_RT();
      }

      await this.DELAY(3);
      for (let i = 0; i < 2; i++) {
        await this.WORM_OUTER_CCW_LF();
        await this.WORM_OUTER_CCW_RT();
      }

      await this.DELAY(4);
      // again LOOPCNT 1 seems wasteful?
      await this.WORM_OUTER_CCW_LF();
      await this.WORM_OUTER_CCW_RT();
      await this.OFFDEL(8) /* make tail disappear */
      await this.OFFDEL(6);
      await this.OFFDEL(4);
      await this.OFF(2);
      await this.DELAY(8);
      /* now all off */

      /* Clockwise draw */
      for (let i = 0; i < 2; i++) {
        /* outside first, then inside */
        await this.ON(2);
        await this.DELAY(3);
        await this.ONDEL(4);
        await this.ONDEL(6);
        await this.ONDEL(8);
        await this.ONDEL(10);
        await this.ONDEL(12);
        await this.ONDEL(14);
        await this.ONDEL(16);
        await this.ONDEL(18);
        await this.ONDEL(20);
        await this.ONDEL(22);
        await this.ONDEL(24);
        await this.ONDEL(26);
        await this.ONDEL(28);
        await this.ONDEL(30);
        await this.ONDEL(29);       	/* all outside on */
        await this.ONDEL(1);
        await this.ONDEL(3);
        await this.ONDEL(5);
        await this.ONDEL(7);
        await this.ONDEL(9);
        await this.ONDEL(11);
        await this.ONDEL(13);
        await this.ONDEL(15);
        await this.ONDEL(17);
        await this.ONDEL(19);
        await this.ONDEL(21);
        await this.ONDEL(23);
        await this.ONDEL(25);
        await this.ON(27);
        await this.DELAY(15);
        /* now all on */
        /* Clockwise erase */
        /* outside first, then inside */
        await this.OFF(2);
        await this.DELAY(3);
        await this.OFFDEL(4);
        await this.OFFDEL(6);
        await this.OFFDEL(8);
        await this.OFFDEL(10);
        await this.OFFDEL(12);
        await this.OFFDEL(14);
        await this.OFFDEL(16);
        await this.OFFDEL(18);
        await this.OFFDEL(20);
        await this.OFFDEL(22);
        await this.OFFDEL(24);
        await this.OFFDEL(26);
        await this.OFFDEL(28);
        await this.OFFDEL(30);
        await this.OFFDEL(29);	/* all outside off (typo in comment) */
        await this.OFFDEL(1);
        await this.OFFDEL(3);
        await this.OFFDEL(5);
        await this.OFFDEL(7);
        await this.OFFDEL(9);
        await this.OFFDEL(11);
        await this.OFFDEL(13);
        await this.OFFDEL(15);
        await this.OFFDEL(17);
        await this.OFFDEL(19);
        await this.OFFDEL(21);
        await this.OFFDEL(23);
        //				OFFDEL 25,
        //				OFFDEL 27, //DELAY 10,
        await this.WORM_LED1();
        await this.WORM_INNER_CW_RT();

        await this.WORM_INNER_CW_LF();
        await this.WORM_INNER_CW_RT();
        await this.WORM_INNER_CW_LF();
        await this.OFFDEL(23);				/* make tail disappear */
        await this.OFFDEL(25);
        await this.OFFDEL(27);
        await this.OFF(1);
        await this.DELAY(10);
      }
      /* now all off */

      await this.POUR_DN_ON();
      await this.THROB();
      await this.POUR_DN_OFF();
      /* now all off */

      await this.ZIGZAG_ON();
      await this.THROB();
      await this.RAND_OFF();
      /* now all off */

      /* light chaser or worm */
      await this.DELAY(3);
      for (let i = 0; i < 2; i++) {
        await this.WORM_OUTER_CW_RT();
        await this.WORM_LED15();
        await this.WORM_INNER_CCW_RT();
        await this.WORM_INNER_CCW_LF();
        await this.WORM_LED18();
        await this.WORM_OUTER_CW_LF();
        await this.WORM_LED1();
        await this.WORM_INNER_CW_RT();
        await this.WORM_LED18();
        await this.WORM_OUTER_CCW_RT();
        await this.WORM_LED1();
        await this.WORM_INNER_CCW_LF();
        await this.WORM_LED18();
        await this.WORM_OUTER_CW_LF(); /* last so the tail disappears correctly */
      }
      await this.OFFDEL(28);				/* make tail disappear */
      await this.OFFDEL(30);
      await this.OFFDEL(29);
      await this.OFF(2);
      await this.DELAY(8);
      /* now all off */

      //                CALL FLASH2,     /* 2 flashes */
      await this.POUR_DN_ON();
      await this.THROB();	            /* throbs */

      await this.UP_OUTER_OFF();
      await this.UP_INNER_OFF();
      await this.UP_INNER_ON();
      await this.DN_OUTER_ON();
      await this.DELAY(15);
      await this.POUR_DN_OFF();
      await this.DN_INNER_ON();
      await this.DN_OUTER_ON();
      await this.DELAY(15);
      await this.THROB();	            /* throbs */
      await this.ZIGZAG_OFF();    	/* zig-zag off */
    }
  }
}


const go = async () => {
  const h = new Heart(svgObject.getSVGDocument());
  h.go();
}
if (svgObject.getSVGDocument()) {
  go();
} else {
  svgObject.onload = go;
}
