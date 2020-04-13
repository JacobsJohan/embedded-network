CURRENTDIR  =$(shell pwd)

include makefiles/config.mk
include makefiles/utils.mk
include makefiles/buildroot.mk


# Not yet implemented
.PHONY: all
all:
	@echo "Make all is not configured"
