
CXX = g++

all: main

main: build/main.o build/file_handling.o build/const.o
	$(CXX) -o main build/main.o build/file_handling.o build/const.o

build/main.o: src/main.cpp
	$(CXX) -c src/main.cpp -o build/main.o

build/file_handling.o: src/file_handling.cpp
	$(CXX) -c src/file_handling.cpp -o build/file_handling.o

build/const.o: src/const.cpp
	$(CXX) -c src/const.cpp -o build/const.o

.PHONY: clean

clean:
	rm -f build/*.o main
	# del /q /f src\*.o src\main.exe