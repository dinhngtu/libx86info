CFLAGS:=-Wall -Wextra -Iinclude/
ARFLAGS:=rcsU

TARGETS:=libx86info.a
SOURCES:=$(wildcard *.c) $(wildcard printers/*.c)
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES))

all: $(TARGETS)

libx86info.a: libx86info.a($(OBJECTS))

.PHONY: clean

clean:
	$(RM) $(RMFLAGS) $(TARGETS) $(OBJECTS)