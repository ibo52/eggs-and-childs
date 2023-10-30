.PHONY=all remove info
	
TARGET=info
all:info makedirs compile

CC=gcc
CLIBS=-lc
CFLAGS= -Wall -ggdb3

PROGRAM_ROOT_DIR=bin

HEADER_FILES:=include/
SERVER_FILE1:=TCPServer.c Server.c socket-util.c
SERVER_FILE2:=UDPServer.c Server.c socket-util.c

CLIENT_FILE1:=TCPClient.c socket-util.c
CLIENT_FILE2:=UDPClient.c socket-util.c

make_std_color=\033[3$1m

RESET_COLOR=\033[0m
ERROR_COLOR = $(strip $(call make_std_color,1))
INFO_COLOR = $(strip $(call make_std_color,3))
CYAN_COLOR=  $(strip $(call make_std_color,6))

info:
	@echo "\t\t$(INFO_COLOR)======================"
	@echo "\t\t  Halil Ibrahim MUT"
	@echo "\t\t----------------------"
	@echo "\t\t -*-$(CYAN_COLOR)Server / Client$(INFO_COLOR)-*-"
	@echo "\t\t $(CYAN_COLOR)Inter-process communication"
	@echo "\t\t$(INFO_COLOR)======================$(RESET_COLOR)\n"

compile:
	@echo "$(INFO_COLOR)compiling.."
	@echo "===Server file===================$(RESET_COLOR)"
	$(CC) $(CFLAGS) $(SERVER_FILE1) -I$(HEADER_FILES) -o "$(PROGRAM_ROOT_DIR)/TCPServer" $(CLIBS)
	$(CC) $(CFLAGS) $(SERVER_FILE2) -I$(HEADER_FILES) -o "$(PROGRAM_ROOT_DIR)/UDPServer" $(CLIBS)
	
	@echo "$(INFO_COLOR)===Client file===================$(RESET_COLOR)"
	$(CC) $(CFLAGS) $(CLIENT_FILE1) -I$(HEADER_FILES) -o "$(PROGRAM_ROOT_DIR)/TCPClient" $(CLIBS)
	$(CC) $(CFLAGS) $(CLIENT_FILE2) -I$(HEADER_FILES) -o "$(PROGRAM_ROOT_DIR)/UDPClient" $(CLIBS)
	@echo "\n"
	
	@echo "Done"

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
	@echo "\n"
	
