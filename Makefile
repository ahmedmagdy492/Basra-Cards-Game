CC=cc

all:
	$(CC) -o build/basra-game main.c -ggdb -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
prod:
	$(CC) -o build/basra-game main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11	

clear:
	rm -rf build/main core*
