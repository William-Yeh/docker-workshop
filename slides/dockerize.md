name: inverse
layout: true
class: center, middle, inverse

---

.percent100[.center[![bg](img/WiseMonkeys-3.jpg)]]

# Dockerized app 必要條件

???

Img src: http://getacover.com/covers/9/8619_1532.jpg

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
- `build-nginx`
]


---

class: center, middle

.percent100[.center[![bg](img/dockerized-app.png)]]

---

template: inverse

# EXPOSE ports

## ☛ VII. Port binding :
Export services via port binding


.footnote[.red[*] See "[12 Factor App](http://12factor.net/)"
]

---

See previous Chat server example.

---

template: inverse

# data VOLUME

## ☛ IV. Backing Services:
Treat backing services as attached resources

.footnote[.red[*] See "[12 Factor App](http://12factor.net/)"
]


---

# Example: Nginx

Official document says: .red[*]

> ## ☛ How to use this image
> hosting some simple static content
>
> `docker run --name some-nginx  \` <br/>
> `   -v /some/content:/usr/share/nginx/html:ro  \` <br/>
> `   -d nginx`
> ## ☚

.footnote[.red[*] Official [`nginx`](https://registry.hub.docker.com/_/nginx/) at Docker Hub.]

---

# Try it!

1. Prepare an HTML file `index.html` at current directory.

--
2. Run an Nginx container:

   ```bash
   $ docker run -d --name nginx   \
        -p 10081:80               \
        -v $(pwd):/usr/share/nginx/html:ro  \
        nginx:1.7.9
   ```

--
3. Try to access it!

   ```bash
   $ curl  localhost:10081
   ```

--
4. Or, use your favorite browser from the host machine!

---

template: inverse

# stdout/stderr

## ☛ XI. Logs
Treat logs as event streams

.footnote[.red[*] See "[12 Factor App](http://12factor.net/)"
]

---

class: center, middle

TL;DR

# Stay foreground in your app.
# Let Docker do necessary daemonize stuff for you.

---

# Avoid "daemonize" yourself

> Twelve-factor app processes should never daemonize or write PID files. Instead, rely on the operating system’s process manager (such as Upstart...) to manage output streams, respond to crashed processes, and handle user-initiated restarts and shutdowns.

.footnote[.red[*] Quote: 12 Factor App: [VIII. Concurrency](http://12factor.net/concurrency)]
---

# Lab directory

`build-nginx`

---

# FYI, "dockerize" tool

"An utility to simplify running applications in docker containers."

- Source at GitHub: [jwilder/dockerize](https://github.com/jwilder/dockerize)

- Article: "[A Simple Way to Dockerize Applications](http://jasonwilder.com/blog/2014/10/13/a-simple-way-to-dockerize-applications/)"


---

class: center, middle

# Questions?
