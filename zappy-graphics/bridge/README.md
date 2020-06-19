# TCP socket bridge

This application establishes a bridge connection between a browser client and 
a TCP server. Browser is connected through the use of websockets (via webtcp 
library).
The use of a bridge is necessary because of browser sandboxes: a browser 
application is not allowed to establish socket connections other than 
websockets (communicating with the http protocol). To communicate with a 
non-http server, http requests must be intercepted by the bridge and their 
raw data transmitted to the target server.

In the scope of the Zappy project, the bridge is used by the web-based 
graphical client to retrieve data from Zappy server.
