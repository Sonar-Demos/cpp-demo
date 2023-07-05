CCFLAGS := --coverage -std=c++17
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	JSON_C_PATH := /opt/homebrew/opt/json-c
	JSON_C_INCLUDE := -I$(JSON_C_PATH)/include
	JSON_C_LIB := -L$(JSON_C_PATH)/lib
	PTHREAD_LIB :=
else
	JSON_C_INCLUDE =
	JSON_C_LIB :=
	PTHREAD_LIB := -lpthread
endif

all: server

build:
	mkdir build

server: build
	c++ \
		./src/Server/serverReadsProfiler.cpp \
		-o "build/server" \
	  	$(CCFLAGS) \
		-I./src/Server \
		$(JSON_C_INCLUDE) \
		$(JSON_C_LIB) \
		$(PTHREAD_LIB) \
		-ljson-c
