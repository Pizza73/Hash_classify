PROGRAM = shake
CC = gcc
CFLAGS = -O2
OBJS = fips202 shake


shake:	shake.o fips202.o
	gcc -Wall -O2 -o shake shake.o fips202.o

shake.o:	shake.c
	gcc -c -Wall shake.c

fips202.o:	fips202.c
	gcc -c fips202.c

clean:
	rm -f shake.o fips202.o
