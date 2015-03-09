#!/bin/bash
#
# provision script; install Docker Registry.
#
# [NOTE] run by Vagrant; never run on host OS. 
#
# @see https://github.com/docker/docker-registry
# 


export DEBIAN_FRONTEND=noninteractive
export LC_ALL=en_US.UTF-8
export LANG=en_US.UTF-8
export LANGUAGE=en_US.UTF-8

readonly REGISTRY_CONFIG_DIR=/opt/docker-registry
readonly REGISTRY_CONFIG_NAME=docker-registry-config.yml
readonly REGISTRY_CONFIG_FULLPATH=$REGISTRY_CONFIG_DIR/$REGISTRY_CONFIG_NAME
readonly REGISTRY_DBPATH=/opt/docker-registry-db



#---------------------------------------#
# prepare directory
#

mkdir $REGISTRY_CONFIG_DIR
mkdir $REGISTRY_DBPATH



#---------------------------------------#
# pull docker-registry image
#

docker pull registry:latest



#---------------------------------------#
# install config file
#

cat << EOF_CONFIG > $REGISTRY_CONFIG_FULLPATH
common: &common
    standalone: true
    disable_token_auth: true

dev:
    <<: *common
    loglevel: debug
    storage: local
    storage_path: $REGISTRY_DBPATH
EOF_CONFIG



#---------------------------------------#
# install init script for Upstart
#

cat << EOF_INIT > /etc/init/docker-registry.conf
description "Docker Registry"

start on filesystem and started docker
stop on runlevel [!2345]

respawn

script

    docker run -d  \
        --name docker-registry   \
        --restart=always         \
        -p 80:5000               \
        -v $REGISTRY_CONFIG_DIR:/conf         \
        -v $REGISTRY_DBPATH:$REGISTRY_DBPATH  \
        -e DOCKER_REGISTRY_CONFIG=/conf/$REGISTRY_CONFIG_NAME  \
        registry

end script

EOF_INIT
