CC := gcc
C_FLAGS := -g -Wall -Wextra

LIBS_DIR := ./src/libs
APP_DIR := ./src/app
TEST_DIR := ./src/test
OBJ_DIR := ./obj
BIN_DIR := ./bin

all: clean app test;

clean:
	rm -f $(APP_DIR)/main.o $(APP_OBJS) $(TEST_OBJS) $(OBJ_DIR)/* $(BIN_DIR)/*;

#------------------------------
# APP
#------------------------------

APP_DIRS := ./src/app/models ./src/app/utils
APP_SRCS := $(foreach dir, $(APP_DIRS), $(wildcard $(dir)/*.c))
APP_OBJS := $(patsubst %.c, %.o, $(APP_SRCS))

$(APP_SRCS):
	$(CC) $(C_FLAGS) -c -o $(patsubst %.c, %.o, $@) $@;

main.o: $(APP_OBJS);
	$(CC) $(C_FLAGS) -c -o $(APP_DIR)/main.o ./src/app/main.c;

app: main.o $(APP_OBJS);
	$(CC) $(C_FLAGS) -o $(BIN_DIR)/$@ $(APP_DIR)/main.o $(APP_OBJS) -L$(LIBS_DIR) -lc_structs;


#------------------------------
# TESTS
#------------------------------

TEST_DIR := src/test
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst %.c, %.o, $(TEST_SRCS))

$(TEST_SRCS):
	$(CC) $(C_FLAGS) -c -o $(patsubst %.c, %.o, $@) $@;

test: $(APP_OBJS) $(TEST_OBJS);
	$(CC) $(C_FLAGS) -o $(BIN_DIR)/$@ $(APP_OBJS) $(TEST_OBJS) -L$(LIBS_DIR) -lc_structs -lcriterion;


#------------------------------
# RELEASE
#------------------------------

release: C_FLAGS := -std=c99 -O2 -g -DNDDEBUG -Wall -Wextra
release: 	clean app test;
