all: partitioning

partitioning.o: partitioning.cpp partitioning.h
	g++ -w -std=c++11 -O3 -D_GLIBCXX_PARALLEL partitioning.cpp -c -g 
	

	
partitioning:  partitioning.o 
	g++ partitioning.o -O3 -D_GLIBCXX_PARALLEL -o partitioning -lm 




clean:
	rm *.o

#-O3 -D_GLIBCXX_PARALLEL