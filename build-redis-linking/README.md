Build a naive Redis image (and some wrappers) for Ubuntu 14.04 LTS (Trusty)
===


## Purpose

Demostrate how to build a naive Redis image (and some wrappers) from Dockerfile.

This lab uses a pre-downloaded DEB file to minimize time to completion. Alternatives have drawbacks for this lab:

  - Building from tarball source will require `build-essential`.
  - Installing by `apt-get` will require downloading packages on-the-fly.

It is just a naive demo, especially in early workshop stages. For a better Dockerfile to learn from, take [williamyeh/redis](https://registry.hub.docker.com/u/williamyeh/redis/) as a starting point.


## Package

PPA: [`ppa:rwky/redis`](https://launchpad.net/~rwky/+archive/ubuntu/redis)

DEB file: [2:2.8.19-rwky1~trusty](https://launchpad.net/~rwky/+archive/ubuntu/redis/+files/redis-server_2.8.19-rwky1~trusty_amd64.deb)

