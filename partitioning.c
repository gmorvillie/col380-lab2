#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "partitioning.h"
#include <limits.h>
char filename[]= "input.txt";
int main() {
    int nbNodes = countNLines();
    NODE graph[nbNodes];
    buildGraph(nbNodes, graph);
    
}

void buildGraph( int nbNodes, NODE graph[nbNodes]){
    FILE * file;
    char str[999];
    
    file = fopen( filename, "r");
    if (file) {
        while (fgets(str, INT_MAX, file)!=NULL)
            printf("line : %s", str);
            
        fclose(file);
    }
}
int countNLines(){
    char c;
    FILE *fp;
    fp = fopen(filename, "r");
    int count =0;
    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }
 
    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
 
    // Close the file
    fclose(fp);
    return count;
}
    
