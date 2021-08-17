CC=gcc

run: damas clean
	./damas 

damas: src/main.o src/jogador.o src/menu.o
	$(CC) src/main.c src/jogador.c src/menu.c -o damas

clean: src/main.o src/jogador.o src/menu.o
	rm src/*.o