Build instructions of rootfs tarballs for walk-tree executables
===



## Source code of walk-tree

 - `c-version`: written in C
 - `golang-version`: written in Go



## Generate rootfs tarballs for walk-tree-*

Use the `extract-elf-so_static_linux-amd64` executable, which is copied from the project: [`William-Yeh/extract-elf-so`](https://github.com/William-Yeh/extract-elf-so).


### Extract required .so files from CentOS 5.11

Execute the following command under CentOS 5.11:

```bash
$ ./extract-elf-so_static_linux-amd64  \
      -d /bin                   \
      -n rootfs-from-centos511  \
      -z                        \
      walk-tree-c
```

An `rootfs-from-centos511.tar.gz` tarball will be generated, if successful.


### Extract required .so files from Ubuntu 14.04

Execute the following command under Ubuntu 14.04:

```bash
$ ./extract-elf-so_static_linux-amd64  \
      -d /bin                    \
      -n rootfs-from-ubuntu1404  \
      -z                         \
      walk-tree-c
```

An `rootfs-from-ubuntu1404.tar.gz` tarball will be generated, if successful.

