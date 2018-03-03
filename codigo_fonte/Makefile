FLAGS = -std=c99 -Wall
PROGRAMA = Projeto1IA

all: $(PROGRAMA)

$(PROGRAMA): main.o busca.o tad.o
	@gcc $(FLAGS) -o bin/$(PROGRAMA) main.o busca.o tad.o
	@rm -rf *.o

main.o: src/main.c src/busca.h src/tad.h
	@gcc $(FLAGS) -c src/main.c

busca.o: src/busca.c src/busca.h
	@gcc $(FLAGS) -c src/busca.c

tad.o: src/tad.c src/tad.h
	@gcc $(FLAGS) -c src/tad.c

clean:
	@rm -rf *.o *~ bin/*

run:
	@./bin/$(PROGRAMA)

