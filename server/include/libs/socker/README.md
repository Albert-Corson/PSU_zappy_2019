# Socker library

The **socker** library is a set of server core utilities and setup functions. It 
is a state machine: it must be bound values it will use internally until 
unbound. It offers an important layer of abstraction above sockets, event 
queues and message queues with the capability to add plugins (such as a server 
and connection queue abstraction, an API router, ...).
