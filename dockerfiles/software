FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    \
    gcc \
    binutils \
    libnewlib-dev \
    \
    make \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /build
CMD ["/bin/bash"]