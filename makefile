all: graph.o main.o
	gcc main.o graph.o -o exe

verifica: graph.o main.o
	gcc main.o graph.o -fsanitize=address -o exe

main.o:
	gcc -c main.c -o main.o

graph.o:
	gcc -c graph.c -o graph.o

run:
	./exe

clean:
	rm *.o
	rm exe