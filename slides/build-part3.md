name: inverse
layout: true
class: center, middle, inverse

---

.percent90[.center[![bg](img/cook-vector.jpg)]]

# 常見地雷／網路

???

Img src: http://www.vectorstock.com/royalty-free-vector/cook-vector-684665

---

layout: false

# Lab setup


.pull-left[
## VMs

1. `main`:
   - `up`
   - `ssh`

2. `registry`:
   - `up`
]


.pull-right[
## Lab directory
- `build-redis`
]

---

# Start the *Dockerized* Redis server...

Background (_**d**aemon_ or _**d**etached_) mode:

```bash
$ docker run -d  `THE_UGLY_IMAGE_ID`
```



<br/><br/>
Container status:

```bash
# current status
$ docker ps
```

---


# Try to connect to the *Dockerized* Redis server...

```bash
$ redis-cli
```

--
```
Could not connect to Redis at 127.0.0.1:6379: Connection refused
not connected>
```

<br/>
<br/>

.red[Why???]


---

template: inverse

# Docker networking models

### Devils in the Detail...


---

class: center, middle

.percent100[.center[![bg](img/docker-bridge.jpg)]]


.footnote[.red[*] Source: [Docker 源码分析（七）：Docker Container 网络（上）](http://blog.daocloud.io/docker-source-code-analysis-part7-first/)
]

---

# What Docker official document said...

> When Docker starts, it creates a virtual interface named `docker0` on the host machine.
> It randomly chooses an address and subnet from the private range defined by RFC 1918 that are not in use on the host machine, and assigns it to `docker0`.

> ... But `docker0` is no ordinary interface. It is a virtual *Ethernet bridge* that automatically forwards packets between any other network interfaces that are attached to it.


.footnote[Source: [Advanced networking](https://docs.docker.com/articles/networking/) at Docker.com
]


---

class: center, middle

# Docker Feature #4:
# .red[Isolation]: network resource is isolated from the host OS.



---

class: center, middle

# To be discussed in later labs...


---


# Summary: Isolation

<br/>

1. 常見地雷／檔案持久化 (Persistence)

   - Docker Feature #1: <br/>
     **Isolation**: file system resource is isolated from the host OS.

2. 常見地雷／網路

   - Docker Feature #4: <br/>
     **Isolation**: network resource is isolated from the host OS.


---

class: center, middle

# Questions?
