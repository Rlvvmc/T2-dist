#include <stdio.h>
#include "DS18B20.h"
#include <bitset>
#include <iostream>

#define NUMERO_SENSORES 2

extern "C" void app_main();


void app_main(void)
{
    uint64_t addrList[NUMERO_SENSORES] = {0,0};
    int addrPos = 0;
    DS18B20 meuSensor = DS18B20(GPIO_NUM_4);
    meuSensor.scanAddresses(0,0,addrList,0,1);
    for(int i=0;i<NUMERO_SENSORES;i++)
    {
      printf("%lld", addrList[i]);
    }
}
