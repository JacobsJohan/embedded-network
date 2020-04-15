BUILDDIR = build

#====================== Buildroot ========================#

# Docker image with buildroot tools installed
BRIMG          = embedded-network

# Cache directory for buildroot on the host
BRCACHEDIR    := $(HOME)/.buildroot-ccache

# Download directory for buildroot on the host
BRDLDIR        = dl

BRBUILDDIR     = $(BUILDDIR)/buildroot

# Make default raspberrypi 4 defconfig
BRDEFCONFIG = raspberrypi4_custom_defconfig

#=========================================================#


