Reverse proxy example
===

## Purpose

Demonstrate how to use reverse proxy for backend application servers.


## Software stack

**Nginx**:

 - [Reverse proxy](http://nginx.com/resources/admin-guide/reverse-proxy/)

 - [Load balancing](http://nginx.com/resources/admin-guide/load-balancer/)

 - [SSL termination](http://nginx.com/resources/admin-guide/nginx-ssl-termination/): use `make-cert.sh` to generate self-signed certificate.


**Node.js application server instances**:

 - Source code in `app` directory.
 - *N* instances.
 - Zero-downtime deployments.

**Redis server**:

 - Shared across Node.js application instances.
 - Persistence RDB and AOF modes.


## Usage

First, start the whole software stack:

```bash
$ docker-compose up -d

$ docker ps
```


Second, connect via HTTP :

```bash
$ curl -v http://localhost:10080
```

Third, connect via HTTPS :

```bash
$ curl -v --insecure https://localhost:10443
```
