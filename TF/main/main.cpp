#include <stdio.h>
#include "DS18B20.h"
#include <bitset>

#define NUMERO_SENSORES 2

extern "C" void app_main();

void app_main(void)
{
    std::bitset<64> addrList[NUMERO_SENSORES] = {0,0};
    std::bitset<64> addrContainer;
    DS18B20 meuSensor = DS18B20(GPIO_NUM_4);
    meuSensor.scanAddresses(0,0,addrList,addrPPtr,1);
    for(int i=0;i<NUMERO_SENSORES;i++)
    {
        printf("val = 0x%" PRIx64 "\n", addrList[i]);
    }
}
