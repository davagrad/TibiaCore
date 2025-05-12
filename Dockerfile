# Stage 1: Download all dependencies
FROM ubuntu:22.04 AS dependencies

RUN apt-get update && apt-get install -y --no-install-recommends \
		build-essential libluajit-5.1-dev \
		cmake git curl zip tar gdb \
		libmariadb-dev-compat libboost-date-time-dev \
		libboost-filesystem-dev libboost-system-dev \
        libboost-iostreams-dev libpugixml-dev \
		libgmp3-dev libcrypto++-dev \
		libfmt-dev libjsoncpp-dev \
        && apt-get clean \
        && rm -rf /var/lib/apt/lists/*

# Stage 2: Build
FROM dependencies AS build

WORKDIR /srv/build

RUN chmod -R 644 /srv/build

COPY compiler/src /srv/src
COPY compiler/cmake /srv/cmake
COPY compiler/CMakeLists.txt /srv

ENV CMAKE_MAKE_PROGRAM=make
ENV CMAKE_C_COMPILER=gcc
ENV CMAKE_CXX_COMPILER=g++

RUN cmake -D CMAKE_BUILD_TYPE=RelWithDebInfo .. \
        && make

# Stage 3: execute
FROM ubuntu:22.04 AS final

ENV TZ=America/Campo_Grande \
    DEBIAN_FRONTEND=noninteractive

VOLUME ["/tibiacore-path"]

COPY --from=build /srv/build/tfs /tibiacore/TibiaCore
COPY *.sql key.pem antirollback_config restart.sh /tibiacore/
COPY data /tibiacore/data
COPY logs /tibiacore/logs
COPY config.lua /tibiacore/config.lua
COPY 772.zip /var/www/html.zip

RUN apt-get update && apt-get install -y sudo mariadb-client mariadb-server gdb \
	libluajit-5.1-dev libluajit-5.1-common wget nano zip apache2 screen htop curl \
	libboost-filesystem1.74.0 \
	libpugixml1v5 \
	php php-zip php-xml php-json php-mbstring php-bcmath php-gd php-mysql \
	&& apt-get clean \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /var/www

RUN unzip html.zip
RUN cd html && chown -R www-data.www-data /var/www/* \
	&& chmod 755 -R .

#RUN chmod 755 -R system/ 
#RUN chmod 755 -R images/
#RUN chmod 755 -R plugins/ 
#RUN chmod 755 -R tools/

WORKDIR /tibiacore 

COPY dbinstall.sh /tibiacore/dbinstall.sh
RUN chmod +x -R restart.sh dbinstall.sh

#ENTRYPOINT ["/tibiacore/dbinstall.sh"]
