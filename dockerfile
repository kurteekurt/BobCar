# use the official Debian 12 (Bullseye) as the base image
FROM --platform=linux/arm64 debian:12

# set non-interactive frontend for apt
ENV DEBIAN_FRONTEND=noninteractive

# add ARM architecture for cross-compilation (optional if working with cross-compiling)
RUN dpkg --add-architecture armhf

# Install base tools and essential system packages
RUN apt-get update && apt-get install -y \
    git \
    wget \
    make \
    cmake \
    meson \
    ninja-build \
    pkg-config \
    unzip \
    clang-tidy \
    gcc-arm-linux-gnueabihf \
    g++-arm-linux-gnueabihf \
    && rm -rf /var/lib/apt/lists/*

# Install libopencv dev 
RUN apt-get update && apt-get install -y \
    libopencv-dev:armhf \
    && rm -rf /var/lib/apt/lists/*

# Copy the downloaded WiringPi .deb file into the container
RUN wget -O /tmp/wiringpi_3.10_armhf.deb https://github.com/WiringPi/WiringPi/releases/download/3.10/wiringpi_3.10_armhf.deb

# Install the WiringPi package
RUN apt-get update && \
    dpkg -i /tmp/wiringpi_3.10_armhf.deb || \
    apt-get -f install -y && \
    rm -rf /var/lib/apt/lists/* /tmp/wiringpi_3.10_armhf.deb

# set work directory
WORKDIR /workspace

# default command
CMD ["/bin/bash"]