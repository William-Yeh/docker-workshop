Building a Docker Registry box with pre-loaded images
===


## Name

Official box name in Atlas (was: Vagrant Cloud): [`williamyeh/docker-workshop-registry`](https://atlas.hashicorp.com/williamyeh/boxes/docker-workshop-registry).



## Purpose

To build a Vagrant box, which:

  - derives from [`williamyeh/insecure-registry`](https://vagrantcloud.com/williamyeh/insecure-registry) box (refer to [this](https://github.com/William-Yeh/docker-enabled-vagrant/tree/master/insecure-registry) for implementation details).
  - pre-loads Docker images listed in the `IMAGE-LIST` file from Docker Hub.



## Build it on your own...

### Prerequisite

Install [`vagrant-hosts`](https://github.com/adrienthebo/vagrant-hosts) plugin:

```bash
vagrant plugin install vagrant-hosts
```

### Build!


```bash
$ ./build.sh
```

If everything is OK, you'll obtain a box file `docker-workshop-registry.box`. Feel free to place it on your local disk or cloud storage (Dropbox, S3, etc).
