#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include"fips202.h"
#include"shake.h"

#define VERBOSE
// #define TEST

//Chenge the output
#define BIN
// #define HEX

//Binary Output Macro
#define BCD(c) (__bits__[c])
static const unsigned int __bits__[] = {
       0,        1,       10,       11,      100,      101,     110,       111,
    1000,     1001,     1010,     1011,     1100,     1101,    1110,      1111,
   10000,    10001,    10010,    10011,    10100,    10101,    10110,    10111,
   11000,    11001,    11010,    11011,    11100,    11101,    11110,    11111,
  100000,   100001,   100010,   100011,   100100,   100101,   100110,   100111,
  101000,   101001,   101010,   101011,   101100,   101101,   101110,   101111,
  110000,   110001,   110010,   110011,   110100,   110101,   110110,   110111,
  111000,   111001,   111010,   111011,   111100,   111101,   111110,   111111,
 1000000,  1000001,  1000010,  1000011,  1000100,  1000101,  1000110,  1000111,
 1001000,  1001001,  1001010,  1001011,  1001100,  1001101,  1001110,  1001111,
 1010000,  1010001,  1010010,  1010011,  1010100,  1010101,  1010110,  1010111,
 1011000,  1011001,  1011010,  1011011,  1011100,  1011101,  1011110,  1011111,
 1100000,  1100001,  1100010,  1100011,  1100100,  1100101,  1100110,  1100111,
 1101000,  1101001,  1101010,  1101011,  1101100,  1101101,  1101110,  1101111,
 1110000,  1110001,  1110010,  1110011,  1110100,  1110101,  1110110,  1110111,
 1111000,  1111001,  1111010,  1111011,  1111100,  1111101,  1111110,  1111111,
10000000, 10000001, 10000010, 10000011, 10000100, 10000101, 10000110, 10000111,
10001000, 10001001, 10001010, 10001011, 10001100, 10001101, 10001110, 10001111,
10010000, 10010001, 10010010, 10010011, 10010100, 10010101, 10010110, 10010111,
10011000, 10011001, 10011010, 10011011, 10011100, 10011101, 10011110, 10011111,
10100000, 10100001, 10100010, 10100011, 10100100, 10100101, 10100110, 10100111,
10101000, 10101001, 10101010, 10101011, 10101100, 10101101, 10101110, 10101111,
10110000, 10110001, 10110010, 10110011, 10110100, 10110101, 10110110, 10110111,
10111000, 10111001, 10111010, 10111011, 10111100, 10111101, 10111110, 10111111,
11000000, 11000001, 11000010, 11000011, 11000100, 11000101, 11000110, 11000111,
11001000, 11001001, 11001010, 11001011, 11001100, 11001101, 11001110, 11001111,
11010000, 11010001, 11010010, 11010011, 11010100, 11010101, 11010110, 11010111,
11011000, 11011001, 11011010, 11011011, 11011100, 11011101, 11011110, 11011111,
11100000, 11100001, 11100010, 11100011, 11100100, 11100101, 11100110, 11100111,
11101000, 11101001, 11101010, 11101011, 11101100, 11101101, 11101110, 11101111,
11110000, 11110001, 11110010, 11110011, 11110100, 11110101, 11110110, 11110111,
11111000, 11111001, 11111010, 11111011, 11111100, 11111101, 11111110, 11111111,
};

// write a binary_file 
void binary_write(short hex, FILE *fp, char *sp){
	
	printf("%08d\n", BCD(hex));
	fprintf(fp, "%08d", BCD(hex));
	fclose(fp);
	return;
}

// Generate Hash value
/*
Generate Hash value
	- SHAKE outputs 8bits per array element.
	- Output length depends on array length.

Input:
	a: length of hash value
	fp: output file pointer
	sp: file name

Output:
	Hash value writen in file

*/
int hash_generate(int a, FILE *fp, char *sp){
	shake256incctx status;
	uint8_t input[2] = {0};
	// input[0] = 255;
	// input[1] = 255; 
	// input[3] = 255;
	printf("input[2]=%d\n", input[1]);
	size_t inlen = sizeof(input);
	printf("Input length : %ld\n", inlen);
	uint8_t output[32] = {0};
	size_t outlen = sizeof(output);
	int output_element = sizeof(output) / sizeof(output[0]);

	long iter_num = a * 1000000000 / (8 * output_element);
	// long iter_num = a * 100000 / (8 * output_element);
	iter_num = 2;


	#ifdef VERBOSE
		printf("Output length : %dGbit\n", a);
		printf("Output array element : %d\n", output_element);
	#endif

	fp = fopen(sp, "w");

	//SHAKE256 hash generation
	shake256_inc_init(&status);
	shake256_inc_absorb(&status, input, inlen);
	shake256_inc_finalize(&status);

	#ifdef TEST 
		shake256_inc_squeeze(output, outlen, &status);
		printf("output[0]:%d\n", output[0]);
		for(int i = 0; i < output_element; i++){
			#ifdef VERBOSE
				printf("%02x", output[i]);
			#endif
			fprintf(fp, "%02x", output[i]);
		}
		printf("\nDone\n");
	#endif

	#ifndef TEST
	while(iter_num > 0){
		shake256_inc_squeeze(output, outlen, &status);
		for(int i = 0; i < output_element; i++){
			#ifdef BIN
				#ifdef VERBOSE
					printf("%08d", BCD(output[i]));
				#endif
				fprintf(fp, "%08d", BCD(output[i]));
			#endif

			#ifdef HEX
				#ifdef VERBOSE
					printf("%02x", output[i]);
				#endif
				fprintf(fp, "%02x", output[i]);
			#endif
		}	
		iter_num--;
	}
	printf("\nDone\n");
	#endif 

	fclose(fp);
	return 0;
}


int main(int argc, char *argv[]){
 	FILE *fp = NULL;
	int input = atoi(argv[1]);

	#ifdef VERBOSE
	printf("input : %d\n", input);
	printf("output file name: %s\n", argv[2]);
	#endif

	hash_generate(input, fp, argv[2]);

	/*
	unsigned char input = '1';
	unsigned char output;
	size_t inlen = sizeof(input);
	size_t outlen = sizeof(output);
	
	shake256(&output, outlen, &input, inlen);

	printf("%d\n", output);
	*/

	return 0;
}
