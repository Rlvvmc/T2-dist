#include <inttypes.h> 
#include <vector>
#include "onewire.h"

#include "digital.h"
#include "debug.h"


class DS18B20 {

private:
	ONEWIRE *onewire;
	char CRC (char end[]);
	void capturaBit (int posicao, char v[], int valor);
	
public:
	DS18B20 (gpio_num_t pino);
	float readTemp (void);
		void programa (void);
	float readTargetTemp (char end[]);
	
	void init (void);
	void init2 (void);
	void fazScan(void);
	void scanAddresses(uint64_t bits, int arrPos, std::vector<uint64_t> &bitsVector, int numSens);



};