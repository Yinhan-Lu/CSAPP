Device: MacBook Air (M2)

0.

Move to ``DATALAB-HANDOUT`` folder.

1.

Install Docker from https://www.docker.com/products/docker-desktop/. After installing, check if the docker is working by run``docker --version`` in the terminal.

2.

create and edit a Docker file by

```
nano Dockerfile
```

and Paste the following into the `Dockerfile`:

```
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

```

Save it by ``^O`` and exit by``^X``.

3.

build the docker by

```
docker build --platform linux/amd64 -t csapp-datalab .
```

4.

you start the docker by

```
docker run --platform linux/amd64 -it -v $(pwd):/datalab csapp-datalab
```

everytime before coding, testing using ``make btest`` and ``./btest``.

5.

when you wanna quit the docker, simply enter

```
exit
```

in the terminal. If you wanna enter the docker again, enter

```
docker run --platform linux/amd64 -it -v $(pwd):/datalab csapp-datalab
```

in the terminal is all you need.