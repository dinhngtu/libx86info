VERSION:=0.0.1

FIND:=/usr/bin/find
INSTALL:=/usr/bin/install

PREFIX:=/usr/local
CFLAGS:=-Wall -Wextra -Iinclude/
ARFLAGS:=rcsU
INSTALLFLAGS:=-vDm 644

TARGETS:=libx86info.a x86info.pc
SOURCES:=$(wildcard *.c) $(wildcard printers/*.c)
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES))
HEADERS:=$(wildcard include/x86info/*.h)

all: $(TARGETS)

libx86info.a: libx86info.a($(OBJECTS))

x86info.pc: libx86info.a
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
	$(INSTALL) $(INSTALLFLAGS) libx86info.a $(PREFIX)/lib
	$(INSTALL) $(INSTALLFLAGS) x86info.pc $(PREFIX)/lib/pkgconfig

clean:
	$(RM) $(RMFLAGS) $(TARGETS) $(OBJECTS)

.PHONY: clean install
