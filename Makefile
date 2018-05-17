#!/usr/bin/make -f

all: install

install:
	mkdir -pv $(DESTDIR)
	cp -a src/etc src/usr $(DESTDIR)/.

# vim:ts=4
