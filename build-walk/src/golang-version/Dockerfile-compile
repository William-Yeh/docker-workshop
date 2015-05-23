# building linux-amd64 native binary via Dockerized Go compiler
#
# @see https://registry.hub.docker.com/_/golang/
#

# pull base image
FROM golang:1.4.2
MAINTAINER William Yeh <william.pjyeh@gmail.com>

ENV EXE_NAME  walk_linux-amd64
ENV GOPATH    /opt
WORKDIR       /opt


# fetch imported Go lib...
RUN  go get  github.com/kr/fs  text/tabwriter
COPY walk.go  /opt/

# compile...
RUN  go build -o $EXE_NAME



# copy executable
RUN    mkdir -p /dist
VOLUME [ "/dist" ]
CMD    cp  *_linux-amd64  /dist
