zipname := 9790944
ifdef name
	zipname = $(name)
endif
all: compile

compile: queue.o graph.o main.o
	@gcc graph.o queue.o main.o -o main -g -Wall -march=native -O3 -std=c99 #main.o elevador.o

main.o: main.c
	@gcc -c main.c

graph.o: graph.c
	@gcc -c graph.c

queue.o: queue.c
	@gcc -c queue.c

cmpg: clean
	@gcc -o main *.cpp -g -Wall

clean:
	@rm *.o *.zip main -f

run: main
	@./main

debug: clean cmpg
	@valgrind -v --track-origins=yes --leak-check=full ./main

zip:
	@zip -r $(zipname).zip *
	@echo sucess
