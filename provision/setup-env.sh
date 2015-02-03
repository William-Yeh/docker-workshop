#!/bin/bash
#
# append PRIVATE_DOCKER_REGISTRY global env
#

cat <<EOF >> /etc/environment
PRIVATE_DOCKER_REGISTRY="registry.com"
EOF

