#!/bin/bash

REDIS_VERSION=3.0.0

echo "==> Install curl and helper tools..."
sudo apt-get install -y  curl make gcc


echo "==> Compile..."
tar zxvf redis-$REDIS_VERSION.tar.gz
cd redis-$REDIS_VERSION
make


echo "==> Copy aux files..."
cp redis.conf   ..


echo "==> Clear screen..."
cd ..
clear


echo "==> Investigate required .so files..."
ldd redis-$REDIS_VERSION/src/redis-server


echo "==> Extract .so files and pack them into rootfs.tar.gz..."
../extract-elf-so_static_linux-amd64  \
  -z  \
  redis-$REDIS_VERSION/src/redis-server
