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


void randomMatch( graph source, vector <pair<vertex,vertex>> * matching){
    int nbMtch = 1;
    
    for( int i3 = 0; i3<nbMtch; i3++){        // the number of matching that are calculated can vary. How to choose it ?
        int tempSize;
        (*matching).clear();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(source.vtx), std::end(source.vtx), rng);
        vector <vertex>::iterator i1;
     
        for (i1=source.vtx.begin();i1!=source.vtx.end();++i1)
        {   // randomly iterates over the vertices
            
            if(!i1->match){
                
                
                auto randomng = std::default_random_engine {};
                std::shuffle(std::begin(i1->pneighbour), std::end(i1->pneighbour), randomng);
                
                vector <vertex *>::iterator i6;
                
                for (i6=i1->pneighbour.begin();i6!=i1->pneighbour.end();++i6){          //careful, the algo of the paper says pick one random unmatched neighbor. here we are randomly iterating over neighbors to find an unmatched one
                        if(!(*i6)->match){
                            
                            
                            pair<vertex, vertex> match_entry (**i6,  *i1);
                            
                            (*matching).push_back(match_entry);
                            (*i6)->match=true;
                            i1->match=true;
                            break;          //careful for parallel version about break !!!
                            
                            
                        }
                        
                    
                 }
                 
                
            }
        }
        if(tempSize<matching->size()) 
            tempSize=matching->size();
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
    for(int i4 = 0; i4<init_graph.num_nodes;i4++){      // update the pointers to neighbors --> inefficient !
        
        for(int i5 = 0; i5<init_graph.vtx[i4].deg;i5++){
            int n=init_graph.vtx[i4].neighbour[i5];
            
            
            if(n== init_graph.vtx[n-1].id){        //if the ith element has id i --> faster than search for id i
                
                init_graph.vtx[i4].pneighbour.push_back(&init_graph.vtx[n-1]);       //in the list of pointers to neighbours, add the adress of this neighbour
            }
                
        }
    }
}

int main() {

vector < pair<vertex, vertex> > matching;
graph init_graph;
buildGraph (init_graph) ;

randomMatch( init_graph, &matching);
cout<< "matching 1" <<endl;
for(int j =0; j< matching.size(); j++){
    cout<<matching[j].first.id<<" "<<matching[j].second.id<<endl;
}


init_graph.print_graph();
}


