# a naive image for Node.js + mcrypt

FROM node:0.10.36-slim

RUN     mkdir -p /opt/node_modules
WORKDIR /opt

# copy to image/container
COPY libmcrypt4_2.5.8-3.3_amd64.deb    libmcrypt4.deb
COPY libmcrypt-dev_2.5.8-3.3_amd64.deb libmcrypt-dev.deb

# install from deb
RUN dpkg -i libmcrypt4.deb libmcrypt-dev.deb

# copy pre-installed Node.js modules
COPY node_modules /opt/node_modules/
#COPY package.json /opt/
#RUN npm install

# run!
ENTRYPOINT ["node"]
