CC=g++
CFlags=-c -Wall
t=tmp/
b=build/
d=data/

s=server
S=ServerMain
c=client
C=ClientMain

f=file
l=logger
buf=buffer
p=protocol

# 	  logger	  protocol    server	client 
lib.o=$(t)$(l).o $(t)$(p).o $(t)$(s).o $(t)$(c).o
# $(t)$(f).o

ALL: server client
	echo compiled success

server: lib ServerMain.o
	$(CC) $(t)$(S).o $(lib.o) -o $(s)
	mv $(s) $(b)$(s)

ServerMain.o:
	$(CC) $(CFlags) src/$(S).cpp
	mv $(S).o $(t)$(S).o

client: lib ClientMain.o 
	$(CC) $(t)$(C).o $(lib.o) -o $(c)
	mv $(c) $(b)$(c)

ClientMain.o:
	$(CC) $(CFlags) src/$(C).cpp
	mv $(C).o $(t)$(C).o

lib:
# logger
	$(CC) $(CFlags) src/$(l).cpp -o $(l).o
	mv $(l).o $(t)$(l).o
# file
# 	$(CC) $(CFlags) src/$(f).cpp -o $(f).o
# 	mv $(f).o $(t)$(f).o
# protocol
	$(CC) $(CFlags) src/$(p).cpp -o $(p).o
	mv $(p).o $(t)$(p).o
# server
	$(CC) $(CFlags) src/$(s).cpp -o $(s).o
	mv $(s).o $(t)$(s).o
# client
	$(CC) $(CFlags) src/$(c).cpp -o $(c).o
	mv $(c).o $(t)$(c).o

clean:
	rm $(t)*
	rm $(b)*
	rm $(dl)*

init:
	mkdir $(b)
	mkdir $(t)
	mkdir $(dl)
