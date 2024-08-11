# How it work

## Server

### Starting server

in Server::init() server create and build socket

then server create thred where listen connectoin

Server::servProccess() start listening client and create thread

### Accept clients connectoin

Server accepting connectoins and work with clients

functions:

1. Server::newClient()
2. Server::acceptNewConnectoin()

one thread per one client

### Head

Server recv Head. In head client send, what he want.

It in Server::

### Doing

After recv Head server do something and send Head

functions:

1. Server::cltDo()
2.
    - Server::chekConnection()
    - Server::recvMsg()
    - Server::endSesion()

### Ending

server send End with operation status

functions:

1. Server::sendSuccess()
2. Server::sendFail()

## Client

When client connected hi send Head(in Protocol::Head.md more).

After server answer client recv End(in Protocol::ENd.md more) with operation status (succes or fail).
