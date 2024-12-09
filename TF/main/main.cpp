#include <stdio.h>
#include "DS18B20.h"

#define NUMERO_SENSORES 10

extern "C" void app_main();

void app_main(void)
{
    uint64_t addrList[NUMERO_SENSORES];
    uint64_t* addrLPtr = &addrList[0];
    int addrPos = 0;
    int *addrPPtr = &addrPos;
    DS18B20 meuSensor = DS18B20(GPIO_NUM_4);
    meuSensor.scanAddresses(0,0,addrLPtr,addrPPtr,0);
    for(int i=0;i<NUMERO_SENSORES;i++)
    {
        printf("val = 0x%" PRIx64 "\n", addrList[i]);
    }
}
