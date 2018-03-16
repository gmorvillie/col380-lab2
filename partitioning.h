#include<bits/stdc++.h>
using namespace std;

int num_levels = 15;

class vertex {
public:
    int deg; 
    bool match;
    vector<int> neighbour;  //for storing ids of all neighbours
    vector<int> weights;  
    int id;
    vector<vertex *> pneighbour;
    int matched_1; 
    int matched_2;
    bool visited;
    // int ;

    public:
    void init(uint deg1, bool match1, int id1, vector<int> &neighbour1, int matched1_1, int matched1_2)
    {
        deg = deg1;
        match = match1; 
        id = id1; 
        matched_1 = matched1_1; 
        matched_2 = matched1_2; 
        visited = false;

        for(int i=0;i<neighbour1.size();i++)
        {
            neighbour.push_back(neighbour1[i]);
            weights.push_back(1);
        }
    }

    void print_vertex()
    {
        cout<<"id "<<id<<" deg: "<<deg <<" match: "<<match<<" neighbours: ";
        for(int i=0;i<pneighbour.size();i++){
            if(pneighbour[i]!=NULL){
                cout<<pneighbour[i]->id<< " "<<neighbour[i]<<" ";
            }else{
                
                cout<<neighbour[i]<<" ";
            }
            
        }
        cout<<endl;
    }
};


class graph{
    public:
        int num_nodes;
        int num_edges;
        vector <vertex> vtx;     //vertex vector
        vector < pair<int, int> > edges; // for storing all edges 

        void print_graph()
        {
            cout<<"num_nodes: "<<num_nodes<<endl;
            cout<<"num_edges: "<<num_edges<<endl;
            for(uint i=0;i<vtx.size();i++)
                vtx[i].print_vertex();
            cout<<endl;
        }
};  



void buildGraph(graph &init_graph);





