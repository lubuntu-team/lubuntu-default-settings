#!/usr/bin/make -f

all: build install

build:
	make -C src/usr/share/xsessions/po/
	rm -rf src/usr/share/xsessions/po/ src/usr/share/xsessions/*.in
	cd snap-installation-monitor && cmake -DCMAKE_BUILD_TYPE=Release . && make

install:
	mkdir -pv $(DESTDIR)/lubuntu-snap-installation-monitor/usr/libexec
	mkdir -pv $(DESTDIR)/lubuntu-snap-installation-monitor/etc/xdg/autostart
	mkdir -pv $(DESTDIR)/lubuntu-default-settings/
	cp -a src/etc src/usr $(DESTDIR)/lubuntu-default-settings/.
	cp -a snap-installation-monitor/snap-installation-monitor $(DESTDIR)/lubuntu-snap-installation-monitor/usr/libexec/.
	cp -a snap-installation-monitor/snap-installation-monitor.desktop $(DESTDIR)/lubuntu-snap-installation-monitor/etc/xdg/autostart/.
