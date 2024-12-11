#include <stdio.h>
#include "DS18B20.h"
#include <bitset>
#include <iostream>

#define NUMERO_SENSORES 10

extern "C" void app_main();

unsigned int bintohex(char *digits){
  unsigned int res=0;
  while(*digits)
    res = (res<<1)|(*digits++ -'0');
  return res;
}

void app_main(void)
{
    std::vector<std::vector<bool>> addrArrays;
    std::vector<bool> dummy;
    DS18B20 meuSensor = DS18B20(GPIO_NUM_4);
    meuSensor.scanAddresses(addrArrays,dummy);
     for (int i = 0; i < addrArrays.size(); i++) {
        for(int j=0; j <addrArrays.at(i).size();j++)
        {
          std::cout << addrArrays.at(i).at(j) << ' ';
        }
        printf("\n");
    }
}
