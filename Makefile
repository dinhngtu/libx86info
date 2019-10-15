VERSION:=0.0.1

PREFIX:=/usr/local

FIND:=/usr/bin/find
INSTALL:=/usr/bin/install

CFLAGS+=-Wall -Wextra -std=gnu11 -Og -g3 -D_GNU_SOURCE
CPPFLAGS+=-MMD -MP -Iinclude/
ARFLAGS:=rcsU
INSTALLFLAGS:=-vDm 644

TARGETS:=libx86info.a x86info.pc
SOURCES:=$(wildcard *.c) $(wildcard printers/*.c)
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES))
DEPS:=$(patsubst %.c,%.d,$(SOURCES))

all: $(TARGETS)

libx86info.a: libx86info.a($(OBJECTS))

x86info.pc:
	@echo "prefix=$(PREFIX)" > $@
	@echo "includedir=$(PREFIX)/include" >> $@
	@echo "libdir=$(PREFIX)/lib" >> $@
	@echo "" >> $@
	@echo "Name: x86info" >> $@
	@echo "Description: x86 helper library" >> $@
	@echo "Version: $(VERSION)" >> $@
	@echo "Cflags: -I\$${includedir}" >> $@
	@echo "Libs: -L\$${libdir} -lx86info" >> $@

install: libx86info.a x86info.pc
	$(FIND) include/ -type f -exec $(INSTALL) $(INSTALLFLAGS) "{}" "$(PREFIX)/{}" \;
	$(INSTALL) $(INSTALLFLAGS) libx86info.a $(PREFIX)/lib/libx86info.a
	$(INSTALL) $(INSTALLFLAGS) x86info.pc $(PREFIX)/lib/pkgconfig/x86info.pc

clean:
	$(RM) $(RMFLAGS) $(TARGETS) $(OBJECTS) $(DEPS)

.PHONY: clean install

.PRECIOUS: %.o

-include $(DEPS)
