#include <24EP256GP204.h>

#FUSES WDT                      //Watch Dog Timer
#FUSES WPRES32                  //Watch Dog Timer PreScalar 1:32
#FUSES WPOSTS11                 //Watch Dog Timer PostScalar 1:1024
#FUSES NOJTAG                   //JTAG disabled
#FUSES CKSFSM                   //Clock Switching is enabled, fail Safe clock monitor is enabled

#device ICSP=1
#use delay(internal=7.37MHz,restart_wdt)
#pin_select U1TX=PIN_B11
#pin_select U1RX=PIN_B12
#use rs232(UART1, baud=115200, restart_wdt, errors, stream=UART_PORT1)

#use spi(MASTER, SPI1, MODE=0, BITS=8, stream=spi_str, SAMPLE_FALL, MSB_FIRST, BAUD=2000000)


