#include "partitioning.h"
#include <string>
#include <algorithm>
#include <random>



void string_to_array(vector<int> &v, string s)
{
    int num=0; 
    for( uint i=0;i< s.size();i++)
    {
        if(s[i]==' ')
        {
            v.push_back(num);
            num=0;
        }
        else
        {
            num = num*10+(int)(s[i]-48);            
        }

    }
    v.push_back(num);

}


void randomMatch( graph source, vector < pair<int, int> > matching){
    int nbMtch = 2;
    
    for( int i3 = 0; i3<nbMtch; i3++){        // the number of matching that are calculated can vary. How to choose it ?
        int tempSize;
        matching.clear();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(source.vtx), std::end(source.vtx), rng);
        vector <vertex>::iterator i1;
     
        for (i1=source.vtx.begin();i1!=source.vtx.end();++i1)
        {   // randomly iterates over the vertices
            if(!i1->match){
                
                //  TODO-select random non matched neighbour
                //  Problem : only the id of neighbour is stored. //  possible to store the vertex ?
            }
        }
        if(tempSize<matching.size()) 
            tempSize=matching.size();
    }
}

void coarse(graph source, vector < pair<int, int> > matching){
    
}
    


void buildGraph( graph &init_graph ){
    
    string str;      //string to read data 
    vector<int> v;  //vector to store parsed numbers

    ifstream myfile ("input.txt");
    getline(myfile, str);
    string_to_array(v,str);
    // cout<<v.size();

    init_graph.num_nodes=v[0];
    init_graph.num_edges=v[1];
    init_graph.edges.resize(init_graph.num_nodes); //update edges 

    int id =1;
    if (myfile) {
        while (getline(myfile, str))
        {
            v.clear();
            string_to_array(v, str); 
            vertex temp;
            temp.init(v.size(), false, id, v);
            init_graph.vtx.push_back(temp);
            id++;
        }
    }

}

int main() {

vector < pair<int, int> > matching;
graph init_graph;
buildGraph (init_graph) ;

randomMatch( init_graph, matching);
//init_graph.print_graph();
}

// int countNLines(){
//     char c;
//     FILE *fp;
//     fp = fopen(filename, "r");
//     int count =0;
//     // Check if file exists
//     if (fp == NULL)
//     {
//         printf("Could not open file %s", filename);
//         return 0;
//     }
 
//     // Extract characters from file and store in character c
//     for (c = getc(fp); c != EOF; c = getc(fp))
//         if (c == '\n') // Increment count if this character is newline
//             count = count + 1;
 
//     // Close the file
//     fclose(fp);
//     return count;
// }
    
