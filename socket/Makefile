.PHONY=all remove info makedirs build compile_tests
TARGET=info

all:info makedirs build compile_tests
CC:=gcc
CLIBS:=-lc -ljpeg -pthread

BUILD_DIR:=build
SRC_DIR:=src
TEST_DIR:=test
BIN_DIR=bin

SRCS:=$(shell find $(SRC_DIR)/ -name "*.c" -type f)#to get names of files to be compiled
SRCS:=$(SRCS:src/%=%)#remove prefix "src/" from all texts

OBJS:=$(SRCS:%.c=%.o)#linker objects to store object files compiled
DEPS := $(OBJS:.o=.d)

INC_DIRS:= $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

TEST_EXECS:=$(shell find $(TEST_DIR)/ -name "*.c" -type f)#main entry points of class to test

CFLAGS:= -Wall -ggdb3 $(INC_FLAGS) -MMD -MP
#****************************************
make_std_color=\033[3$1m

RESET_COLOR=\033[0m
ERROR_COLOR = $(strip $(call make_std_color,1))
INFO_COLOR = $(strip $(call make_std_color,3))
CYAN_COLOR=  $(strip $(call make_std_color,6))
#****************************************

# Build step for linux executable of tests
compile_tests: makedirs build
	@ for var in $(TEST_EXECS); do \
		echo "$(CYAN_COLOR)\tCompile test executable:$(RESET_COLOR) '$$var'"; \
		mkdir -p $(BIN_DIR)/$$var; \
		$(CC) $(CFLAGS) $(addprefix $(BUILD_DIR)/, $(OBJS)) $$var -o $(BIN_DIR)/$$var.out $(CLIBS) ||break; \
		echo; \
	done


# Build step for C source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	
	@echo "$(INFO_COLOR)Compile linker object: $@"
	@echo "====================================$(RESET_COLOR)"
	mkdir -p $(dir $@)

	$(CC) $(CFLAGS) -c $< -o $@
	@echo

#build step: require headers to source files

build: $(addprefix $(BUILD_DIR)/, $(OBJS))

info:
	@ echo "\t\t$(INFO_COLOR)======================"
	@ echo "\t\t  Halil Ibrahim MUT"
	@ echo "\t\t----------------------"
	@ echo "\t\t -*-$(CYAN_COLOR)Server / Client$(INFO_COLOR)-*-"
	@ echo "\t\t $(CYAN_COLOR)Inter-process communication"
	@ echo "\t\t$(INFO_COLOR)======================$(RESET_COLOR)\n"

remove:
	@echo "$(INFO_COLOR)Removing main Directory and linker objects.."
	@echo "======================$(RESET_COLOR)"
	rm -rf $(BIN_DIR) $(BUILD_DIR)
	@echo "\n"
	@echo "Program directory removed."

makedirs:
	@echo "$(INFO_COLOR)making directories.."
	@echo "======================$(RESET_COLOR)"
	@echo "$(BIN_DIR) is MAIN DIRECTORY FOR SETUP"
	mkdir -p $(BIN_DIR)/$(TEST_DIR) $(TEST_DIR) $(BUILD_DIR)
	@echo "\n"
	
print:
	@echo "source names"
	@echo $(SRCS)
	@echo "\nobject destinations"
	@echo $(OBJS)
	@echo "\ninclude destinations"
	@echo $(INC_FLAGS)
	@echo "\ntest executables"
	@echo $(TEST_EXECS)


-include $(DEPS)