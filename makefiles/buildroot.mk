# Buildroot makefile

# Build docker image
.PHONY: docker-build
docker-build:
	docker build -t $(BRIMG) docker/


# Standard buildroot configuration
.PHONY: br-menuconfig
br-menuconfig: br-setup
	$(info Configuring buildroot...)
	$(BRDOCK) 'source setup-build.sh -e $$PWD/buildroot -d /v/$(BRBUILDDIR) $(BRDEFCONFIG) && \
		make menuconfig && make savedefconfig > /dev/null'


# Build the buildroot image, different defconfigs can be configured in
# the config.mk file
.PHONY: br-build
br-build: br-setup
	$(info Building with buildroot...)
	$(BRDOCK) 'source setup-build.sh -e $$PWD/buildroot -d /v/$(BRBUILDDIR) $(BRDEFCONFIG) && $$BRMAKE'


# Clean the entire buildroot tree (use with care)
.PHONY: br-clean
br-clean:
	$(info Cleaning buildroot directory...)
	$(BRDOCK) 'source setup-build.sh -e $$PWD/buildroot -d /v/$(BRBUILDDIR) $(BRDEFCONFIG) && \
		make clean > /dev/null'


# Configure the linux kernel for buildroot
.PHONY: br-linuxconfig
br-linuxconfig: br-setup
	$(info Configuring buildroot linux kernel...)
	$(BRDOCK) 'source setup-build.sh -e $$PWD/buildroot -d /v/$(BRBUILDDIR) $(BRDEFCONFIG) && \
		make linux-menuconfig && make linux-update-defconfig'


# Reconfigure the linux kernel after changes were made
.PHONY: br-reconfigure
br-reconfigure: br-setup
	$(info Reconfiguring buildroot linux kernel...)
	$(BRDOCK) 'source setup-build.sh -e $$PWD/buildroot -d /v/$(BRBUILDDIR) $(BRDEFCONFIG) && \
		make linux-reconfigure'


# Rebuild a specific package
.PHONY: br-package
br-package: br-setup
	$(info Rebuilding a specific package...)
	$(BRDOCK) 'source setup-build.sh -e $$PWD/buildroot -d /v/$(BRBUILDDIR) $(BRDEFCONFIG) && \
		make rpi-firmware-rebuild'


# Create the dowload and cache directories on the host if they do not exist yet
.PHONY: br-setup
br-setup:
	@mkdir -p $(BRCACHEDIR) $(BRDLDIR) $(BRBUILDDIR)


# dd to sdcard
.PHONY: br-sdcard
br-sdcard:
	dd if=build/buildroot/images/sdcard.img of=/dev/mmcblk0 bs=4M
