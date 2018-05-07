CFLAGS = -Wall -fpic -coverage -lm

runtest: testme.c
		gcc -o testme testme.c -g $(CFLAGS) 
		./testme

clean:
		-rm -f *.gcda *.gcno testme