# Start with an official Debian or Ubuntu image
FROM archlinux:latest AS base

# Install necessary packages
RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
        curl \
        base-devel \
        cmake \
        git \
        xorg-server \
        mesa \
        libx11 \
        libxcursor \
        libxrandr \
        libxinerama \
        libxi \
        alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama \
        criterion raylib;

# Set working directory
WORKDIR /root/app

# Copy the application code
COPY ./src ./src
COPY Makefile .
RUN mkdir bin;

# Dev image
FROM base AS dev
RUN make;
RUN ./bin/test;
CMD ["./bin/app"]
