CC=cc

all:
	$(CC) -o build/cards main.c -ggdb -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
prod:
	

clear:
	rm -rf build/main core*
