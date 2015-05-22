Reverse proxy example
===

## Purpose

Demonstrate how to use reverse proxy for backend application servers, all in the Docker's world.


## Software stack

![bg](reverse-proxy.png)


#### Nginx

 - [Reverse proxy](http://nginx.com/resources/admin-guide/reverse-proxy/)

 - [Load balancing](http://nginx.com/resources/admin-guide/load-balancer/)

 - [SSL termination](http://nginx.com/resources/admin-guide/nginx-ssl-termination/): use `make-cert.sh` to generate self-signed certificate.


#### HAProxy

 - Reverse proxy

 - Load balancing

 - SSL termination: use `make-cert.sh` to generate self-signed certificate.



#### Node.js application server instances

 - Source code in `app` directory.
 - *N* instances.
 - High availability and zero-downtime deployments via Nginx or HAProxy.


#### Redis server

 - Shared datastore across all Node.js application instances.
 - [Persistence](http://redis.io/topics/persistence): RDB and AOF modes.


## Usage

First, start the whole software stack:

```bash
$ docker-compose up -d

$ docker ps
```


Second, connect via HTTP :

```bash
# test Nginx
$ curl -v http://localhost:10080

# test HAProxy
$ curl -v http://localhost:10090
```

Third, connect via HTTPS :

```bash
# test Nginx
$ curl -v --insecure https://localhost:10443

# test HAProxy
$ curl -v --insecure https://localhost:10091
```
