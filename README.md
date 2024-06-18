# Heart Of Love

I once purchased an [electronics kit](https://www.kitsrus.com/k136.html)
from Kitsrus called Heart of Love (kit 136) as a Valentine Day present. 15 years
later, the Heart of Love continues to blink its LEDs in fun patterns. The kit
includes [source code](heart.c) and [schematic](k136.pdf). This repo contains
a JavaScript port. Implementing this code gave me an opportunity to peek and
understand how the flashing patterns were encoded. Interestingly, the original
source code implemented an interpreter to save code space.

Next steps? Maybe I'll emulate the chip (an [Intel 8051](https://en.wikipedia.org/wiki/MCS-51))
or build a keychain-sized clone...

## See it in action

Visit [k136.html](https://www.quaxio.com/heart-of-love/k136.html) in
your browser to see the JavaScript version of Heart of Love.
