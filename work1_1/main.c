#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "math.h"
int main(void)
{
    SysCtlClockSet (SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)=GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR)=0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)=0;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//pull up aktifleþtirme
    int b;
    int i=0;
    while(1)
    {
            while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==1);
            while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0);
            i+=1;
            if(i==2)
                {
                i=0;
                for(b=0;b<15;++b)
                    {

                     GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,2);
                     SysCtlDelay(200000);
                     GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0);
                     SysCtlDelay(200000);
                    }
            }
    }
}
