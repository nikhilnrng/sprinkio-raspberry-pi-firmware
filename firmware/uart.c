#include "sprinkio.h"

int uart0_filestream;

/**
 * Initialize UART communication
 */
void uart_init() {
  // initialize uart
  uart0_filestream = -1;
  uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (uart0_filestream == -1) {
    printf("Error: Unable to open UART. Ensure it is not in use by another application\n");
  }

  // configure uart
  struct termios options;
  tcgetattr(uart0_filestream, &options);
  options.c_cflag = B9600 | CS8; // 9600 baud rate, 8 bit, no parity, 1 stop
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart0_filestream, TCIFLUSH);
  tcsetattr(uart0_filestream, TCSANOW, &options);
}

/**
 * Transimt a byte over UART
 */
void uart_write(uint8_t data) {
  if (uart0_filestream != -1) {
    int wp = write(uart0_filestream, &data, 1);
    if (wp == -1) {
      printf("Error: UART Tx failed\n");
    }
  }
}

/**
 * Read a byte from UART
 */
uint8_t uart_read() {
  uint8_t data;
  if (uart0_filestream != -1) {
    int rp = read(uart0_filestream, (void*) &data, 1);
    if (rp == -1) {
      printf("Error: UART Rx failed\n");
    } else if (rp == 0) {
      // no data received
      return UART_NO_DATA;
    } else {
      // data received
      return data;
    }
  }
}
