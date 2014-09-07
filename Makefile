CPP=g++

SRC_DIR=src
EXE_DIR=bin
LIB_DIR=lib
EXE_NAME=game

INCLUDE_DIRS=$(shell find . -path '*/include' -or -path '*/src' -type d)
CPPFLAGS=$(foreach dir, $(INCLUDE_DIRS), -I$(dir) -isystem $(dir)) -std=c++11 -MD -MP
WARNINGS=-Wall -Wextra -pedantic -Werror

SFML_LIBS=-lsfml-graphics -lsfml-window -lsfml-system
BOOST_LIBS=-lboost_filesystem -lboost_system
OTHER_LIBS=-lnoise
LDLIBS=$(SFML_LIBS) $(BOOST_LIBS) $(OTHER_LIBS)
LDFLAGS=-Wl,-rpath=$(shell pwd)/$(LIB_DIR)

SRCS=$(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

DEPS=$(shell find . -type f -name '*.d')

MKDIR_P=mkdir -p
RM=rm -rf

.PHONY: all clean distclean

all: mkdir exe

exe: $(OBJS)
	$(CPP) -o $(EXE_DIR)/$(EXE_NAME) $? -L$(LIB_DIR) $(LDLIBS) $(LDFLAGS)

debug: CPPFLAGS += -DDEBUG -g
debug: exe

mkdir: $(EXE_DIR)

clean:
	$(RM) $(OBJS) $(DEPS)

distclean: clean
	$(RM) $(EXE_DIR) core

run: mkdir exe
	./$(EXE_DIR)/$(EXE_NAME)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(WARNINGS) -c $< -o $@

$(EXE_DIR):
	$(MKDIR_P) $(EXE_DIR)

-include $(DEPS)
