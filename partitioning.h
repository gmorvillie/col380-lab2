#include <stdio.h>

/*****************\
     Structures
\*****************/

struct node  {
    struct node *adjacent;
    struct node *next;
};

typedef  struct node NODE;
typedef  NODE * LIST;

void buildGraph(int , NODE []);
int countNLines();




