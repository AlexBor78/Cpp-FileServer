# Server.cpp and Server.h doc

## Functions

### Private

- init()
- servProccess()
<br><br>
- cltProccess()
- servAccept()
- cltDo()
<br><br>
- ServSend()
- ServRecv()
<br><br>
- recvHead()
- recvMiddle()
<br><br>
- sendSuccess()
- sendFail()
<br><br>
- endSesion()
- chekConnection()
- recvMsg()

### Public

- start()
- stop()
<br><br>
- isStarted()
- getStatus()
- getPort()
- getIP()

## Functions descriptions

### start

Call init and starting server.

Not returning.

### stop

Join all threads and close all connections and socket.

Not returning.

### init

Technical function, that initing Server to start,
Creating socket and bind that.

Return 0 if success,
or return -1 if not success.

### servProccess

Create threads for clients.

Not returning.

### cltProccess

Proccess of work with clients, use other functions to perform actions.

Not returning.

### servAccept

Call in cltProccess().
Accept client connection,

return 0 if succes and -1 if unsuccess.

### cltDo

Call in cltProccess().
Action proccessing,

return 0 if succes and <strong>1 if connection shold will close.</strong>

### ServSend && ServRecv

Technical functions for send/recv data.

Based on functions send/recv.

Return 0 if succcess or -1 if unsuccess.

### recvHead

Technical function for easy recv Protocol::Head,
based on ServRecv.

Return 0 if succcess or -1 if unsuccess.

### recvMiddle

Technical function for easy recv Protocol::Middle,
based on ServRecv

Return 0 if succcess or -1 if unsuccess.

### sendSuccess

Technical function for easy send success Protocol::End,
based on ServSend

Return 0 if succcess or -1 if unsuccess.

### sendFail

Technical function for easy send unsuccess Protocol::End,
based on ServSend

Return 0 if succcess or -1 if unsuccess

### chekConnection()

Call in cltDo().

Send success Head to test connectoin.

Return 0 if succcess or -1 if unsuccess

### endSesion

Call in cltDo().

Send success Head if success, then start to close.

Return 0 if succcess or -1 if unsuccess

### recvMsg()

Call in cltDo().

Recv message, print to console and return back to client.

Return 0 if succcess or -1 if unsuccess.
