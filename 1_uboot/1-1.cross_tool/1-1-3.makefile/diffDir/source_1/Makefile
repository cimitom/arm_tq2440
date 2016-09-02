src = test.c

tag : test.c
	gcc -c $(src) -o $(src:.c=.o)
	gcc $(src:.c=.o) -o test
.PHONY: clean
clean :
	rm test *.o
