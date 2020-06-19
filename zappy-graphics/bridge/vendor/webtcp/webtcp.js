// WebTCP server to which browsers are connecting.

// Creates SockJS server, receives messages from a browser
// and triggers corresponding actions 

// Check out example in examples/server.js

var http = require('http');
var sockjs = require('sockjs');
var Socket = require('./socket.js').Socket;

module.exports.WebTCP = function() {
  this.sockjsServer = sockjs.createServer();
  this.sockjsConn = null;
  this.websockets = {};
  this.httpClients = {};

  var self = this;

  this.sockjsServer.on('connection', function(conn) {
    self.sockjsConn = conn;
    conn.on('data', function(message) {
      self.dispatch(conn, message);
    });
  });

  // client's message processor
  this.dispatch = function(conn, message) {
    message = JSON.parse(message);
    // create socket binding if it doesn't exist
    if (!this.websockets[message.sID]) 
      this.websockets[message.sID] = new Socket(this, message.sID, message.host, message.port, message.options);
    this.websockets[message.sID].onClientData(message);
  }

  this.listen = function(port, host) {
    this.server = http.createServer();
    this.sockjsServer.installHandlers(this.server, { prefix: '/bridge' });
    this.server.listen(port, host);
  }
}