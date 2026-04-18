
CXX = g++

all: main

main: main.o file_handling.o const.o
	$(CXX) -o main main.o file_handling.o const.o

main.o: src/main.cpp
	$(CXX) -c src/main.cpp

file_handling.o: src/file_handling.cpp
	$(CXX) -c src/file_handling.cpp

const.o: src/const.cpp
	$(CXX) -c src/const.cpp

.PHONY: clean

clean:
	del /q /f src\*.o src\main.exe