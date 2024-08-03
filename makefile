CC=g++
CFlags=-c -Wall
t=tmp/
b=build/

s=server
S=ServerMain
c=client
C=ClientMain
d=data
f=file
lib.o=$(t)$(s).o $(t)$(c).o $(t)$(d).o $(t)$(f).o

ALL: server client

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
	$(CC) $(CFlags) src/$(s).cpp -o $(s).o
	$(CC) $(CFlags) src/$(c).cpp -o $(c).o
	$(CC) $(CFlags) src/$(d).cpp -o $(d).o
	$(CC) $(CFlags) src/$(f).cpp -o $(f).o
	mv $(s).o $(t)$(s).o
	mv $(c).o $(t)$(c).o
	mv $(d).o $(t)$(d).o
	mv $(f).o $(t)$(f).o

clean:
	rm $(t)*
	rm $(b)*
