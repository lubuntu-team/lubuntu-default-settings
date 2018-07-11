#!/usr/bin/make -f

all: install
	make -C src/usr/share/xsessions/po/
	rm -rf src/usr/share/xsessions/po/ src/usr/share/xsessions/*.in

install:
	mkdir -pv $(DESTDIR)
	cp -a src/etc src/usr $(DESTDIR)/.

# vim:ts=4
