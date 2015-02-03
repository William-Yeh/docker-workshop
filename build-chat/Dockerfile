FROM node:0.10.36-slim

RUN     mkdir -p /app
WORKDIR /app

COPY  package.json  /app/
RUN   npm install --production
COPY  .  /app

EXPOSE 3000
CMD [ "npm", "start" ]
