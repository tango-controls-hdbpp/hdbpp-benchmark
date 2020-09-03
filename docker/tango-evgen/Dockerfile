FROM nexus.engageska-portugal.pt/ska-docker/tango-libtango:latest

USER root

RUN apt-get update && \
    apt-get install -y \
        git \
        cmake \
        make \
        g++ \
        pkg-config
	
RUN git clone --depth 1 https://github.com/gscalamera/hdbpp-benchmark.git

RUN cd hdbpp-benchmark/tango/evgen \
 && mkdir build \
 && cd build \
 && cmake ..  \
 && make -j4 \
 && make install


