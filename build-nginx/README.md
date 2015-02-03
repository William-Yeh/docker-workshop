Build a naive Nginx image for Ubuntu 14.04 LTS (Trusty)
===


## Purpose

Demostrate how to build a naive Nginx image from Dockerfile.

This lab uses a pre-downloaded DEB file to minimize time to completion. Alternatives have drawbacks for this lab:

  - Building from tarball source will require `build-essential`.
  - Installing by `apt-get` will require downloading packages on-the-fly.

It is just a naive demo, especially in early workshop stages. For a better Dockerfile to learn from, see [official repo](https://registry.hub.docker.com/_/nginx/).


## Package

PPA: [`ppa:nginx/stable`](https://launchpad.net/~nginx/+archive/ubuntu/stable)

DEB file: [nginx-full_1.6.2-5+trusty0_amd64.deb](https://launchpad.net/~rwky/+archive/ubuntu/redis/+files/redis-server_2.8.19-rwky1~trusty_amd64.deb)

