Build a derived Nginx image for Ubuntu 14.04 LTS (Trusty)
===


## Purpose

 - Demostrate how to build derived Nginx image(s) from Dockerfile(s).

 - Demostrate different behaviors while running Nginx with/without the "daemon off" flag.


## Build a (correct!) daemon-off Nginx image

- Docker 1.5.0 or higher:

  ```
  $ docker build  -f Dockerfile-daemon-off  .
  ```

- Docker 1.4.1 or lower:

  ```
  $ cp  Dockerfile-daemon-off  Dockerfile
  $ docker build  .
  ```

## Build an (incorrect!) daemonize Nginx image

- Docker 1.5.0 or higher:

  ```
  $ docker build  -f Dockerfile-daemonize  .
  ```

- Docker 1.4.1 or lower:

  ```
  $ cp  Dockerfile-daemonize  Dockerfile
  $ docker build  .
  ```
