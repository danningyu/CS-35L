CC=gcc

sfrob: sfrob.c
	$(CC) -o sfrob -fsanitize=address -fsanitize=undefined \
	 -static-libubsan -static-libasan -g -W -Wall -pedantic sfrob.c

clean:
	rm -f sfrob

valgrind:
	$(CC) -o sfrob -g -W -Wall -pedantic sfrob.c
