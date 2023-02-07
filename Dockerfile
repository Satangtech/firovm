FROM ubuntu:18.04 AS builder
RUN apt update
RUN apt-get install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils git cmake libboost-all-dev libgmp3-dev
RUN apt-get install -y software-properties-common
RUN add-apt-repository ppa:bitcoin/bitcoin
RUN apt-get update -y
RUN apt-get install -y libdb4.8-dev libdb4.8++-dev
RUN apt-get install -y curl bison byacc

WORKDIR /firovm
COPY . .

RUN cd depends && make -j$(nproc) && cd .. && ./autogen.sh && \
    ./configure --prefix=`pwd`/depends/x86_64-pc-linux-gnu --disable-tests --disable-bench --without-gui && \
    make clean && make -j$(nproc) && make install

FROM ubuntu:18.04

RUN apt-get update && useradd -ms /bin/bash firovm
USER firovm
WORKDIR /firovm

RUN mkdir -p /firovm/.firovm
RUN chown firovm:firovm /firovm/.firovm

COPY --from=builder /firovm/src/firovmd /usr/local/bin
COPY --from=builder /firovm/src/firovm-cli /usr/local/bin
COPY --from=builder /usr/lib/x86_64-linux-gnu/libboost_system.so.1.65.1 \
    /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.65.1 \
    /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.65.1 \
    /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.65.1 \
    /usr/lib/libdb_cxx-4.8.so \
    /usr/lib/

EXPOSE 1234

ENTRYPOINT [ "firovmd" ]
