FROM debian:bullseye as builder

RUN apt-get update && apt-get install -y automake bsdmainutils g++ libtool make pkg-config patch bzip2 xz-utils curl

WORKDIR /tmp/firovm
COPY . /tmp/firovm

# build depends
RUN cd depends && make clean && make -j$(nproc) NO_QT=1 HOST=$(uname -m)-linux-gnu

# build firovm
RUN ./autogen.sh && \
    ./configure --without-gui --prefix=/tmp/firovm/depends/$(uname -m)-linux-gnu --disable-tests && \
    make -j$(nproc) && \
    make install

RUN mkdir /tmp/ldd
RUN for library in $(ldd "./depends/$(uname -m)-linux-gnu/bin/firovmd" | cut -d '>' -f 2 | awk '{print $1}'); do [ -f "${library}" ] && cp --verbose --parents "${library}" "/tmp/ldd"; done
RUN for library in $(ldd "./depends/$(uname -m)-linux-gnu/bin/firovm-cli" | cut -d '>' -f 2 | awk '{print $1}'); do [ -f "${library}" ] && cp --verbose --parents "${library}" "/tmp/ldd"; done

RUN cp ./depends/$(uname -m)-linux-gnu/bin/* /usr/bin/

FROM debian:bullseye-slim

COPY --from=builder /usr/bin/firovmd /usr/bin/firovmd
COPY --from=builder /usr/bin/firovm-cli /usr/bin/firovm-cli
COPY --from=builder /tmp/ldd /tmp/ldd

RUN cp -vnrT /tmp/ldd / && \
    rm -rf /tmp/ldd && \
    ldd /usr/bin/firovmd && \
    ldd /usr/bin/firovm-cli

RUN useradd firovm && \
    mkdir -p /firovm && \
    chown -R firovm:firovm /firovm

USER firovm
WORKDIR /firovm

# Testnet ports
EXPOSE 13888
EXPOSE 13889

ENTRYPOINT ["/usr/bin/firovmd", "-datadir=/firovm"]