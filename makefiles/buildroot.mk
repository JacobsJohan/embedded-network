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



# Create the dowload and cache directories on the host if they do not exist yet
.PHONY: br-setup
br-setup:
	@mkdir -p $(BRCACHEDIR) $(BRDLDIR) $(BRBUILDDIR)
