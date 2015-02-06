name: inverse
layout: true
class: center, middle, inverse

---

.percent80[.center[![bg](img/CodeMonkey-3.jpg)]]

# 編譯示範／從源碼建 image

???

Img src: http://zikayn.com/blog/wp-content/uploads/2011/12/monkey-5.jpg

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
- `build-chat`
]

---

# 這次沒有 DEB 或 RPM 了...


```bash
$ tree
.
├── ABOUT-THIS-PATCH.md
├── Dockerfile
├── README.md
├── index.html
├── index.js
└── package.json
```

--

### 可是，有 Node.js 程式碼檔案，

### ... 還有 dependency 設定...

---

# Dependencies

`package.json`:

```json
{
    "name": "socket-chat-example",
    "version": "0.0.1",
    "description": "my first socket.io app",
    "scripts": {
        "start": "node index.js"
    },
    "dependencies": {
        "express": "4.10.2",
        "socket.io": "1.2.0"
    }
}
```

---

template: inverse

## ☛ II. Dependencies
Explicitly declare and isolate dependencies

.footnote[.red[*] See "[12 Factor App](http://12factor.net/)"
]

---

# Dockerfile

## "Makefile" for Docker images

.percent50[.right[![bg](img/app-building-dockerway.svg)]]

---

# Dockerfile for this chat server

```dockerfile
FROM  node:0.10.36-slim

RUN      mkdir -p /app
WORKDIR  /app

COPY     package.json  /app/
RUN      npm install --production
COPY     .  /app

EXPOSE   3000
CMD      [ "npm", "start" ]
```

.footnote[.red[☛] Open 〈[Dockerfile 指令](http://philipzheng.gitbooks.io/docker_practice/content/dockerfile/instructions.html)〉 and "[Dockerfile Reference](https://docs.docker.com/reference/builder/)" side by side for your easy reference.]

---

# 逐行拆解 Dockerfile 指令

## #1: Base image

```dockerfile
FROM  node:0.10.36-slim
```

.footnote[.red[*] Docker Hub: https://registry.hub.docker.com/_/node/ ]

--

Remember image hierarchy?

```bash
$ docker images --tree
```

---

# 逐行拆解 Dockerfile 指令

## #2: prepare directory inside the image

```dockerfile
# 建新目錄
RUN      mkdir -p /app

# 設定：以下各行的 Dockerfile 命令，皆以此為工作目錄
WORKDIR  /app
```

--

也可依循傳統 Linux 慣例，把軟體安裝在 image 裡面的 `/usr/local` 或 `/opt` 等處。

---

# 逐行拆解 Dockerfile 指令

## #3: Add something to target image

```dockerfile
COPY  package.json  /app/
```

.percent50[.center[![bg](img/cook-vector.jpg)]]


???

Img src: http://www.vectorstock.com/royalty-free-vector/cook-vector-684665

---

# 逐行拆解 Dockerfile 指令

## #4: Run commands within target image

```dockerfile
#--  install dependencies from Nodejs NPM system
RUN  npm install --production
```


---

# 逐行拆解 Dockerfile 指令

## #5: Ports to be exposed


```dockerfile
EXPOSE  3000
```

.footnote[.red[*] Good practice: Treat Dockerfile as a spec.]

--

<br/>

- TCP port 3000 is defined in `index.js`:

  ```javascript
  http.listen(3000, function(){ /*... */ });
  ```

---

# 逐行拆解 Dockerfile 指令

## #6: Default start cmd for the target image

```dockerfile
# start chat server
CMD  [ "npm", "start" ]
```

.footnote[.red[*] In this case, `/usr/local/bin/npm` <br/> as provided from the base image `node:0.10.36-slim`.]

---

# Build it!

```bash
$ docker build .
```

.percent50[.right[![bg](img/app-building-dockerway.svg)]]


---

# Look what we've built...


```bash
$ docker images
```

Or,

```bash
$ docker images --tree
```

---

# 收割時刻：Run it!

Foreground mode:

```bash
$ docker run  `IMAGE_ID_OR_NAME`
```

<br/>
**Ctrl-C** to stop.


---

# 收割時刻：Run it!

Background mode (_**d**aemon_ mode):

```bash
$ docker run -d  `IMAGE_ID_OR_NAME`
```

--

Is it running?

```bash
# process?
$ ps aux | grep node

# current status
$ docker ps
```

---

# Try to connect to it?

```bash
$ curl http://localhost:3000
curl: (7) Failed to connect to localhost port 3000: Connection refused


$ curl http://127.0.0.1:3000
curl: (7) Failed to connect to 127.0.0.1 port 3000: Connection refused
```

--

<br/>
<br/>
## WHY?

---

template: inverse

# Docker networking models

---

# Devils in the Detail...

Low-level information on a container or image

```bash
Usage: docker inspect [OPTIONS] CONTAINER|IMAGE [CONTAINER|IMAGE...]

Return low-level information on a container or image

  -f, --format=""    Format the output using the given go template.
```

.footnote[.red[*] See [official reference](https://docs.docker.com/reference/commandline/cli/#inspect) for more details.]

---

# Port mappings

Usage

```bash
$ docker port

Usage: docker port CONTAINER [PRIVATE_PORT[/PROTO]]

List port mappings for the CONTAINER,
or lookup the public-facing port
              that is NAT-ed to the PRIVATE_PORT
```

---

# Re-run with port mapping...

```bash
$ docker run -d   -p 10800:3000   `IMAGE_ID_OR_NAME`
```

--

<br/>
<br/>
檢查看看 port mapping 是否生效...

```bash
$ docker port  `CONTAINER_ID_OR_NAME`
3000/tcp -> 0.0.0.0:10800
```

--

試著連線看看...

```bash
$ curl http://127.0.0.1:10800
```

---

class: center, middle

# 用瀏覽器玩玩看吧...

.percent90[![topology](img/lab-topology-4.svg)
]

---

# Quiz

這次的 Dockerfile 有一個地方用途重疊。

請設法找出，修改，並以這個修正版重新執行。

```dockerfile
FROM  node:0.10.36-slim

RUN      mkdir -p /app
WORKDIR  /app

COPY     package.json  /app/
RUN      npm install --production
COPY     .  /app

EXPOSE   3000
CMD      [ "npm", "start" ]
```


---

# 其他語言？

## Python: pip

例子：官方版 [`registry`](https://registry.hub.docker.com/_/registry/) 的 [Dockerfile](https://github.com/docker/docker-registry/blob/master/Dockerfile)：

```dockerfile
...

# Install core
RUN pip install /docker-registry/depends/docker-registry-core

# Install registry
RUN pip install file:///docker-registry#egg=docker-registry[bugsnag,newrelic,cors]

...
```

---

# 其他語言？

## Ruby: gem

例子：[`williamyeh/fluentd`](https://registry.hub.docker.com/u/williamyeh/fluentd/) 的 [Dockerfile](https://github.com/William-Yeh/docker-fluentd/blob/master/Dockerfile)：

```dockerfile
...

$FLUENT_GEM install \
        fluent-plugin-secure-forward  \
        fluent-plugin-watch-process   \
        fluent-plugin-multiprocess    \
        fluent-plugin-docker-metrics  \
        fluent-plugin-elasticsearch   \
        fluent-plugin-kafka           \
        --no-rdoc --no-ri  && \
...
```


---

class: center, middle

# Questions?
