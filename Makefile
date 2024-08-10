CC := gcc
C_FLAGS := -g -Wall -Wextra

APP_DIR := ./src/app
TEST_DIR := ./src/test
OBJ_DIR := ./obj
BIN_DIR := ./bin

#------------------------------
# APP
#------------------------------

APP_DIRS = ./src/app/models ./src/app/utils
APP_SRCS = $(foreach dir, $(APP_DIRS), $(wildcard $(dir)/*.c))
APP_OBJS := $(patsubst %.c, %.o, $(APP_SRCS))

$(APP_SRCS):
	$(CC) $(C_FLAGS) -c -o $(patsubst %.c, %.o, $@) $@;

main.o: $(APP_OBJS);
	$(CC) $(C_FLAGS) -c -o $(APP_DIR)/main.o src/app/main.c;

app: main.o $(APP_OBJS);
	$(CC) $(C_FLAGS) -o $(BIN_DIR)/$@ $(APP_DIR)/main.o $(APP_OBJS);


#------------------------------
# TESTS
#------------------------------

TEST_DIR := ./src/test
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst %.c, %.o, $(TEST_SRCS))

$(TEST_SRCS):
	$(CC) $(C_FLAGS) -c -o $(patsubst %.c, %.o, $@) $@;

test: $(APP_OBJS) $(TEST_OBJS);
	$(CC) $(C_FLAGS) -lcriterion -o $(BIN_DIR)/$@ $(APP_OBJS) $(TEST_OBJS);


#------------------------------
# RELEASE
#------------------------------

release: C_FLAGS := -std=c99 -O2 -g -DNDDEBUG -Wall -Wextra
release: 	clean app test;


all: clean app test;

clean:
	rm -f $(APP_DIR)/main.o $(APP_OBJS) $(TEST_OBJS) $(BIN_DIR)/*;
