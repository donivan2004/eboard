#include <main.h>

#include <math.h>
#include <string.h>

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
   int i, j=0, k;
   int8 result;
   unsigned int16 ch1data;
   unsigned int16 ch2data;
   //float          ch1data_f;
   //float          ch2data_f;
   unsigned int16 ch3data;
   unsigned int16 ch4data;
   
   int16 out_data[500][2];

#INT_TIMER2
void  timer2_isr(void) 
{
   //disable_interrupts(INT_TIMER2);
   fprintf(UART_PORT1, "INT ");
   output_high(START);
   if(!input(DRDY))
   {
      output_low(SPI_CS);          
      result = spi_xfer(RDATA);
      //data_in[0] = spi_read();
      for(k = 0; k < 19; k++)
      {
         data_in[i] = spi_xfer(0);
      }         
      output_high(SPI_CS);
      output_low(START);
      
      //fprintf(UART_PORT1, "---------------------------------------------------------------------\n\r");
      
      ch1data = 0;
      ch2data = 0;
      ch3data = 0;
      ch4data = 0;
      ch1data = (data_in[3] << 8) | data_in[4];
      ch2data = (data_in[5] << 8) | data_in[6];
      ch3data = (data_in[7] << 8) | data_in[8];
      ch4data = (data_in[9] << 8) | data_in[10];
      
      //ch2data = ((ch2data - 145300) / 490) + 25;
      //ch1data_f = (3.0 / 32768.0) * (signed int16)ch1data;
      //ch2data_f = (3.0 / 32768.0) * (signed int16)ch2data;
      //for(i = 0; i < 11; i++)
     // {
      //   fprintf(UART_PORT1, "%u\t", data_in[i]);
      //}         
      
      //fprintf(UART_PORT1, "Status: %u,\t%u,\t%u\tch1: %2.5gV,\t ch2: %1.5gV,\t ch3: %u,\t ch4: %u\t", 
      //   data_in[0], data_in[1], data_in[2], ch1data_f, ch2data_f, ch3data, ch4data);
      //fprintf(UART_PORT1, "\n\r");
      //fprintf(UART_PORT1, "\n\r---------------------------------------------------------------------\n\r");
      //delay_ms(1);
      
      //fprintf(UART_PORT1, "b%d,%d,le", (signed int16)ch1data, (signed int16)ch2data);
      //delay_ms(1);
      
      out_data[j][0] = (signed int16)ch1data;
      out_data[j][1] = (signed int16)ch2data;
      j++;
      //delay_ms(5);
   }
   //enable_interrupts(INT_TIMER2);
}

void main()
{
    
   setup_timer2(TMR_INTERNAL | TMR_DIV_BY_1, 3684); // 500,135us   //1842   
   
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

   //output_high(BT_WKHW);
   //delay_ms(1000);
   //fprintf(UART_PORT1, "SR,20060000\r\n");
   //fprintf(UART_PORT1, "R,1\r\n");
   //output_low(BT_CMD);
   // Bluetooth Init
   
   //spi_write(0x10); // RDATAC

   while(TRUE)
   {
      
      fprintf(UART_PORT1, "asd ");
      delay_ms(10);
      
      /*while(j < 100)
      {
         output_high(START);
         if(!input(DRDY))
         {
            output_low(SPI_CS);          
            result = spi_xfer(RDATA);
            //data_in[0] = spi_read();
            for(i = 0; i < 19; i++)
            {
               data_in[i] = spi_xfer(0);
            }         
            output_high(SPI_CS);
            //output_low(START);
            
            //fprintf(UART_PORT1, "---------------------------------------------------------------------\n\r");
            
            ch1data = 0;
            ch2data = 0;
            ch3data = 0;
            ch4data = 0;
            ch1data = (data_in[3] << 8) | data_in[4];
            ch2data = (data_in[5] << 8) | data_in[6];
            ch3data = (data_in[7] << 8) | data_in[8];
            ch4data = (data_in[9] << 8) | data_in[10];
            
            //ch2data = ((ch2data - 145300) / 490) + 25;
            //ch1data_f = (3.0 / 32768.0) * (signed int16)ch1data;
            //ch2data_f = (3.0 / 32768.0) * (signed int16)ch2data;
            //for(i = 0; i < 11; i++)
           // {
            //   fprintf(UART_PORT1, "%u\t", data_in[i]);
            //}         
            
            //fprintf(UART_PORT1, "Status: %u,\t%u,\t%u\tch1: %2.5gV,\t ch2: %1.5gV,\t ch3: %u,\t ch4: %u\t", 
            //   data_in[0], data_in[1], data_in[2], ch1data_f, ch2data_f, ch3data, ch4data);
            //fprintf(UART_PORT1, "\n\r");
            //fprintf(UART_PORT1, "\n\r---------------------------------------------------------------------\n\r");
            //delay_ms(1);
            
            //fprintf(UART_PORT1, "b%d,%d,le", (signed int16)ch1data, (signed int16)ch2data);
            //delay_ms(1);
            
            out_data[j] = (signed int16)ch1data;
            j++;
            delay_ms(5);
         }
      }*/
      
      if(j >= 100)
      {
         fprintf(UART_PORT1, "b");  
         for(i=0; i<100; i++)
         {
            fprintf(UART_PORT1, "%d,%d,l", (signed int16)out_data[i][0], (signed int16)out_data[i][1]);
         }
         fprintf(UART_PORT1, "e");
         j = 0;
      }
      
   }

}
