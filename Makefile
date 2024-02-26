# Set these two values for downloading the latest sfml library archive
SFMLROOTDIR=./lib
# The parent directory for keeping the extracted library. This value is a part of the url itself
SFMLVER=SFML-2.6.1
# The current version of SFML
SFMLLINK=https://www.sfml-dev.org/files/$(SFMLVER)-linux-gcc-64-bit.tar.gz
# The compiler to use
CC=clang++


# The following are set automatically. You are free to set them on your own if you really want to
BEAR=.bear-config.json
COMP=compile_commands.json
TIDY=.clang-tidy
TFLAGS=--checks=modern*,performance*,read*
FORM=.clang-format
BNF=./bin
DEBUG_EXE=./bin/debug.exe
FINAL_EXE=./bin/program.exe
SRC=./src/*.c* ./src/*/*.c*
HPP=./src/*/*.h*
SFMLPATH=$(SFMLROOTDIR)/$(SFMLVER)
SFMLFILE=$(SFMLPATH)/include/SFML/Config.hpp
LIBDIR=$(SFMLPATH)/lib
INCDIR=$(SFMLPATH)/include
LIBFLAGS=-I$(INCDIR) -L$(LIBDIR) -lsfml-system -lsfml-graphics -lsfml-window
DLNAME=$(SFMLROOTDIR)/sfml-lib.tar.gz
DBG_BUILD_CMD=$(CC) $(WFLAGS) -g -o $(DEBUG_EXE) $(SRC) $(LIBFLAGS)

.PHONY:clean format build debug-build run

WFLAGS=-Wall -Wextra -pedantic -std=c++20

$(FINAL_EXE):$(SRC) $(HPP) $(BNF) $(SFMLFILE)
	$(CC) $(WFLAGS) -O3 -o $(FINAL_EXE) $(SRC) $(LIBFLAGS)

$(DEBUG_EXE):$(SRC) $(HPP) $(BNF) $(SFMLFILE)
	$(DBG_BUILD_CMD)

$(BNF):
	mkdir $(BNF)

$(FORM):
	clang-format --dump-config > $(FORM)

$(BEAR): 
	mkdir -p $(BNF) && echo '{"compilation": null,"output": {"content":{"include_only_existing_source": true,"duplicate_filter_fields": "file"},"format": {"command_as_array": true,"drop_output_field": false}}}' > $(BEAR)

$(COMP): $(BEAR)
	bear --config $(BEAR) -- $(DBG_BUILD_CMD)

$(TIDY):
	clang-tidy --checks='$(TFLAGS)' --dump-config > $(TIDY)

clean:
	rm -f ./bin/*.exe $(DLNAME)

format: $(FORM) $(SRC) $(HPP)
	clang-format -i $(SRC) $(HPP)

tidy: $(COMP) $(TIDY) $(SRC)
	clang-tidy --config-file=$(TIDY) $(SRC) $(HPP)

flush-tidy:
	rm -f .clang-tidy compile_commands.json

debug:$(DEBUG_EXE)

build:$(FINAL_EXE)

run:$(FINAL_EXE)
	LD_LIBRARY_PATH=$(LIBDIR) $(FINAL_EXE)

$(DLNAME):
	mkdir -p $(SFMLROOTDIR) && wget -O $(DLNAME) $(SFMLLINK)

$(SFMLFILE): 
	if [ -d "$(SFMLPATH)" ] && [ -f "$(SFMLFILE)" ]; then \
		echo "Library linked successfully."; \
	else \
		echo "Now downloading library" && \
		mkdir -p $(SFMLROOTDIR) && \
		wget -O $(DLNAME) $(SFMLLINK) && \
		tar -xf $(DLNAME) -C $(SFMLROOTDIR); \
	fi
