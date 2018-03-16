all: partitioning

partitioning.o: partitioning.cpp partitioning.h
	g++ -w -std=c++11 partitioning.cpp -c 
	

	
partitioning:  partitioning.o 
	g++ partitioning.o -o partitioning -lm




clean:
	rm *.o
