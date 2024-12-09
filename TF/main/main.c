#include <stdio.h>
#include "digital.h"
#include "DS18B20.h"
#include "delay.h"

float temperatura1;
float temperatura2;

 

extern "C" void app_main() ;

void printFloat (float f)
{
  char str[20];
 sprintf(str, "%d.%04d\n", (int)f, (int)(f*10000)%10000);
 printf(str);

}

void app_main()
{
  delay_ms(2000);
  printf("\n\nRODANDO\n\n");

  DS18B20 meuSensor = DS18B20(GPIO_NUM_4);
 
 float temp;
 int inteira;
 int fracionaria;

 
 
 meuSensor.init2();
 meuSensor.fazScan();




 meuSensor.programa();
 while (1)
 {   
 	temp = meuSensor.readTemp();
 
 	inteira = temp;
 	fracionaria = (temp - inteira)*100;
 
 	printf("temperatura = %d.%d\n",inteira,fracionaria);
 	delay_ms(1000);
}

 }