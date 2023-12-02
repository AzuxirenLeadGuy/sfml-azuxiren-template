DEBUG_EXE=./bin/debug.exe
FINAL_EXE=./bin/program.exe
SRC=./src/*.c* ./src/core/*.c* ./src/scene/*.c*
HPP=./src/core/*.h* ./src/scene/*.h*
LIB=-lsfml-system -lsfml-graphics -lsfml-window -pthreads

.PHONY: build debug-build clean run

WFLAGS=-Wall -Wextra -pedantic -std=c++20

$(FINAL_EXE):$(SRC) $(HPP)
	clang++ $(WFLAGS) -O3 -o $(FINAL_EXE) $(SRC) $(LIB)

$(DEBUG_EXE):$(SRC) $(HPP)
	clang++ $(WFLAGS) -g -o $(DEBUG_EXE) $(SRC) $(LIB)

clean:
	rm -f ./bin/*.exe

build:$(FINAL_EXE)

debug:$(DEBUG_EXE)

run:$(FINAL_EXE)
	$(FINAL_EXE)