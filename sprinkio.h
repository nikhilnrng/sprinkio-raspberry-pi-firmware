#ifndef SPRINKIO_H
#define SPRINKIO_H

#define BCM2835_NO_DELAY_COMPATIBILITY

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <bcm2835.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <wiringPi.h>
#include <time.h>
#include <sys/time.h>

#include "structs.h"
#include "settings.h"
#include "raspberry_pi.h"
#include "helper.h"
#include "uart.h"
#include "atmel.h"
#include "lcd.h"
#include "menu.h"
#include "rotary_encoder.h"
#include "button.h"
#include "system.h"

#endif
