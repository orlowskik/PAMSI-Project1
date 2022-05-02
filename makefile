program: main.o structures.o
	g++ -o main.out structures.o  main.o 

main.o: main.cpp structures.h
	g++ -c -o main.o main.cpp

structures.o: structures.cpp structures.h
	g++ -c -o structures.o structures.cpp

.PHONY: clean

clean:
	rm -f *.o
