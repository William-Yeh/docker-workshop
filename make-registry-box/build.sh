#!/bin/bash

readonly BOX_FILE=docker-workshop-registry.box
#readonly BOX_FILE=output.box


vagrant halt
vagrant destroy --force

vagrant up
vagrant package --output $BOX_FILE

vagrant destroy --force
