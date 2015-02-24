Build a naive PHP/Node.js + mcrypt image for Ubuntu 14.04 LTS (Trusty)
===


## Purpose

Demostrate how to build a naive PHP/Node.js + mcrypt image from Dockerfile.

This lab uses pre-downloaded DEB files to minimize time to completion. Alternatives have drawbacks for this lab:

  - Building from tarball source will require `build-essential`.
  - Installing by `apt-get` will require downloading packages on-the-fly.

It is just a naive demo, especially in early workshop stages. For a better Dockerfile to learn from, see [official PHP repo](https://registry.hub.docker.com/_/php/) and [official Node.js repo](https://registry.hub.docker.com/_/node/).


## Package

Package: [`libmcrypt4`](http://packages.ubuntu.com/trusty/libmcrypt4) and [`libmcrypt-dev`](http://packages.ubuntu.com/trusty/libmcrypt-dev)

DEB files: see http://mirrors.kernel.org/ubuntu/pool/universe/libm/libmcrypt/
