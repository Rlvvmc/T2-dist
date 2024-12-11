#include <stdio.h>
#include "DS18B20.h"
#include <bitset>
#include <iostream>
#include <vector>

#define NUMERO_SENSORES 2

extern "C" void app_main();


void app_main(void)
{
  std::vector<uint64_t> bits; 
  DS18B20 meuSensor = DS18B20(GPIO_NUM_4);
  meuSensor.scanAddresses(0,0, bits, 0);
  meuSensor.scanAddresses(0,0, bits, 1);
  for(int i=0;i<bits.size();i++)
  {
    printf("Sensor %i %lld \n", i+1, bits[i]);
  }
}
