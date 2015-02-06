name: inverse
layout: true
class: center, middle, inverse

---

.percent80[.center[![bg](img/WiseMonkeys-2.jpg)]]

# 與 Native Process 比較

???

Img src: http://digital-art-gallery.com/picture/big/272

---

layout: false

# Lab setup

--

.pull-left[
## VMs

1. `main`:
   - `up`
   - `ssh`

2. `registry`:
   - `up`
]

--

.pull-right[
## Lab directory
- `build-redis`
]

---

class: center, middle

# "In most cases, a *dockerized app* acts as a normal *native process* within the host OS."

---

# 分析！

.pull-left[
## In Theory
]

.pull-right[
## In Practice
]

---

## In Theory

---

class: center, middle

# “In theory, theory and practice are the same.  In practice, they are not.”

― Albert Einstein

---

## In Practice

- Process view

- Runtime performance

---

# 前置作業

1. 回復至初始狀態，登入

   ```bash
   $ vagrant snapshot back  main
   $ vagrant ssh            main
   ```
--
2. 安裝 Redis (native process)

   ```bash
   $ sudo dpkg -i /vagrant/build-redis/redis-server_2.8.19.deb
   $ sudo service  redis-server  stop
   ```
--
3. 安裝 Redis (Docker 版) .red[*]

   ```bash
   $ DOCKER pull  williamyeh/redis:2.8.19
   ```

.footnote[.red[*] See [williamyeh/redis](https://registry.hub.docker.com/u/williamyeh/redis/) at Docker Hub for more info.
]

---

template: inverse

# Task #1: Process view

---

# Task 1A: Native version

啟動 Redis server：

```bash
$ sudo service  redis-server  start
```

--

檢視 process 資訊：

```bash
$ ps aux | grep redis
```
--

... 或是 process tree：

```bash
$ ps faux
```

---

# Task 1B: Docker version

啟動 Redis container：

```bash
$ docker run -d  williamyeh/redis:2.8.19  start
```

--

檢視 process 資訊：

```bash
$ ps aux | grep redis
```
--

... 或是 process tree：

```bash
$ ps faux
```

---

class: center, middle

# Similar?

---

template: inverse

# Task #2: Runtime performance

---

# 前置作業

先關閉各種版本的 Redis server：

```bash
$ sudo service   redis-server  stop
$ sudo pkill -f  redis
```

--

看看是否還有漏網之魚...

```bash
$ ps aux | grep redis
```

---

# Task 2A: Native version

啟動 Redis server：

```bash
$ sudo service  redis-server  start
```
--

跑 benchmark：

```bash
$ redis-benchmark
```

--

跑完後，暫時關閉 Redis server：

```bash
$ sudo service   redis-server  stop
```

---

# Task 2B: Docker version

啟動 Redis server：

```bash
$ docker run -d  --name redis  \
    -v $(pwd):/data            \
    williamyeh/redis:2.8.19  start
```
--

跑 benchmark：

```bash
$ docker run --rm       \
    --link redis:redis  \
    williamyeh/redis:2.8.19  benchmark
```

---

# For more performance details...

➤ *Performance Comparison of Virtual Machines and Linux Containers*:

   - Author: IBM
   - Presented at DockerCon 2014
   - [Video](http://youtu.be/JHqM_5X3MBU) at YouTube
   - [Slides](http://www.slideshare.net/BodenRussell/performance-characteristics-of-traditional-v-ms-vs-docker-containers-dockercon14) at SlideShare
   - [Paper](http://domino.research.ibm.com/library/CyberDig.nsf/papers/0929052195DD819C85257D2300681E7B/$File/rc25482.pdf): Felter, Wes, et al. "An Updated Performance Comparison of Virtual Machines and Linux Containers." *technology* 28: 32.


➤ *Docker Tips And Tricks*:

   - Author: Jérôme Petazzoni 大神
   - Presented at the Docker Beijing Meetup 2014
   - [Slides](http://www.slideshare.net/jpetazzo/docker-tips-and-tricks-at-the-docker-beijing-meetup) at SlideShare


---

template: inverse

# Recap
## Containerization vs Native processes

---

class: center, middle

# "In most cases, a *dockerized app* acts as a normal *native process* within the host OS."

---

class: center, middle

# Questions?
