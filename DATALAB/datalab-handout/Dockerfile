FROM ubuntu:20.04

RUN dpkg --add-architecture i386 && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    gcc-multilib \
    make \
    vim \
    git \
    wget \
    curl \
    build-essential \
    libc6:i386 \
    libncurses5:i386 \
    libstdc++6:i386 \
    gdb

WORKDIR /datalab

