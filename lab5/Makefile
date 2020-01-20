CC=gcc

all: tr2b tr2u sfrobu sfrobufast sfrobfast

tr2b: tr2b.c
	gcc -o tr2b -g -W -Wall -pedantic -std=c11 tr2b.c

tr2u: tr2u.c
	gcc -o tr2u -g -W -Wall -pedantic -std=c11 tr2u.c

sfrobu: sfrobu.c
	gcc -o sfrobu -fsanitize=address -fsanitize=undefined \
	 -static-libubsan -static-libasan -std=c11 -g -W -Wall -pedantic sfrobu.c

sfrobufast: sfrobu.c
	gcc -o sfrobufast -std=c11 -W -Wall -pedantic sfrobu.c

sfrobfast: sfrob.c
	gcc -o sfrobfast -std=c11 -W -Wall -pedantic sfrob.c

clean:
	rm -f tr2b tr2u sfrobu sfrobufast
