#include <stdio.h>
#include "DS18B20.h"
#include <bitset>
#include <iostream>

#define NUMERO_SENSORES 2

extern "C" void app_main();

unsigned int bintohex(char *digits){
  unsigned int res=0;
  while(*digits)
    res = (res<<1)|(*digits++ -'0');
  return res;
}

void app_main(void)
{
    std::bitset<64> addrList[NUMERO_SENSORES] = {0,0};
    std::bitset<64> addrContainer;
    int addrPos = 0;
    int *addrPPtr = &addrPos;
    DS18B20 meuSensor = DS18B20(GPIO_NUM_4);
    meuSensor.scanAddresses(addrContainer,0,addrList,addrPPtr,1);
    for(int i=0;i<NUMERO_SENSORES;i++)
    {
        std::cout << "val = " << std::hex << addrList[i].to_ulong() << std::endl;
    }
}
