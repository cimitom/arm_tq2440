VPATH = include:source

test : test.c no.h
	gcc $^ -o $@

.PHONY : clean
clean :
	rm -f *.o test
