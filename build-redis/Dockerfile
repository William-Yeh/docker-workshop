# a naive Redis image

FROM ubuntu:14.04

# copy to image/container
COPY redis-server_2.8.19.deb redis-server.deb

# install from deb
RUN dpkg -i redis-server.deb

# start Redis server
CMD [ "redis-server" ]
