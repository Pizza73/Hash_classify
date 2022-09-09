PROGRAM = shake
CC = gcc
CFLAGS = -Wall -O2
OBJS = fips202 shake


../bin/shake:	../obj/shake.o ../obj/fips202.o
	$(CC) $(CFLAGS) -o ../bin/shake ../obj/shake.o ../obj/fips202.o

../obj/shake.o:	shake.c
	$(CC) $(CFLAGS) -c shake.c -o ../obj/shake.o

../obj/fips202.o:	fips202.c
	$(CC) $(CFLAGS) -c fips202.c -o ../obj/fips202.o

clean:
	rm -f ../obj/shake.o ../obj/fips202.o