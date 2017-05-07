 var express = require("express");
 var http = require('http').Server(express);
 var io = require('socket.io')(http);
 var net = require('net');
 var app = express();

var p = 0;
var q = 0;
 /* serves main page */
 app.get("/", function(req, res) {
 	p = req.query.p;
 	q = req.query.q;
 	console.log(req.query.q + " " + req.query.p);
 	// client.write('Hello');
 	//io.emit('data', 'res');
 	//console.log("passed");
    res.sendfile('new.html')	
 });

  app.post("/user/add", function(req, res) { 
	/* some server side logic */
	// res.send("OK");
	console.log(req.body);
  });

  app.get("/datafeed",function(req, res) {
  	res.setHeader('Content-Type', 'application/json');
    res.send(JSON.stringify({ well: q, tank: p }));
  });

io.on('connection', function(socket){
  console.log('User connected');
  socket.on('message', function(msg){
    console.log('message: ' + msg);
    // client.write('Hello');
  });

});
 /* serves all the static files */
 // app.get(/^(.+)$/, function(req, res){ 
 //     console.log('static file request : ' + req.params);=
 //     res.sendfile( __dirname + req.params[0]); 
 //     console.log(req);
 // });

 var port = process.env.PORT || 5000;
 app.listen(port, function() {
   console.log("Listening on " + port);
 });

// var client = new net.Socket();
// client.connect(5000, '127.0.0.1', function() {
//   console.log('Connected');
//   // client.write('Hello, server! Love, Client.\n');
// });