#include "user.h"
#include <uart.h>
#include <xc.h>

char sbuf[20];//Registro de almacenamiento de temporales.
char sbufb[20];//Registro de almacenamiento de temporales.
void InitUART1(void){//Configuracion de UART1
unsigned int UartMode = 0;
unsigned int UartCtrl = 0;
UartMode =  UART_EN &       //Enable UART
UART_IDLE_CON &     //Continue working when Idle
UART_IrDA_DISABLE & //Not using IrDA
UART_MODE_SIMPLEX & //Not using Flow control
UART_UEN_00 &       //Not using CTS/RTS pins by not setting it up
UART_DIS_WAKE &     //Disable wakeup option
UART_DIS_LOOPBACK & //Not using in loopback mode
UART_DIS_ABAUD &    //Disable ABAUD
UART_NO_PAR_8BIT &  //8bit data with none for parity
UART_BRGH_SIXTEEN & //Clock pulse per bit
UART_UXRX_IDLE_ONE& // UART Idle state is 1
UART_1STOPBIT;      // 1 stop bit
UartCtrl = UART_TX_ENABLE &     //Enable UART transmit
UART_IrDA_POL_INV_ZERO &//sets the pins idle state
UART_SYNC_BREAK_DISABLED &
UART_INT_RX_CHAR &      //Interrupt at every character received
UART_ADR_DETECT_DIS &  //Disabled since not using addressed mode
UART_RX_OVERRUN_CLEAR;  //UART Overrun Bit Clear
ConfigIntUART1( UART_RX_INT_EN & //Enable RX Interrupt
UART_RX_INT_PR2 &        //Set priority level
UART_TX_INT_DIS &        //Disable TX Interrupt
UART_TX_INT_PR0);        //Priority as none
IFS0bits.U1RXIF = 0;
OpenUART1(UartMode,UartCtrl,  39);//UART speed 57600bauds default.
}


void Floattocharsend(float number){//Conversion and send
  int Integerpart=0;
  int i=0;
  int Poscounter=0;
  int Breakpos=0;
  float Decimalpartf=0;
  int Decimalparti=0;
  Integerpart=number;
  Decimalpartf=number-Integerpart;
  Decimalpartf=Decimalpartf*1000;//Two decimal digit
  Decimalparti=Decimalpartf;
  while(Integerpart){//Integer conversion
      sbuf[Poscounter++]=(Integerpart%10)+'0';
      Integerpart=(Integerpart/10);
  }

  for(i=0;i<Poscounter;i++){

      sbufb[(Poscounter-1)-i]=sbuf[i];
 }
  sbufb[Poscounter++]='.';
  Breakpos=Poscounter;
  while(Decimalparti){//Integer conversion
      sbuf[Poscounter]=(Decimalparti%10)+'0';
      Decimalparti=(Decimalparti/10);
      Poscounter++;
  }

 for(i=Breakpos;i<=Poscounter;i++){

      sbufb[i]=sbuf[Poscounter-1];
      Poscounter--;
 }
  
  Poscounter=0;
  i=0;
  while(sbufb[i]!='\0'){//Send character until break character found
      while(BusyUART1());//Wait until TX buffer will be empty.
      putcUART1(sbufb[i]);//Send characters.
      i++;
  }
  i=0;
  putcUART1('\n');//Line Breaker.
  }


void Inttocharsend(int number){//Conversion and send integer.
  int Poscounter=0;
  int i=0;
  while(number){//Integer conversion
      sbuf[Poscounter++]=(number%10)+'0';
      number=(number/10);
  }

  for(i=0;i<Poscounter;i++){

      sbufb[(Poscounter-1)-i]=sbuf[i];
 }
  Poscounter=0;
  i=0;
  while(sbufb[i]!='\0'){//Send character until break character found
      while(BusyUART1());//Wait until TX buffer will be empty.
      putcUART1(sbufb[i]);//Send characters.
      i++;
  }
  i=0;
  putcUART1('\n');//Line Breaker.
  }

void charsend(char *p){//This function sends a specific character to uart.
    char value='o';//Init cah value
    while(value!='\0'&&value>=48&&value<=122){//Wait until EOF detected.
        value=*p;
		while(BusyUART1());//Wait until TX buffer will be empty.
        if(value>=32&&value<=126){
        putcUART1(value);//Send characters to UART.
		}
        p++;
    }
    putcUART1('\n');//Line Breaker.
   
}





