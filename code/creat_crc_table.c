#include <stdio.h>
#include <stdint.h>

#define CRCPOLYLSB 0x31 //LSB x8+x5+x4+1
#define CRCPOLYMSB 0x8c //MSB x8+x5+x4+1
/*
 * \brief  calculate CRC-8 LSB
 * \param  -value need calc value
 * \retval crc
 * \v0.02 2021/01/08
 */
uint8_t calc_crc8_lsb(uint8_t value)
{
	uint8_t i, crc;

	crc = 0;           // default value
	crc ^= value;

	for (i=8; i>0; --i) {
		if (crc & 0x01)
			crc = (crc >> 1) ^ CRCPOLYLSB;
		else
			crc = (crc >> 1);
	}
	return crc;
}

/*
 * \brief calculate CRC-8 MSB
 * \param value need calc value
 * \retval crc
 * \v0.02 2021/01/08
 */
uint8_t calc_crc8_msb(uint8_t value)
{
	uint8_t i, crc;
	crc=0x00;           // default value
	crc ^=value;

	for (i=8; i>0; --i) {
		if (crc & 0x80)
			crc = (crc << 1) ^ CRCPOLYMSB;
		else
			crc = (crc << 1);
	}
	return crc;
}

/*
 * \brief  creat table
 * \v0.02 2021/01/08
 */
void creat_tab(void)
{
	uint32_t i;
	uint8_t j;
	FILE* file1;
	FILE* file2;
	file1 = fopen("a.txt","w");
	file2 = fopen("b.txt","w");

	for (i=0; i<=0xFF; i++) {
		if (0 == (i%16))
			fprintf(file1,"\n");
		j = i&0xFF;
		fprintf(file1,"0x%.2x, ", calc_crc8_lsb(j));
	}
	for (i=0; i<=0xFF; i++) {
		if (0 == (i%16))
			fprintf(file2,"\n");
		j = i&0xFF;
		fprintf(file2,"0x%.2x, ", calc_crc8_msb(j));
	}
}

void main(void)
{
	creat_tab();
}
