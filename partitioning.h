#include<bits/stdc++.h>
using namespace std;


class vertex {
public:
	int deg; 
	bool match;
	vector<int> neighbour;  //for storing ids of all neighbours
	int id; 


	public:
	void init(uint deg1, bool match1, int id1, vector<int> &neighbour1)
	{
		deg = deg1;
		match = match1; 
		id = id1; 
		for(int i=0;i<deg;i++)
		{
			neighbour.push_back(neighbour1[i]);
		}
	}

	void print_vertex()
	{
		cout<<"deg: "<<deg <<" match: "<<match<<" neighbours: ";
		for(int i=0;i<deg;i++)
			cout<<neighbour[i]<<" ";
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





