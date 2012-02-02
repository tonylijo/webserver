CC := g++
RM := rm
OBJ := www
LINK := -lrt
server: socket.o server.cc
	$(CC) server.cc socket.o $(LINK) -o $(OBJ)
socket.o: socket.cc
	$(CC) -c socket.cc
clean: 
	$(RM) *.o www
