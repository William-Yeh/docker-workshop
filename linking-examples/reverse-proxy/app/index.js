// A simple web server that generates dyanmic content based on responses from Redis
//
// Adapted from: https://github.com/mranney/node_redis/blob/master/examples/web_server.js
//

var http = require('http'),
    ip = require("ip");

var PORT       = process.env.PORT       || 3000        ;
var REDIS_HOST = process.env.REDIS_HOST || '127.0.0.1' ;
var REDIS_PORT = process.env.REDIS_PORT || 6379        ;


function get_remote_ip(req) {
    var ip_address = null;
    try {
        ip_address = req.headers['x-forwarded-for'];
    }
    catch (err) {
        ip_address = req.connection.remoteAddress;
    }
    return ip_address;
}


function report_health(resp) {
    resp.writeHead(200, {
        "Content-Type": "text/plain"
    });
    resp.write("OK");
    resp.end();
}


var redis_client = require('redis').createClient(REDIS_PORT, REDIS_HOST);
var server = http.createServer(function(request, response) {

    console.log(request.url);

    // skip uninteresting URL requests
    if (request.url === '/favicon.ico') {
        return;
    }
    else if (request.url === '/health') {
        report_health(response);
        return;
    }


    response.writeHead(200, {
        "Content-Type": "text/plain"
    });

    var total_requests;

    redis_client.incr("requests", function(err, reply) {
        total_requests = reply; // stash response in outer scope
    });

    redis_client.hincrby("ip", get_remote_ip(request), 1);
    redis_client.hgetall("ip", function(err, reply) {
        // This is the last reply, so all of the previous replies must have completed already
        response.write(
            "Total requests: " + total_requests + "\n\n" +
            "My IP: " + ip.address() + "\n\n" +
            "Remote IP count: \n");
        Object.keys(reply).forEach(function(ip) {
            response.write("    " + ip + ": " + reply[ip] + "\n");
        });
        response.end();
    });

}).listen(PORT);

console.log('Server listening on port', PORT);
