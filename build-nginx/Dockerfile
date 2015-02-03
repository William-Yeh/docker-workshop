# a naive Nginx image

FROM ubuntu:14.04

# copy to image/container
COPY nginx-full_1.6.2-5+trusty0_amd64.deb nginx.deb

# install from deb
RUN dpkg -i nginx.deb

# start Nginx server
CMD [ "nginx" ]

#CMD ["nginx", "-g", "daemon off;"]
