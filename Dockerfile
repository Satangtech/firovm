FROM ubuntu:22.04 AS builder
RUN apt update -y
RUN apt install -y build-essential libtool autotools-dev automake pkg-config libssl-dev \
    bsdmainutils python3 git cmake libboost-all-dev libgmp3-dev \
    libevent-dev libboost-dev libboost-system-dev libboost-filesystem-dev libboost-test-dev \
    libsqlite3-dev libminiupnpc-dev libnatpmp-dev libzmq3-dev curl bison byacc

WORKDIR /firovm
COPY . .

RUN /firovm/contrib/install_db4.sh `pwd`

RUN cd depends && make -j$(nproc) && cd .. && ./autogen.sh && \
    ./configure --prefix=`pwd`/depends/x86_64-pc-linux-gnu --disable-tests --disable-bench --without-gui && \
    make clean && make -j$(nproc) && make install

FROM ubuntu:22.04

RUN apt-get update && useradd -ms /bin/bash firovm

WORKDIR /firovm
RUN chown -R firovm:firovm /firovm

COPY --from=builder /firovm/src/firovmd /usr/local/bin
COPY --from=builder /firovm/src/firovm-cli /usr/local/bin
COPY --from=builder /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0 \
    /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0 \
    /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.74.0 \
    /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.74.0 \
    /firovm/db4/lib/libdb_cxx-4.8.a \
    /usr/lib/

USER firovm

EXPOSE 1234

ENTRYPOINT [ "firovmd", "-datadir=/firovm" ]
