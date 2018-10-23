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
int b;
int i=0;
int k=0;
void kesmefonksiyonu()
{
    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0)
    {
        while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==1)
        {}
        k+=1;
    }
    if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0)
    {
        while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==1)
        {}
        i+=1;
    }
   // return i,k;
}
void ledyak (int c)
{
    i=0;
    k=0;
    for(b=0;b<15;++b)
        {
         GPIOPinWrite(GPIO_PORTF_BASE,pow(2,c),pow(2,c));
         SysCtlDelay(200000);
         GPIOPinWrite(GPIO_PORTF_BASE,pow(2,c),0);
         SysCtlDelay(200000);
        }
}
int main(void)
{
    IntMasterEnable();//1. ayar
    SysCtlClockSet (SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)=GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR)=0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)=0;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//pull up aktifleþtirme
    GPIOIntTypeSet(GPIO_PORTF_BASE,17,GPIO_FALLING_EDGE);//gpio pin 4 VE PÝN0
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
    GPIOIntRegister(GPIO_PORTF_BASE,kesmefonksiyonu);
    IntEnable(INT_GPIOF);
    while(1)
    {
            if(i==2)
                {
                ledyak(1);
                }
            if(k==3)
                {
                ledyak(2);
                }
    }
}
