
# Microcontroller version, this is for MSP430G2231 
# (look at the chip to se what version should be used)
ifndef MCU
	MCU=msp430g2231
endif 

CC 	= msp430-gcc
CFLAGS 	= -mmcu=$(MCU) -Werror
LD 	= $(CC)
LDFLAGS = -mmcu=$(MCU)
STRIP 	= msp430-strip

ifdef DEBUG
	CFLAGS += -g
else
	CFLAGS += -Os
endif

ifndef VERBOSE
	QUIET_CC = @echo '   ' CC $@;
	QUIET_LD = @echo '   ' LD $@;
	QUIET_STRIP = @echo '   ' STRIP $@;
endif

PROGRAMS = react.elf

.PHONY : clean distclean

all : $(PROGRAMS)

clean :
	$(RM) *.o

distclean : clean
	$(RM) $(PROGRAMS)

react.elf : main.o sm.o btn.o rand.o



%.elf :
	$(QUIET_LD)$(LD) $(LDFLAGS) -o $@ $^
ifndef DEBUG
	$(QUIET_STRIP)$(STRIP) $@
endif

%.o : %.c
	$(QUIET_CC)$(CC) $(CFLAGS) -c -o $@ $^
