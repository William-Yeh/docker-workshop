#!/bin/bash
#
# append host entry into /etc/hosts
#
# [NOTE] better way -- use 'vagrant-hosts' plugin:
#        https://github.com/adrienthebo/vagrant-hosts
#

cat <<EOF >> /etc/hosts
10.0.0.200   registry.com
EOF
