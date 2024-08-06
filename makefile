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
e=error
buf=buffer
p=protocol
lib.o=$(t)$(s).o $(t)$(c).o 
# $(t)$(p).o
# $(t)$(d).o  
# $(t)$(buf).o
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
#	$(CC) $(CFlags) src/$(p).cpp -o $(p).o
#	mv $(p).o $(t)$(p).o
	$(CC) $(CFlags) src/$(s).cpp -o $(s).o
	mv $(s).o $(t)$(s).o
	$(CC) $(CFlags) src/$(c).cpp -o $(c).o
	mv $(c).o $(t)$(c).o
#	$(CC) $(CFlags) src/$(buf).cpp -o $(buf).o
#	mv $(buf).o $(t)$(buf).o
#	$(CC) $(CFlags) src/$(d).cpp -o $(d).o
#	mv $(d).o $(t)$(d).o
# 	$(CC) $(CFlags) src/$(e).cpp -o $(e).o
# 	mv $(e).o $(t)$(e).o
# 	$(CC) $(CFlags) src/$(f).cpp -o $(f).o
# 	mv $(f).o $(t)$(f).o

clean:
	rm $(t)*
	rm $(b)*
