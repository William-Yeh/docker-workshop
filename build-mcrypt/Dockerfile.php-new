# a naive PHP + mcrypt image

FROM php:5.6.6-cli

# copy to image/container
COPY libmcrypt4_2.5.8-3.3_amd64.deb    libmcrypt4.deb
COPY libmcrypt-dev_2.5.8-3.3_amd64.deb libmcrypt-dev.deb

# install from deb
RUN dpkg -i libmcrypt4.deb libmcrypt-dev.deb

# install PHP modules
#   ... via a convenient wrapper for "make ; make install" stuff
RUN docker-php-ext-install mcrypt


# start PHP
ENTRYPOINT [ "php" ]