#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CFLAGS += -O2 -g -Wall #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS +=

game: game.o test.o sound_engine.o gamepad_engine.o screen_engine.o

all: game

clean:
	-rm -f game *.o

install:


.PHONY: all install clean

# end of development makefile
