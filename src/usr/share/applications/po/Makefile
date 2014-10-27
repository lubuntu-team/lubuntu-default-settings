#!/usr/bin/make -f

POTFILES := $(shell cat POTFILES.in)

all: generate-po-files

generate-pot: POTFILES.in
	intltool-update --pot --gettext-package=lubuntu-default-settings-files

generate-po-files:
	for i in $(POTFILES); do \
		f=$$(echo $$i | sed 's/\.in//'); \
		intltool-merge -d . ../$$i ../$$f; \
	done

update-po:
	for i in *.po; do \
		code=$$(echo $$i | sed 's/.po//'); \
		intltool-update --gettext-package=lubuntu-default-settings-files --dist $$code; \
	done

# vim:ts=4
