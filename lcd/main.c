#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_gpio.h"
#include "math.h"
#define LCDPORT GPIO_PORTB_BASE // LCD’nin bacaklarýna gidecek baðlantýlar.
#define RS GPIO_PIN_0           // PORTD.0 pini   1
#define E GPIO_PIN_1            // PORTD.1 pini   2
#define PORTD GPIO_PORTB_BASE
void Lcd_Komut(unsigned char);              //Lcd ye komut göndermeye yarar
void Lcd_Temizle(void);                     //Lcd ekranýný temizler
void Lcd_SatirveSutunaGit(char);       //Kursorü istenilen yere gönderir
void Lcd_init(void);                        //Lcd baþlangýç ayarlarý
void Lcd_Tek_Karakter_Yaz(unsigned char);
int main(void)
{
    SysCtlClockSet (SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)=GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR)=0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)=0;
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,0xFF);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1);

//ÝLK SATIR BURDAN BAÞLIYOR

    GPIOPinWrite(LCDPORT,0XFF, 0x07F);
    Lcd_init();
    GPIOPinWrite(PORTD,RS,0);
    GPIOPinWrite(PORTD,E,1);
    SysCtlDelay(100000);
    GPIOPinWrite(LCDPORT,0XFF, 0x83);
    GPIOPinWrite(PORTD,E,0);
    GPIOPinWrite(PORTD,RS,1);
    GPIOPinWrite(PORTD,E,1);
    SysCtlDelay(100000);
    Lcd_SatirveSutunaGit(1);
    SysCtlDelay(100000);
    Lcd_Tek_Karakter_Yaz(0x41);          //data=41h EKRANA A YAZ
}

void Lcd_init()
{
    GPIOPinWrite(PORTD,RS,0);
    SysCtlDelay(100000);
    Lcd_Komut(0x30);
    Lcd_Komut(0x30);
    Lcd_Komut(0x30);
    Lcd_Komut(0x3c);
    Lcd_Komut(0x0f);
    Lcd_Komut(0x01);
    Lcd_Komut(0x06);
}
void Lcd_Komut(unsigned char c)
{
        GPIOPinWrite(PORTD, E,0);
        SysCtlDelay(100000);
        GPIOPinWrite(LCDPORT,0XFF,c);
        GPIOPinWrite(PORTD, RS,0);
        GPIOPinWrite(PORTD, E,1);
        SysCtlDelay(100000);
}
void Lcd_Temizle(void)
{
        Lcd_Komut(0x01);
        SysCtlDelay(100000);
}
void Lcd_SatirveSutunaGit(char a)
{
    GPIOPinWrite(PORTD,E,0);
    SysCtlDelay(100000);
    GPIOPinWrite(LCDPORT,8,a-1);
    GPIOPinWrite(PORTD,E,1);
    SysCtlDelay(100000);

}
void Lcd_Tek_Karakter_Yaz(unsigned char data)
{
    GPIOPinWrite(PORTD, E,0);
    SysCtlDelay(100000);
    GPIOPinWrite(PORTD, RS,1);
    SysCtlDelay(100000);
    GPIOPinWrite(LCDPORT,0XFF,data);
    GPIOPinWrite(PORTD, E,1);
    SysCtlDelay(100000);
}
