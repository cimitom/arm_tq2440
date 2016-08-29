#VPATH = source_2:source_1

#test_1 : test.c
#	cd source_1
#	gcc $^ -o $@

#test_2 : test.c
#	cd source_2
#	gcc $^ -o $@

dir_1 := source_1
from := 1
to_2 := 2
to_3 := 3
.PHONY: all clean
all :
	$(MAKE) -C $(dir_1)
	$(MAKE) -C $(subst $(from),$(to_2),$(dir_1))
	$(MAKE) -C $(subst $(from),$(to_3),$(dir_1))

clean :
	-$(MAKE) clean -C source_1
	-$(MAKE) clean -C $(dir_1:1=2)
	-$(MAKE) clean -C $(dir_1:1=3)
