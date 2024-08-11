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

- isStarted()
- getStatus()
- getPort()
- getIP()

## Functions descriptions

### start

call init and starting server

no returning

### stop

join all threads and close socket

no returning

### init

It initing Server to start

Creating socket and bind that.

return 0 if success,
or return -1 if not success

### servProccess

Create threads for clients

no returning

### cltProccess

proccess of work with clients, use other functions

no returning

### servAccept

Accept client connection

return 0 if succes and -1 if unsuccess

### cltDo

action proccess

return 0 if succes and 1 if connection shold will close

### ServSend && ServRecv

technical functions for send/recv data

based on functions send/recv

return 0 if succcess or -1 if unsuccess

### recvHead

functions for easy recv Protocol::Head

based on ServRecv

return 0 if succcess or -1 if unsuccess

### recvMiddle

functions for easy recv Protocol::Middle

based on ServRecv

return 0 if succcess or -1 if unsuccess

### sendSuccess

functions for easy send success Protocol::End

based on ServSend

return 0 if succcess or -1 if unsuccess

### sendFail

functions for easy send unsuccess Protocol::End

based on ServSend

return 0 if succcess or -1 if unsuccess

### chekConnection()

after action proccess if client want to cheak connection, call in cltDo()

return 0 if succcess or -1 if unsuccess

### endSesion

after action proccess if client want to close sesion, call in cltDo()

return 0 if succcess or -1 if unsuccess

### recvMsg()

after action proccess if client want to send message, call in cltDo()

return 0 if succcess or -1 if unsuccess
