#!/bin/bash

openssl req -new -x509 -sha256 -newkey rsa:2048 -days 365 -nodes -out ./certificate.crt -keyout ./certificate.key

cat certificate.crt certificate.key > certificate.pem
