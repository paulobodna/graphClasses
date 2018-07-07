zipname := 9790944
ifdef name
	zipname = $(name)
endif
all: clean compile run

compile: #elevador.o main.o
	@g++ -o main graph.c #main.o elevador.o

#main.o: main.cpp elevador.hpp
#	@g++ -c main.cpp

#elevador.o: elevador.cpp
#	@g++ -c elevador.cpp

cmpg: clean
	@g++ -o main *.cpp -g -Wall

clean:
	@rm *.o *.zip main -f

run: main
	@./main

debug: clean cmpg
	@valgrind -v --track-origins=yes --leak-check=full ./main

zip:
	@zip -r $(zipname).zip *
	@echo sucess
