#!/bin/bash
#
# generates fluentd conf on-the-fly for specific running container.
#
# NOTE: see docker-gen for more complete solution:
#       http://jasonwilder.com/blog/2014/03/17/docker-log-management-using-fluentd/
#

if [ $# -lt 1 ]; then
    echo "Generates fluentd conf on-the-fly for specific running container."
    echo "Usage: gen-fluentd-conf.sh  container_name  [pos_file_directory]"
    exit 1
fi


readonly CONTAINER_NAME=$1
readonly CONTAINER_ID=`sudo docker inspect --format="{{ .Id }}" $CONTAINER_NAME`
readonly LOG_FULLPATH=/var/lib/docker/containers/$CONTAINER_ID/$CONTAINER_ID-json.log

readonly POS_FILE_DIRECTORY=${2:-/data}
readonly POS_FILE_FULLPATH=$POS_FILE_DIRECTORY/$CONTAINER_ID-json.log.pos

#echo $CONTAINER_ID
#echo $LOG_FULLPATH





cat <<EOF
<source>
    type         tail
    format       json
    time_key     time
    time_format  %Y-%m-%dT%H:%M:%S.%L

    path         $LOG_FULLPATH
    pos_file     $POS_FILE_FULLPATH
    rotate_wait  5

    tag          docker.$CONTAINER_NAME.$CONTAINER_ID
</source>


<match docker.**>
    type copy

    <store>
        # for debug (see /var/log/td-agent.log)
        type stdout
    </store>

    <store>
        # @see https://github.com/uken/fluent-plugin-elasticsearch
        type elasticsearch

        #host localhost
        #port 9200
        logstash_format  true
        logstash_prefix  docker.spray
        include_tag_key  true
        tag_key          _key
    </store>
</match>
EOF
