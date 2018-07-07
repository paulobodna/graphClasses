zipname := 9790944
ifdef name
	zipname = $(name)
endif
all: compile

compile:
	@gcc -o main main.c int_arr.c tuple.c heap.c grafo-matriz.c -I./include -std=c99 -Wall

run:
	@./main

zip:
	@zip -r $(zipname).zip *
	@echo sucess
