CC=gcc

run: damas clean
	./damas 

damas: src/main.o src/jogador.o src/jogo.o src/menu.o 
	$(CC) src/main.c src/jogador.c src/jogo.o src/menu.c -lm -o damas

clean: src/main.o src/jogador.o src/jogo.o src/menu.o 
	rm src/*.o