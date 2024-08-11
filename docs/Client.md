# Server.cpp and Server.h doc

## Functions

### Private

- init()
<br><br>
- cltSend()
- cltRecv()
<br><br>
- sendHead()
- RecvSuccess()
<br><br>
- chekConnection()
- closeConnection()

### Public

- send()
<br><br>
- connect()
- disconnect()
<br><br>
- isCOnnected()

## Functions descriptions

### connect

Call init and connect to server.

Not returning.

### disconnect

call closeConnection and close connect to server.
Not returning.

### init

Technical function for connecting to server.

It creating socket and connect to server.

return 0 if success,
or -1 if unsuccess.

### cltSend() && cltRecv()

Technical functions for send/recv data

Based on functions send/recv

Return 0 if success,
or -1 if unsuccess.

### sendHead

Technical function for easy send Head to server.

Return 0 if success,
or -1 if unsuccess.

### RecvSuccess

Technical function for easy recv success Head from server.

Return 0 if success and recv-ed head has success status,
or -1 if unsucces.

### chekConnection

Technical function for easy test connectoin to server.

Return 0 if success and test of connection to server is success,
or -1 if unsuccess.

### closeConnection

Technical function for easy close connectoin to server.

Return 0 if success,
or -1 if unsuccess.
