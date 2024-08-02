CC=g++
CFlags=-c -Wall
t=tmp/
b=builded/

S=server
SM=ServerMain
C=client
CM=ClientMain

ALL: server

server: server.o ServerMain.o
	$(CC) $(t)$(S).o $(t)$(SM).o -o server
	mv server $(b)server

server.o:
	$(CC) $(CFlags) src/$(S).cpp
	mv $(S).o $(t)$(S).o

ServerMain.o:
	$(CC) $(CFlags) src/$(SM).cpp
	mv $(SM).o $(t)$(SM).o