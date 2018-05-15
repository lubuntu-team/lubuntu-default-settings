#!/usr/bin/make -f

all: install

install:
	mkdir -pv $(DESTDIR)
	cp -a src/etc src/usr $(DESTDIR)/.

	# remove some remaining files
	find $(DESTDIR) -type f -iname "*.in" | xargs rm -f

# vim:ts=4
