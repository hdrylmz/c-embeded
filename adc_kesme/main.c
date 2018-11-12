#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "inc/hw_gpio.h"
#include "driverlib/adc.h"


    void adckesme(void)
    {
        uint32_t ui32ADC0Value[4]; // 4 elemanlý dizimiz
        uint32_t ui32TempAvg;
        uint32_t ui32TempValueC;
        uint32_t ui32TempValueF;

        ADCIntClear(ADC0_BASE, 1);

        ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
        ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
        ui32TempValueC = (((ui32TempAvg*3300)/4095)/10);
        ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;
        ADCProcessorTrigger(ADC0_BASE, 1);
    }

    int main(void)
    {

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN| SYSCTL_XTAL_16MHZ);
    // çevre birimi aktif
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    // sequence 1 -> 4 kanallý -> yazýlým ile çevrim baþlayacak
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR , 0);
    // sequnce ait step ayarlarý // tümünde sadece dahili sýcaklýk sensörü okunuyor.
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0);

    ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 1);
    IntMasterEnable();
    ADCIntClear(ADC0_BASE, 1);
    ADCIntRegister(ADC0_BASE, 1,adckesme);
    ADCIntEnable(ADC0_BASE, 1);
    IntEnable(INT_ADC0SS1);
    ADCProcessorTrigger(ADC0_BASE, 1);

    while(1)
    {

    }
    }
