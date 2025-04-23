#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

unsigned long long _rand_next;

void newlib_srand(unsigned int seed)
{
	_rand_next = seed;
}

int newlib_rand()
{
	_rand_next =
		 _rand_next * 6364136223846793005LL + 1;
	return (int)((_rand_next >> 32) & RAND_MAX);
}

int FUN_420007c8(int param_1,int param_2);

uint32_t FUN_420007e6(uint32_t param_1)
{
	uint32_t uVar1;

	if (param_1 != 0) {
		if ((int)param_1 < 0) {
			uVar1 = FUN_420007c8(0,-param_1);
			return uVar1;
		}
		uVar1 = newlib_rand();
		param_1 = uVar1 % param_1;
	}
	return param_1;
}

int FUN_420007c8(int a,int b)

{
	int iVar1;

	if (a < b) {
		iVar1 = FUN_420007e6(b - a);
		a = a + iVar1;
	}
	return a;
}

uint8_t enc_flag[64] = {
	0xa3,0xaa,0x79,0xeb,0x00,0x9b,0xef,0xff,0x13,0x86,0xe1,0x4d,0x81,0x6b,0x0d,0x3d,0x10,0x2d,0xec,0x86,0x1b,0x00,0xb9,0x68,0xfb,0x7d,0xe0,0xc1,0x1e,0xbd,0x30,0x53,0x8c,0xf1,0xa7,0xf9,0x7b,0x1a,0xf3,0xed,0xa7,0x1c,0x95,0x61,0x8b,0x73,0x4a,0x8e,0x28,0xa4,0xeb,0x0e,0x55,0x99,0xf5,0xbe,0xfd,0xfc,0x31,0x48,0x67,0xc3,0xde,0xcc
};

uint8_t local_b4[64];

int main() {
	for(int i = 0; i < 4096; i++) {
		newlib_srand(i);

		for(int j = 0; j < 30000; j++) {
			uint8_t *pbVar2 = local_b4;
			uint8_t *pbVar7 = local_b4 + 64;

			do {
				uint16_t uVar3 = FUN_420007c8(0,0x10001);
				*pbVar2 = (uint8_t)((uint16_t)uVar3 >> 8);
				pbVar2[1] = (uint8_t)uVar3;
				pbVar2 = pbVar2 + 2;
			} while (pbVar2 != pbVar7);

			for(int c = 0; c < 64; c++) {
				local_b4[c] ^= enc_flag[c];
			}

			if(!strncmp(local_b4, "ASIS", 4)) {
				printf("seed %i, iteration %i, flag: %s\n", i, j, local_b4);
				return 0;
			}
		}
	}
}

// ASIS{ESP32s_R4ndomn3sS_weAkNes5_iZ_S!gnif1can7_Av0iD_ItS_pleaS3}
