#!/usr/bin/make -f

all: install

install:
	make -C src/usr/share/xsessions/po/
	mkdir -pv $(DESTDIR)
	cp -a src/etc src/usr $(DESTDIR)/.

# vim:ts=4
