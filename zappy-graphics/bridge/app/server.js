const { WebTCP } = require('../vendor/webtcp/webtcp')

const server = new WebTCP();
server.listen(9999, "127.0.0.1");
