CC = g++
CFLAGS = -std=c++11
TARGET = scanner
OBJS = main.o Scanner.o FileManager.o TestScanner.o
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
TestScanner.o: TestScanner.cpp
	$(CC) $(CFLAGS) -c TestScanner.cpp
Scanner.o: Scanner.cpp
	$(CC) $(CFLAGS) -c Scanner.cpp
FileManager.o: FileManager.cpp
	$(CC) $(CFLAGS) -c FileManager.cpp
clean:
	/bin/rm -f *.o
clean_all:
	/bin/rm -f *.o $(TARGET)

