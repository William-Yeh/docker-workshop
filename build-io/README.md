File I/O example
===

This directory demonstrates several Docker topics:

- The usefulness of **volume** mechanism in Docker.
- The `docker logs` command.


## Steps

1. Run without Docker

   ```bash
   $ ./io.sh
   $ ./io.sh
   $ ./io.sh

   $ cat /tmp/output
   ```


2. Run with Docker, without volume mechanism

   ```bash
   $ docker build -t io .

   $ docker run io
   $ docker run io
   $ docker run io

   $ cat /tmp/output

   $ docker ps -a
   $ docker logs <container id>
   ```


3. Run with Docker, with volume mechanism

   ```bash
   $ docker run  -v $(pwd):/tmp  io
   $ docker run  -v $(pwd):/tmp  io
   $ docker run  -v $(pwd):/tmp  io

   $ cat ./output

   $ docker ps -a
   $ docker logs <container id>
   ```
