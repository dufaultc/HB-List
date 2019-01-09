assn3: list.o main.o assignment3.h
	gcc -o assn3 list.o main.o assignment3.h
list.o: list.c assignment3.h
	gcc -c list.c assignment3.h
main.o: main.c assignment3.h
	gcc -c main.c assignment3.h
clean:
	rm assn3 *.o
