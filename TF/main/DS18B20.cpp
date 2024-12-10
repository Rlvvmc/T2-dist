#ifndef __DS18B20__
#define __DS18B20__

#include "DS18B20.h"
#include "delay.h"

void DS18B20::programa (void)
{
	onewire->reset();
	onewire->writeByte(0x4E);
	onewire->writeByte(0x00);
	onewire->writeByte(0x00);
	onewire->writeByte(0x7F);
	
	
}
void DS18B20::capturaBit (int posicao,char v[], int valor)
{
	unsigned char pbyte = posicao / 8;
	unsigned char pbit  = posicao % 8;
	
	if (valor==1) v[pbyte] |= (1 << pbit);
	else v[pbyte] &= ~(1<< pbit);
}

void DS18B20::scanAddresses(std::bitset<64> bits, int bitsPos, std::bitset<64>* arr, int* arrPos, int Opp)
{
	uint8_t normal = 0, complemento = 0;
	if(Opp == 1)
	{ 
		onewire->reset();
		onewire->writeByte(SEARCH_ROM);
		if(bits != 0x0000000000000000)
		{
			for(int i = bitsPos; i > 0; i--)
			{
				normal      = onewire->readBit();
				complemento = onewire->readBit();
				onewire->escreve_bit(bits[i]);
			}
		}
	}
	else
	{
		normal      = onewire->readBit();
		complemento = onewire->readBit();
	}
	
	if(bitsPos == 65)
	{
		arr[*arrPos] = bits;
		return;
	}
	else if(normal==0 && complemento==0)
	{
		bits.set(bitsPos, false);
		printf("b(%d)=%d \n",bitsPos,0);
		onewire->escreve_bit(0);
		scanAddresses(bits,bitsPos+1,arr,arrPos,0);
		bits.set(bitsPos, true);
		printf("b(%d)=%d \n",bitsPos,1);
		*arrPos=*arrPos+1;
		scanAddresses(bits,bitsPos+1,arr,arrPos,1);
	}
	else if(normal==0 && complemento==1)
	{
		bits.set(bitsPos, false);
		printf("b(%d)=%d \n",bitsPos,0);
		onewire->escreve_bit(0);
		scanAddresses(bits,bitsPos+1,arr,arrPos,0);
	}
	else if(normal==1 && complemento==0)
	{
		bits.set(bitsPos, true);
		printf("b(%d)=%d \n",bitsPos,0);
		onewire->escreve_bit(1);
		scanAddresses(bits,bitsPos+1,arr,arrPos,0);
	}
	else
	{
		return;
	}
}

void DS18B20::fazScan (void)
{
		printf("*** fazScan***\n");

	char v[8]={0,0,0,0,0,0,0,0};
	uint8_t normal, complemento;
	
	onewire->writeByte(SEARCH_ROM);
	normal      = onewire->readBit();
	complemento = onewire->readBit();
	
	for (int x=0;x<64;x++)
	{
		normal      = onewire->readBit();
		complemento = onewire->readBit();
		if (normal==0 && complemento==0)
		{	
			// bits conflitantes na posicao
			printf("bits conflitantes\n");

			onewire->escreve_bit(1);
			capturaBit(x,v,1);
		}
		if (normal==0 && complemento==1)
		{
			// o bit é 0
			printf("b(%d)=0\n",x);

			capturaBit(x,v,0);
			onewire->escreve_bit(0);
		}
		if (normal==1 && complemento==0)
		{
			// o bit é 1
			printf("b(%d)=1\n",x);

			capturaBit(x,v,1);
			onewire->escreve_bit(1);
		}
		if (normal==1 && complemento==1)
		{
			// nao existem escravos no barramento
			printf("Nao existem escravos no barramento\n");
			printf("Posicao do bit%d\n",x);
			return;
		}
		
	}
	printf("Codigo da Familia: %x\n",v[0]);
    	printf("Numero de Serie  : %x %x %x %x %x %x\n",v[6],v[5],v[4],v[3],v[2],v[1]);
 	printf("CRC=             : %x\n",v[7]);
 	
 	printf("Endereco completo: %x %x %x %x %x %x %x %x\n",v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7]);

	
}
void DS18B20::init (void)
{
	// So pode ser usada se existir apenas um escravo no barramento
	uint8_t serial[6],crc;
		printf("*** init***\n");

	delay_ms(500);

	printf("INIT\n");
	if (onewire->reset()==0) printf("Detectou escravo na linha\n");
	else printf("Nao detectou escravo\n");

	onewire->writeByte(READ_ROM);
	printf("Codigo da Familia: %d\n",onewire->readByte());
	for (uint8_t x=0;x<6;x++) serial[x] = onewire->readByte();

    printf("Numero de Serie  : %d %d %d %d %d %d\n",serial[0],serial[1],serial[2],serial[3],serial[4],serial[5]);

 	crc = onewire->readByte();
 	printf("CRC=             : %d\n",crc);

 	delay_ms(1000);


}
void DS18B20::init2 (void)
{
	// Pode ser chamada se existir 1 ou mais escravos
	
	printf("*** init2***\n");
	delay_ms(500);

	printf("INIT\n");
	if (onewire->reset()==0) printf("Detectou escravo na linha\n");
	else printf("Nao detectou escravo\n");

	
 	delay_ms(1000);


}



// Usa o pino GPIO16 para fazer a comunicacao
DS18B20::DS18B20 (gpio_num_t pino)
{
	DEBUG("DS18B20:Construtor\n");
	onewire = new ONEWIRE(pino);
}

char DS18B20::CRC (char end[])
{
	// calcula o CRC e retorna o resultado
	return 0;
}
float DS18B20::readTargetTemp (char vetor_64bits[])
{
	float temperatura;

	uint8_t a,b,inteira;
	float frac;

	onewire->reset();
	onewire->writeByte(MATCH_ROM);
	for (int x=7;x>=0;x--)
	{
		onewire->writeByte(vetor_64bits[x]);
	}
	onewire->writeByte(INICIA_CONVERSAO_TEMP);
	delay_ms(1000);
	onewire->reset();
	onewire->writeByte(MATCH_ROM);
	for (int x=7;x>=0;x--)
	{
		onewire->writeByte(vetor_64bits[x]);
	}
	onewire->writeByte(READ_TEMP_MEMORY);
	a = onewire->readByte();
    b = onewire->readByte();
    inteira = (b<<4)|(a >> 4);


    	frac=((a & 1)*(0.0625))+ (((a>>1) & 1)*(0.125)) + (((a>>2) & 1)*(0.25)) + (((a>>3) & 1)*(0.5));
     
            temperatura = inteira + frac;
  return temperatura;     


	
}
float DS18B20::readTemp (void)
{
	float temperatura;

	uint8_t a,b,inteira;
	float frac;

	onewire->reset();
	onewire->writeByte(SKIP_ROM);
	onewire->writeByte(INICIA_CONVERSAO_TEMP);
	delay_ms(1000);
	onewire->reset();
	onewire->writeByte(SKIP_ROM);
	onewire->writeByte(READ_TEMP_MEMORY);
	a = onewire->readByte();
    b = onewire->readByte();
    inteira = (b<<4)|(a >> 4);


    	frac=((a & 1)*(0.0625))+ (((a>>1) & 1)*(0.125)) + (((a>>2) & 1)*(0.25)) + (((a>>3) & 1)*(0.5));
     
            temperatura = inteira + frac;
  return temperatura;     


	
}

#endif
