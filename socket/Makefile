.PHONY=all remove info

TARGET=info
all:info makedirs compile

CC=gcc
CLIBS=-lc
CFLAGS= -Wall -ggdb3

PROGRAM_ROOT_DIR=bin
PROGRAM_TEST_DIR=bin/test

HEADER_FILES:=include/
SERVER_FILE1:=TCPServer.c Server.c socket-util.c
SERVER_FILE2:=UDPServer.c Server.c socket-util.c

CLIENT_FILE1:=TCPClient.c socket-util.c
CLIENT_FILE2:=UDPClient.c socket-util.c

SOURCE_FILES=$(shell find src/ -type f -name "*.c")
TEST_FILES=$(shell find test/ -type f -name "*.c")

make_std_color=\033[3$1m

RESET_COLOR=\033[0m
ERROR_COLOR = $(strip $(call make_std_color,1))
INFO_COLOR = $(strip $(call make_std_color,3))
CYAN_COLOR=  $(strip $(call make_std_color,6))

info:
	@ echo "\t\t$(INFO_COLOR)======================"
	@ echo "\t\t  Halil Ibrahim MUT"
	@ echo "\t\t----------------------"
	@ echo "\t\t -*-$(CYAN_COLOR)Server / Client$(INFO_COLOR)-*-"
	@ echo "\t\t $(CYAN_COLOR)Inter-process communication"
	@ echo "\t\t$(INFO_COLOR)======================$(RESET_COLOR)\n"

compile:
	@ echo "$(INFO_COLOR)compiling.."
	@ echo "===Test files===================$(RESET_COLOR)"
	@ for var in $(TEST_FILES); do \
	echo "$(INFO_COLOR)'$$var' compiling..$(RESET_COLOR)"; \
	echo "\t$(CC) $(CFLAGS) $(SOURCE_FILES) $$var -I$(HEADER_FILES) -o "$(PROGRAM_ROOT_DIR)/$$var.out" $(CLIBS) ";\
	$(CC) $(CFLAGS) $(SOURCE_FILES) $$var -I$(HEADER_FILES) -o "$(PROGRAM_ROOT_DIR)/$$var.out" $(CLIBS) ; \
	echo; \
	done
	
	@ echo "\nDone"

remove:
	@echo "$(INFO_COLOR)Removing main Directory.."
	@echo "======================$(RESET_COLOR)"
	rm -rf $(PROGRAM_ROOT_DIR)/
	@echo "\n"
	@echo "Program directory removed."

makedirs:
	@echo "$(INFO_COLOR)making directories.."
	@echo "======================$(RESET_COLOR)"
	@echo "$(PROGRAM_ROOT_DIR) is MAIN DIRECTORY FOR SETUP"
	mkdir -p $(PROGRAM_ROOT_DIR)
	mkdir -p $(PROGRAM_TEST_DIR)
	@echo "\n"
	
