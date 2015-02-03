# a naive Redis image

FROM centos:5.11

# copy to image/container
COPY redis-2.8.19-1.el5.remi.x86_64.rpm redis-server.rpm
COPY jemalloc-3.6.0-2.el5.x86_64.rpm    jemalloc.rpm

# install from RPM
RUN rpm -i jemalloc.rpm redis-server.rpm

# start Redis server
CMD [ "redis-server" ]
