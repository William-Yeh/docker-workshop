name: inverse
layout: true
class: center, middle, inverse

---

.center[![bg](img/CodeMonkey-1.jpg)]

# Memo #1: 安裝說明

???

Img src: http://andrewgarrison.com/wp-content/uploads/2012/10/CodeMonkey-68762_960x360.jpg


---

layout: false

# 使用情境

- Linux machines

- Local VMs

- IaaS platforms

- CaaS platforms

---

.left-column[
  ## Linux
]

.right-column[

See https://docs.docker.com/

- CentOS
- Debian
- RHEL
- Ubuntu
- ...

]

---

.left-column[
  ## Linux
  ## Local VMs
]

.right-column[

1. [Boot2Docker](http://boot2docker.io/) (for Windows and Mac OS X)
   - [VirtualBox](https://www.virtualbox.org/) 
   - [Tiny Core Linux](http://tinycorelinux.net/) in VirtualBox

2. [Docker Machine](https://docs.docker.com/machine/)
   - download a Boot2Docker VM with `docker-machine create --driver virtualbox`

3. [Kitematic](https://docs.docker.com/kitematic/) (for Windows and Mac OS X)
   - [VirtualBox](https://www.virtualbox.org/)
   - Kitematic GUI app

4. [Vagrant](https://www.vagrantup.com/)
   - [VirtualBox](https://www.virtualbox.org/), [VMware Workstation](http://www.vmware.com/tw/products/workstation/), [VMware Fusion](http://www.vmware.com/tw/products/fusion), [Parallels Desktop](http://www.parallels.com/products/desktop/)
   - Any Linux (e.g., [docker-enabled-vagrant](https://github.com/William-Yeh/docker-enabled-vagrant))

]


---

.left-column[
  ## Linux
  ## Local VMs
  ## IaaS
]

.right-column[

1. Pick any modern Linux distribution, and install Docker in it (see https://docs.docker.com/)

2. Pick any pre-installed cloud image
   - [CoreOS](https://coreos.com/)<br/><br/>
   - AWS: [Amazon ECS-Optimized Amazon Linux AMI](https://aws.amazon.com/marketplace/pp/B00U6QTYI2)
   - GCP: [Container-optimized image](https://cloud.google.com/compute/docs/containers/container_vms)
   - Azure: [Docker VM Extension](https://azure.microsoft.com/en-us/documentation/articles/virtual-machines-docker-vm-extension/)
   - ...

]


---

.left-column[
  ## Linux
  ## Local VMs
  ## IaaS
  ## CaaS
]

.right-column[

1. [Google Container Engine](https://cloud.google.com/container-engine/)

2. Amazon [EC2 Container Service (ECS)](http://aws.amazon.com/tw/ecs/)

]



---



.left-column[
  ## XXX
]

.right-column[

**TODO**: XXX

]

---

.left-column[
  ## XXX
  ## - YYY
]

.right-column[

**TODO**: YYY

]

---






