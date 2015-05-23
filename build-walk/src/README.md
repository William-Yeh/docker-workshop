Build instructions of rootfs tarballs for walk executables
===



## Source code of walk

Two versions of the same functionality are provided:

 - `c-version`: written in C
 - `golang-version`: written in Go



## Generate rootfs tarballs for walk-*


### Prepare

Use the `extract-elf-so` executable copied from the project: [`William-Yeh/extract-elf-so`](https://github.com/William-Yeh/extract-elf-so).

Install:

```bash
$ curl -sSL http://bit.ly/install-extract-elf-so \
    | sudo bash
```

### Extract required .so files from Ubuntu 14.04

Execute the following command under Ubuntu 14.04:

```bash
$ extract-elf-so  \
      -d /bin                    \
      -n rootfs-from-ubuntu1404  \
      -z                         \
      walk-c
```

An `rootfs-from-ubuntu1404.tar.gz` tarball will be generated, if successful.


### Extract required .so files from CentOS 5.11

Execute the following command under CentOS 5.11:

```bash
$ extract-elf-so  \
      -d /bin                   \
      -n rootfs-from-centos511  \
      -z                        \
      walk-c
```

An `rootfs-from-centos511.tar.gz` tarball will be generated, if successful.
