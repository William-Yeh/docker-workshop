About this patch (ONBUILD version)
===

## Introduction

The original project [rauchg/chat-example](https://github.com/rauchg/chat-example) is a simple chatroom demo using Node.js + Socket.IO.

I patch the code a little bit to "Dockerize" it.


## Patch for Docker

1. Add: `Dockerfile`

2. Patch `package.json`: add a "start" section.


## Reference

`node:0.10.36-onbuild` Dockerfile: https://github.com/joyent/docker-node/blob/d23f190e500e91ecc636878a079ff971b29eab3e/0.10/onbuild/Dockerfile

See [`node` official repo](https://registry.hub.docker.com/_/node/) at Docker Hub for more ONBUILD assumptions.
