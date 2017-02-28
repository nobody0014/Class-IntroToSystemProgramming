CC = gcc
CFLAGS = -Wall -W -pedantic -g -std=c99

all: bit_practice least_bit_check most_bit_check

bit_practice: bit_practice.c
	$(CC) $(CFLAGS) -o $@ $<

least_bit_check: least_bit_check.c
	$(CC) $(CFLAGS) -o $@ $<

most_bit_check: most_bit_check.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -r bit_practice least_bit_check
