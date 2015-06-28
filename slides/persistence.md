name: inverse
layout: true
class: center, middle, inverse

---

.percent90[.center[![bg](img/cook-vector.jpg)]]

# 常見地雷／檔案持久化 (Persistence)

???

Img src: http://www.vectorstock.com/royalty-free-vector/cook-vector-684665

---

layout: false

# Lab setup

--

.pull-left[
## VMs

1. `main`:
   - `up`
   - `ssh`
]

--

.pull-right[
## Lab directory
- `build-io`
]

---

template: inverse

# Layers

## Which base image to build from?

---

# Again, the minimal approach...

- .red[☛ ☛ ☛ **Minimalism: based on `scratch` or `busybox`** ☚ ☚ ☚]

  - See: [Quest for minimal Docker images 【追求極簡化 Docker image 之路】](http://bit.ly/docker-mini)

- Modest: barebone Linux distributions
  - Reuse your existing Linux experiences: make, ant, apt-get, yum...

- Convenience: programming languages installed
  - Reuse your existing experiences: gem, maven, npm, pip...


---

# Let's build a Docker image from a 2.5 MB base!

.percent90[.center[![bg](img/cook-vector.jpg)]]

Add something to the `busybox` **base image**.

---

# We're going to do...

Add the `io.sh` file to the `busybox` base image.

### Target image layout

```
             +-------------------------------------+
             |                                     |
             |                                     |
             |  script file: io.sh      (< 0.5 kB) |
             |                                     |
             |                                     |
             +-------------------------------------+
             |                                     |
             |                                     |
             |  base image:  busybox      (2.5 MB) |
             |                                     |
             |                                     |
             +-------------------------------------+
```


---

# About the `io.sh` script

Append date info to specified output file (default: `/tmp/output`), and display its content.

--


```bash
#!/bin/sh

OUTPUT=${1:-/tmp/output}

# create output file, if not exist...
if [ ! -f "$OUTPUT" ]; then
    touch $OUTPUT
fi


# append date info
date >> $OUTPUT


# display the content of output file
cat $OUTPUT
```

---

# Try it first!

```bash
$ ./io.sh
$ ./io.sh
$ ./io.sh

$ cat /tmp/output
```

---

# We're going to do (revisited)...

Add the `io.sh` file to the `busybox` base image.

### Target image layout

```
             +-------------------------------------+
             |                                     |
             |                                     |
             |  script file: io.sh      (< 0.5 kB) |
             |                                     |
             |                                     |
             +-------------------------------------+
             |                                     |
             |                                     |
             |  base image:  busybox      (2.5 MB) |
             |                                     |
             |                                     |
             +-------------------------------------+
```

---

class: center, middle

# Dockerfile

## "Makefile" for Docker images


---

# Dockerfile for "io.sh"

```dockerfile
# base image: busybox
FROM  busybox

# copy to image/container
COPY  io.sh  /usr/local/bin/

# define the default command for convenience
CMD  ["io.sh"]
```

.footnote[.red[☛] Open 〈[Dockerfile 指令](http://philipzheng.gitbooks.io/docker_practice/content/dockerfile/instructions.html)〉 and "[Dockerfile Reference](https://docs.docker.com/reference/builder/)" side by side for your easy reference.]

---

# 逐行拆解 Dockerfile 指令

## #1: Base image

```dockerfile
FROM  busybox
```

--

<br/><br/>
Remember image hierarchy?

```bash
$ dockviz images --tree
```

---

# 逐行拆解 Dockerfile 指令

## #2: Add something to target image

```dockerfile
COPY  io.sh  /usr/local/bin/
```

.percent50[.center[![bg](img/cook-vector.jpg)]]


???

Img src: http://www.vectorstock.com/royalty-free-vector/cook-vector-684665


---

# 逐行拆解 Dockerfile 指令

## #3: Default start cmd for the target image

```dockerfile
# define the default command for convenience
CMD  ["io.sh"]
```

.footnote[.red[*] In this case, `/usr/local/bin/io.sh`.]

---

# Build it!

```bash
$ docker build .
```

.percent50[.right[![bg](img/app-building-dockerway.svg)]]


.footnote[.red[*] See the _very very very ugly_ ID?]


---

# Look at what we've built...


```bash
$ docker images
```

.footnote[.red[*] See the _very very very ugly_ ID?]

--

Or,

```bash
$ dockviz images --tree
```

---

# 收割時刻：Run it!

Foreground mode:

```bash
$ docker run  `THE_UGLY_IMAGE_ID`
```

--

<br/><br/>
Container status:

```bash
# current status
$ docker ps

# historical status
$ docker ps -a
```



---

# Image IDs and Container IDs


<br/>

>| Static Structure | ↔ | Dynamic Behavior |
|:----------------:|---|:----------------:|
|  image 映像檔     | ↔ |  container 容器   |


--

.pull-left[
- images:

   ```bash
   $ docker images
   ```
]

.pull-right[
- containers:

   ```bash
   $ docker ps
   ```
]


---

template: inverse

#Naming

.center[![bg](img/TwoHardThings.png)]

.right[Source: http://martinfowler.com/bliki/TwoHardThings.html]

---

# Image naming

- Method 1: name it *after* building:

  ```bash
  $ docker tag  `THE_UGLY_IMAGE_ID`  `IMAGE_NAME`
  ```

--
  ... also tag it:

  ```bash
  $ docker tag  `THE_UGLY_IMAGE_ID`  `IMAGE_NAME`:`TAG`
  ```


--

- Method 2: name it *while* building:

  ```bash
  $ docker build  -t `IMAGE_NAME`  .
  ```

--
  ... also tag it:

  ```bash
  $ docker build  -t `IMAGE_NAME`:`TAG`  .
  ```

---

# Container naming

- Method 1: name it *while* invoking:

  ```bash
  $ docker run  \
        --name `CONTAINER_NAME` \
        `IMAGE_ID_or_NAME`
  ```

--

- Method 2: rename an existing container .red[*]:

  ```bash
  $ docker rename  \
        `OLD_CONTAINER_NAME`  \
        `NEW_CONTAINER_IMAGE`
  ```


.footnote[.red[*] Since Docker 1.5.0.]

---

template: inverse

# 檔案持久化
## Persistence

---

# Is the output file correct?

```bash
$ docker build  -t io  .

$ docker run io
$ docker run io
$ docker run io
```

--

```bash
$ docker ps -a

$ cat /tmp/output
```

--

<br/>
<br/>
.red[What's wrong with the Docker version?]


---

# Isolation: file system resource

```
|                                                                       |
|      +-------------------------------------+                          |
|      |                                     |                          |
|      | resources injected by Docker engine |                          |
|      | (/etc/hosts, /etc/resolv.conf, etc) |                          |
|      |                                     |                          |
|      +-------------------------------------+                          |
|      |                                     |                          |
|      |                                     |                          |
|      |  script file: io.sh      (< 0.5 kB) |                          |
|      |                                     |                          |
|      |                                     |                          |
|      +-------------------------------------+                          |
|      |                                     |                          |
|      |                                     |                          |
|      |  base image:  busybox      (2.5 MB) |                          |
|      |                                     |                          |
|      |                                     |                          |
|      +-------------------------------------+                          |
|                 Docker container                                      |
|                                                  host machine         |
|                                                  root file system     |
|                                                                       |
+-----------------------------------------------------------------------+
```

---

# Solution: volume mounting

.right[`-v ` &nbsp; *host_directory*`:`*container_directory*]

<br/>

- Mount a host directory `$(pwd)` as a data volume `/tmp`:

  ```bash
  $ docker run         \
        -v $(pwd):/tmp   \
        io
  ```

--
  ```bash
  $ cat  ./output
  ```

---

class: center, middle

# Questions?
