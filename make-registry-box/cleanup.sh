#!/bin/bash

# clean up docker's execution trace
sudo docker kill docker-registry
sudo docker rm `sudo docker ps --no-trunc -a -q`

# clean "registry.com" host entry
sed -i -e \
  's/^.*registry.com$//' \
  /etc/hosts


sudo rm -f \
  /var/log/messages   \
  /var/log/lastlog    \
  /var/log/auth.log   \
  /var/log/syslog     \
  /var/log/daemon.log \
  /var/log/docker.log


#---------------------------------------#
# Vagrant-specific settings below
#


# zero out the free space to save space in the final image
sudo dd if=/dev/zero of=/EMPTY bs=1M
sudo rm -f /EMPTY


rm -f /home/vagrant/.bash_history  /var/mail/vagrant
