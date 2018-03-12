all: partitioning

partitioning.o: partitioning.c partitioning.h
	gcc -Wall partitioning.c -c
	

	
partitioning:  partitioning.o 
	gcc partitioning.o -o partitioning -lm




clean:
	rm *.o
