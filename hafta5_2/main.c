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
    double time=200000;
    while (1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,4);
        SysCtlDelay(time);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
        SysCtlDelay(time);

        if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0)
        {
            while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0);
            time+=10000;
        }
        if(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0)
        {
            while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0);
            time-=10000;

            if (time<10000)
            {
                time=200000;
            }
        }

        if (time<10000)
        {
            time=200000;
        }


}
}
