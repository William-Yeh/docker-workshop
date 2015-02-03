Build a naive Redis image for CentOS 5
===


## Purpose

Demostrate how to build a naive Redis image from Dockerfile.

This lab uses a pre-downloaded RPM file to minimize time to completion. Alternatives have drawbacks for this lab:

  - Building from tarball source will require `gcc`, `make` and other dependencies.
  - Installing by `yum` will require downloading packages on-the-fly.

It is just a naive demo, especially in early workshop stages. For a better Dockerfile to learn from, see [official repo](https://registry.hub.docker.com/_/redis/).


## Package

Redis:

  - Rpmfind: [`remi`](http://www.rpmfind.net/linux/rpm2html/search.php?query=redis)

  - RPM file: [redis-2.8.19-1.el5.remi.x86_64.rpm](http://www.rpmfind.net//linux/RPM/remi/enterprise/5/x86_64/redis-2.8.19-1.el5.remi.x86_64.html)

jemalloc:

  - Rpmfind: [`EPEL`](http://www.rpmfind.net/linux/rpm2html/search.php?query=libjemalloc.so.1%28%29%2864bit%29)

  - RPM file: [jemalloc-3.6.0-2.el5.x86_64.rpm](http://www.rpmfind.net//linux/RPM/epel/5/x86_64/jemalloc-3.6.0-2.el5.x86_64.html)

