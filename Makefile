CC := gcc
C_FLAGS := -g -Wall -Wextra

SRC_D := ./src
OBJ_D := ./obj
BIN_D := ./bin

all: 	clean \
			io.o io_test.o \
			player.o player_test.o board.o board_test.o \
			main.o main

#------------------------------
# RELEASE
#------------------------------

release: C_FLAGS := -std=c99 -O2 -g -DNDDEBUG -Wall -Wextra
release: 	clean \
			io.o io_test.o \
			player.o player_test.o board.o board_test.o \
			main.o main

#------------------------------
# MAIN
#------------------------------

main.o:
	$(CC) $(C_FLAGS) -c -o $(OBJ_D)/$@ $(SRC_D)/main.c;

main: io.o player.o board.o main.o
	$(CC) $(C_FLAGS) -o $(BIN_D)/$@ $(OBJ_D)/io.o $(OBJ_D)/player.o $(OBJ_D)/board.o $(OBJ_D)/main.o;


#------------------------------
# MODELS
#------------------------------

MODELS_D := $(SRC_D)/models

player.o: io.o
	$(CC) $(C_FLAGS) -c -o $(OBJ_D)/$@ $(MODELS_D)/player.c;

player_test.o: io.o player.o;
	$(CC) $(C_FLAGS) -c -o $(OBJ_D)/$@ $(MODELS_D)/player_test.c;

board.o: io.o
	$(CC) $(C_FLAGS) -c -o $(OBJ_D)/$@ $(MODELS_D)/board.c;

board_test.o: io.o board.o;
	$(CC) $(C_FLAGS) -c -o $(OBJ_D)/$@ $(MODELS_D)/board_test.c;

#------------------------------
# UTILS
#------------------------------

UTILS_D := $(SRC_D)/utils

io.o:
	$(CC) $(C_FLAGS) -c -o $(OBJ_D)/$@ $(UTILS_D)/io.c;

io_test.o: io.o;
	$(CC) $(C_FLAGS) -c -o $(OBJ_D)/$@ $(UTILS_D)/io_test.c;

#------------------------------
# MISC
#------------------------------

clean:
	rm -f $(OBJ_D)/* $(BIN_D)/*;
