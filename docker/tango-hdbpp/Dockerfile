FROM nexus.engageska-portugal.pt/ska-docker/tango-libtango:latest

USER root

RUN apt-get update && \
    apt-get install -y \
        git \
        cmake \
        make \
        g++ \
        pkg-config \
        libpq-dev \
        libmariadb-dev-compat libmariadb-dev

RUN git clone --depth 1 https://github.com/tango-controls-hdbpp/libhdbpp.git

RUN cd libhdbpp \
 && mkdir build \
 && cd build \
 && cmake ..  \
 && make -j4 \
 && make install

RUN git clone -b project-build2 --depth 1 --recurse-submodules https://github.com/tango-controls-hdbpp/libhdbpp-timescale.git


RUN cd libhdbpp-timescale \
 && mkdir build \
 && cd build \
 && cmake -DPostgreSQL_TYPE_INCLUDE_DIR=/usr/include/postgresql ..  \
 && make -j4 \
 && make install

RUN git clone -b libhdbpp2 --depth 1 https://github.com/tango-controls-hdbpp/libhdbpp-mysql.git

RUN cd libhdbpp-mysql \
 && mkdir build \
 && cd build \
 && cmake ..  \
 && make -j4 \
 && make install

RUN git clone -b integrated-build --depth 1 https://github.com/tango-controls-hdbpp/hdbpp-es.git

RUN cd hdbpp-es \
 && mkdir build \
 && cd build \
 && cmake ..  \
 && make -j4 \
 && make install

RUN git clone --depth 1 https://github.com/tango-controls-hdbpp/hdbpp-cm.git

RUN cd hdbpp-cm \
 && mkdir build \
 && cd build \
 && cmake ..  \
 && make -j4 \
 && make install


RUN apt-get update && \
#    apt-get install -y \
#    build-essential && \
    apt-get clean


RUN ldconfig

#NOTE: rename without + because not supported by json2tango
RUN mv /usr/local/bin/hdb++cm-srv /usr/local/bin/hdbppcm-srv
RUN mv /usr/local/bin/hdb++es-srv /usr/local/bin/hdbppes-srv
