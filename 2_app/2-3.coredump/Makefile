all : test_a test_b


%.o : %.c
	gcc -g -c $^

.PHONY: all clean

test_a : test_a.o
	gcc -o $@ $^
test_b : test_b.o
	gcc -o $@ $^

clean :
	-rm test_a test_b *.o core
