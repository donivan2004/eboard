#include <24EP256GP204.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOJTAG                   //JTAG disabled
#FUSES CKSFSM                   //Clock Switching is enabled, fail Safe clock monitor is enabled

#device ICSP=1
#use delay(internal=7.37MHz)
#pin_select U1TX=PIN_B11
#pin_select U1RX=PIN_B12
#use rs232(UART1, baud=115200, restart_wdt, errors, stream=UART_PORT1)

#use spi(MASTER, SPI1, MODE=0, BITS=8, stream=spi_str, SAMPLE_FALL, MSB_FIRST, BAUD=2000000)


