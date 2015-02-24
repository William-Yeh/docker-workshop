# a naive Redis image

FROM ubuntu:14.04

# copy to image/container
COPY redis-server_2.8.19.deb redis-server.deb

# install from deb
RUN dpkg -i redis-server.deb


# expose Redis port (used by "redis-server")
EXPOSE 6379

# install wrapper scripts
COPY client    /usr/local/bin/
COPY benchmark /usr/local/bin/


# start Redis server
CMD [ "redis-server" ]
