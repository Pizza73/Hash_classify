#include<stdio.h>


int file(FILE **fp, char *sp){

	fp = fopen(sp, "w");
	fprintf(*fp, "test");
	fclose(*fp);

	return 0;
}


int main(int argc, char *argv[]){
	FILE *fp;

	file(&fp, argv[1]);
	printf("%s", argv[1]);
	return 0;
}
