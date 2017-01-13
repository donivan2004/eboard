#include <main.h>

#define START PIN_A10
#define SPI_CS PIN_B0
#define DRDY PIN_B13
#define ADC_PDN PIN_B1
#define BT_WKSW PIN_C7
#define BT_WKHW PIN_C8
#define BT_CMD PIN_C9

#define RDATA 0x12
#define RESET 0x06

unsigned int8 data_in[50];
int i, sample_n=0; //, k;
int8 result;
unsigned int16 ch1data;
unsigned int16 ch2data;
//float          ch1data_f;
//float          ch2data_f;
unsigned int16 ch3data;
unsigned int16 ch4data;

int16 out_data_1[500];
int16 out_data_2[500];

#INT_TIMER2
void  timer2_isr(void) 
{
   //fprintf(UART_PORT1, "INT ");
   output_high(START);
}



void main()
{
   setup_timer2(TMR_INTERNAL | TMR_DIV_BY_1, 3684); // 1000 Samples per second
   
   output_high(ADC_PDN);
   output_high(SPI_CS);
   output_low(BT_WKSW);   
   delay_ms(100);   
   output_low(SPI_CS);   
   result = spi_xfer(RESET);
   delay_ms(100);   
   result = spi_xfer(0x11); // SDATAC
   
   //result = spi_xfer(0x47); // Start addr 0x07 + opcode write
   //result = spi_xfer(0x01);  // Write 2 registers
   //result = spi_xfer(0x90); // PD channel
   //result = spi_xfer(0x90); // PD channel
   output_high(SPI_CS);
   
   // Bluetooth Init
   //output_high(BT_CMD);
   output_high(BT_WKSW);
   delay_ms(100);
   fprintf(UART_PORT1, "$$$");
   fprintf(UART_PORT1, "SA,0");
   fprintf(UART_PORT1, "---");
   delay_ms(100);
   
   enable_interrupts(INT_TIMER2);
   enable_interrupts(INTR_GLOBAL);

   while(TRUE)
   {
      if(!input(DRDY))
      {
         //fprintf(UART_PORT1, "DRDY ");
         output_low(SPI_CS); 
         output_low(START);          
         result = spi_xfer(RDATA);
         //data_in[0] = spi_read();
         for(int byte_n = 0; byte_n < 19; byte_n++)
         {
            data_in[byte_n] = spi_xfer(0);
         }         
         output_high(SPI_CS);
                  
         //ch1data = 0;
         //ch2data = 0;
         //ch3data = 0;
         //ch4data = 0;
         ch1data = (data_in[3] << 8) | data_in[4];
         ch2data = (data_in[5] << 8) | data_in[6];
         ch3data = (data_in[7] << 8) | data_in[8];
         ch4data = (data_in[9] << 8) | data_in[10];
         
         out_data_1[sample_n] = (signed int16)ch1data;
         out_data_2[sample_n] = (signed int16)ch2data;
         sample_n++;
      }
      
      if(sample_n >= 100)
      {
         fprintf(UART_PORT1, "b");  
         for(i=0; i<100; i++)
         {
            fprintf(UART_PORT1, "%d,%d,l", (signed int16)out_data_1[i], (signed int16)out_data_2[i]);
         }
         fprintf(UART_PORT1, "e");
         sample_n = 0;
      }
   }

}
