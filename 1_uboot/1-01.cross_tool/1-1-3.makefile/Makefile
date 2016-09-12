VPATH = include:source:apple

all : test_a test_b test_c
.PHONY : all

test_a : test_a.o apple.o
	gcc $^ -o $@

test_a.o : test_a.c a.h
	gcc -c $< -o $@

apple.o : apple.c
	$(MAKE) -C apple

test_b : test_b.c b.h
	gcc $^ -o $@
test_c : test_c.c c.h
	gcc $^ -o $@

.PHONY : cleanall cleanobj
cleanall : cleanobj
	-rm test*
cleanobj :
	-rm *.o
