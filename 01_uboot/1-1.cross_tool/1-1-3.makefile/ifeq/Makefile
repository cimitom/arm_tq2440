no1 = good
no2 = good

comma = ,
empty =
space = $(empty)$(empty)

foo = a b c

subchange = $(subst $(space),$(comma),$(foo))


.PHONY:tstifeq tstsubst

tstifeq:
ifeq ($(no1),$(no2))
	@echo no.1=no.2
else
	@echo no.1 != no.2
endif

tstsubst:
	@echo $(subchange)
