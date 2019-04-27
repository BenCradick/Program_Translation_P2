CC = g++
CFLAGS = -std=c++11
TARGET = parser
OBJS = main.o Scanner.o FileManager.o Parser.o testTree.o
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
testTree.o: testTree.cpp
	$(CC) $(CFLAGS) -c testTree.cpp
Scanner.o: Scanner.cpp
	$(CC) $(CFLAGS) -c Scanner.cpp
FileManager.o: FileManager.cpp
	$(CC) $(CFLAGS) -c FileManager.cpp
Parser.o: Parser.cpp
	$(CC) $(CFLAGS) -c Parser.cpp
clean:
	/bin/rm -f *.o
clean_all:
	/bin/rm -f *.o $(TARGET)

