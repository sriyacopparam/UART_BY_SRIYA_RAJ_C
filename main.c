/*
 * File:   TX_RX.c
 * Author: User
 *
 * Created on June 6, 2023, 6:25 AM
 */
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <math.h>
#include <pic.h>
//#include<time.h>

#define _XTAL_FREQ 10000000

//char *str[20];

void tx_data( char data)
{ 
    //int seconds =1;
    if(PIR1bits.TXIF == 1)
    {
        
        TXREG = data;
        PIR1bits.TXIF = 0;
        
        __delay_ms(25);
        
        
        }
    
}

void txstr(unsigned char *s)
{
    while(*s){
        tx_data(*s++);
    }
}
void serial_init()
{
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.RCIE=1;
    
    TXSTAbits.CSRC = 0;
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.TRMT = 0;
    TXSTAbits.TX9D = 0;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.SREN = 0;
    RCSTAbits.CREN = 1;
    RCSTAbits.ADDEN = 0;
    RCSTAbits.FERR = 0;
    RCSTAbits.OERR = 0;
    RCSTAbits.RX9D = 0;
    
    SPBRG = 64;
}

void main(void) {
    
    serial_init();
    
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB7 = 0;
    PORTBbits.RB7 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;

    while(1)
    {
        txstr("\n\rFinance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan for predicting that \n\rthe next banking crisis would be triggered by MSME lending saying postmortem is easier than taking action when it was required.\n\rRajan, who had as the chief economist at IMF warned of impending financial crisis of 2008,\n\rin a note to a parliamentary committee warned against ambitious credit targets and loan waivers,\n\rsaying that they could be the sources of next banking crisis.\n\rGovernment should focus on sources of the next crisis, not just the last one.\n\r\n\rIn particular, government should refrain from setting ambitious credit targets or waiving loans. \n\rCredit targets are sometimes achieved by abandoning appropriate due diligence, \n\rcreating the environment for future NPAs, Rajan said in the note. \n\rBoth MUDRA loans as well as the Kisan Credit Card, while popular, have to be examined more closely for potential credit risk. \n\rRajan, who was RBI governor for three years till September 2016, is currently.\n\r");
    }
    return;
}

//void __interrupt() RX()
//{
//    if(PIR1bits.RCIF == 1)
//    {
//        RCSTAbits.CREN = 0;
//        __delay_ms(1);
//        RCSTAbits.CREN = 1;
//        __delay_ms(1);
//        *str[20] = RCREG;
////        str[20] = d;
//        PIR1bits.RCIF = 0;
//    }
//}