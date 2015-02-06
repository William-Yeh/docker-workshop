name: inverse
layout: true
class: center, middle, inverse

---

.center[![bg](img/CodeMonkey-1.jpg)]

# 大雜燴

???

Img src: http://andrewgarrison.com/wp-content/uploads/2012/10/CodeMonkey-68762_960x360.jpg

---

layout: false

# Lab setup

.pull-left[
## VMs

1. `centos`:
   - `up`
   - `ssh`

2. `main`:
   - `up`
   - `ssh`

3. `registry`:
   - `up`
]

.pull-right[
## Lab directory
- `linking-full`
]

---

class: center, middle


.percent150[![bg](img/flows.png)]


---

# Step 1

Clear all unused container records:

```bash
$ docker rm  $(docker ps --no-trunc -a -q)
```

--

Or, use my wrapper: .red[*]

```bash
$ docker-rm-stopped
```

.footnote[.red[*] See [William-Yeh/docker-host-tools](https://github.com/William-Yeh/docker-host-tools) at GitHub.]

---

# Step 2

Start the http server (with the container name `spray`):

   ```bash
   $ docker run -d --name spray  \
         williamyeh/spray-httpserver
   ```

---

# Step 3

Tail the logs of the http server, and keep this console open:

   ```bash
   $ docker logs -f spray
   ```

---

# Step 4

Open another console.  Use `wrk` to benchmark the http server:

   ```bash
   $ docker run --link spray:httpserver \
         williamyeh/wrk  http://httpserver:8080/
   ```

---

# Step 5

Use `wrk` to benchmark the http server, with random IPs as input:

```bash
$ docker run --link spray:httpserver  \
    -v $(pwd):/data  \
    williamyeh/wrk  -s wrk-script.lua  http://httpserver:8080/
```

---

# Step 6

Generate Fluentd conf file `td-agent.conf` for capturing logs produced by the `spray` container:

```bash
$ ./gen-fluentd-conf.sh  spray  > td-agent.conf
```

---

# Step 7

Use `fluentd` to collect the `spray` logs:

```bash
$ docker run -it                 \
    -v /var/lib/docker/containers:/var/lib/docker/containers:ro  \
    -v $(pwd):/etc/td-agent:ro   \
    -v $(pwd):/data              \
    --net=host                  \
    williamyeh/fluentd  start
```

---

# Step 8

Re-run previous `wrk` task to see the `fluentd` output!

---

# Step 9

Start the `Elasticsearch` server:

```bash
$ docker run -d  --name elasticsearch  \
     -p 9200:9200  \
     digitalwonderland/elasticsearch
```

---

# Step 10

Use browser to open the Kibana page:

  - http://localhost:9200/_plugin/kibana3/


---

# Step 11

You may also re-run previous `wrk` task to see the Kibana dashboard!

---

class: center, middle

# Recap

.percent150[![bg](img/flows.png)]

---

class: center, middle

# Questions?
