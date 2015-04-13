#!/bin/bash
#
# scirpt for compiling go source via Dockerized Go compiler.
#
# If you'd like to compile via native Go compiler:
#
#   $ go install github.com/docopt/docopt-go
#   $ go build 
#

set -e
set -x


IMAGE_NAME=app_build_temp
docker build  -t $IMAGE_NAME  -f Dockerfile-compile  .
docker run --rm -v "$(pwd)/dist:/dist" $IMAGE_NAME

docker rmi -f $IMAGE_NAME