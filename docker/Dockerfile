FROM ubuntu:18.04

# Update and install dependencies for buildroot
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    git sed make binutils build-essential gcc g++ bash patch gzip bzip2 perl \
    tar cpio unzip rsync file bc wget libncurses5-dev libncursesw5-dev \
    gcc-multilib g++-multilib language-pack-en expect python vim

# User management
RUN adduser --uid 1000 johan && \
        echo "johan ALL=(ALL) NOPASSWD: ALL" | tee -a /etc/sudoers

# Set the locale
RUN sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
    locale-gen
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# Download and install buildroot
RUN git clone git://git.buildroot.net/buildroot --branch 2020.02 --single-branch && cd buildroot && git pull && \
    chown -R johan:johan /buildroot

# Patch the config.txt file in package/rpi-firmware
RUN echo "dtparam=i2c1=on" >> /buildroot/package/rpi-firmware/config.txt

# Setup build directory
RUN mkdir -p /v && chown johan:johan /v

# Include scripts
COPY scripts/setup-build.sh /usr/local/bin/

# Setup environment variables
USER johan
ENV BUILDROOT_DIR /buildroot/
