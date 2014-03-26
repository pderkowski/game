CPP=g++

SRC_DIR=src
EXE_DIR=bin
LIB_DIR=lib
EXE_NAME=robowars

INCLUDE_DIRS=$(shell find . -path '*/include' -type d)
CPPFLAGS=$(foreach dir, $(INCLUDE_DIRS), -I$(dir)) -std=c++11 -MD -MP
WARNINGS=-Wall -Wextra -pedantic -Wshadow

LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS=-Wl,-R$(shell pwd)/$(LIB_DIR)

SRCS=$(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

DEPS=$(shell find . -type f -name '*.d')

MKDIR_P=mkdir -p
RM=rm -rf

.PHONY: all clean distclean

all: mkdir exe

exe: $(OBJS)
	$(CPP) -o $(EXE_DIR)/$(EXE_NAME) $? -L$(LIB_DIR) $(LDLIBS) $(LDFLAGS)

mkdir: $(EXE_DIR)

clean:
	$(RM) $(OBJS) $(DEPS)

distclean: clean
	$(RM) $(EXE_DIR)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(WARNINGS) -c $< -o $@

$(EXE_DIR):
	$(MKDIR_P) $(EXE_DIR)

-include $(DEPS)
