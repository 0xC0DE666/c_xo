default:
	rm -f ./bin/*;
	gcc ./src/main.c ./src/utils/io.c ./src/models/player.c ./src/models/board.c -o ./bin/app;
	gcc ./src/utils/io.c ./src/utils/io.test.c ./src/models/player.c ./src/models/player.test.c ./src/models/board.c ./src/models/board.test.c -lcriterion -o ./bin/test;

build-app:
	gcc ./src/main.c ./src/io.c -o ./bin/app;

build-test:
	gcc ./src/io.c ./src/io_test.c -lcriterion -o ./bin/test;

clean:
	rm -f ./bin/*;
