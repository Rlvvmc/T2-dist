#include <inttypes.h> 
#include "onewire.h"

#include "digital.h"
#include "debug.h"


class DS18B20 {

private:
	ONEWIRE *onewire;
	char CRC (char end[]);
	void capturaBit (int posicao, char v[], int valor);
	void scanAddresses(uint64_t bits, int bitsPos, uint64_t * arr, int * arrPos, int Opp);
public:
	DS18B20 (gpio_num_t pino);
	float readTemp (void);
		void programa (void);
	float readTargetTemp (char end[]);
	
	void init (void);
	void init2 (void);
	void fazScan(void);



};
