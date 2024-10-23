#!/usr/bin/make -f

all:
	make -C src/usr/share/xsessions/po/
	rm -rf src/usr/share/xsessions/po/ src/usr/share/xsessions/*.in
