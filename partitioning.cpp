#include "partitioning.h"
#include <string>
#include <algorithm>
#include <random>


vector<vertex> all_vertices;

vector<graph> all_GRAPHS;

void string_to_array(vector<int> &v, string s)
{
    int num=0; 
    for( uint i=0;i< s.size();i++)
    {
        if(s[i]==' ')
        {
            if(num!=0)
            {
                v.push_back(num);
                num=0;
            }
        }
        else
        {
            num = num*10+(int)(s[i]-48);            
        }

    }
    if(num!=0)
    v.push_back(num);

}
void print_match(vector <pair<vertex,vertex>> & matching)
{
    for(int j =0; j< matching.size(); j++){
    cout<<matching[j].first.id<<" "<<matching[j].second.id<<endl;
    }
}

void randomMatch( graph *source, vector <pair<vertex,vertex>> * matching){
    int nbMtch = 1;
        // cout<<source->vtx[0].deg<<endl;    
    // source->print_graph();
    //     cout<<"Yoyo2"<<endl;   
    for( int i3 = 0; i3<nbMtch; i3++){        // the number of matching that are calculated can vary. How to choose it ?
        int tempSize;
        (*matching).clear();

        // source.vtx[0].for_checking = 100; 
/*        source->vtx[1].pneighbour[0]->for_checking = 100;
        cout<<"for checking: "<<source->vtx[1].pneighbour[0]->for_checking<<" "<<source->vtx[1].pneighbour[0]->id<<" "<<source->vtx[0].for_checking<<endl;*/     
        
        // source->print_graph();
/*        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(source->vtx), std::end(source->vtx), rng);*/
        vector <vertex>::iterator i1;
        // cout<<"Yoyo1"<<endl;
        for (i1=source->vtx.begin();i1!=source->vtx.end();++i1)
        {   // randomly iterates over the vertices
            // source->print_graph();           
            
            if(!i1->match){
                
                // cout<<"I am inside matching: "<<i1->id<<" "<<i1->match<<endl;     
                
                //int i
                for(int i=0;i< i1->pneighbour.size();i++)
                {
                    if(!i1->pneighbour[i]->match)
                    {
                        (*matching).push_back(make_pair(*i1, *i1->pneighbour[i]));
                        i1->match=true;  
                        i1->pneighbour[i]->match=true;
                        break;
                    }

                }                     
                
            }
        }
        if(tempSize<matching->size()) 
            tempSize=matching->size();
    }
}

void merge_graph(graph *old_graph, graph *new_graph)
{

}
void partition(graph* main_graph, graph* left_graph, graph* right_graph)
{

    int total_weight=0; 
    for(int i=0;i<main_graph->num_nodes; i++)
    {
        // cout<<main_graph->vtx[i].weights.size()<<endl;
        for(int j=0;j<main_graph->vtx[i].weights.size();j++)
        {   
            total_weight+=main_graph->vtx[i].weights[j];
        }
    }

    queue<vertex* > bfs_queue;

    bfs_queue.push(&main_graph->vtx[0]);  //right now pushing first vertex but its is random actually 

    int edge_weight=0;
    int f=0; 
    while(edge_weight<total_weight/4 && bfs_queue.size()>0)
    {

        vertex* temp_vertex = bfs_queue.front(); 
        bfs_queue.pop();
        left_graph->vtx.push_back(*temp_vertex);
        cout<<"YoYo1"<<endl;
        for(int j=0;j<temp_vertex->neighbour.size();j++)
         {   
                if(!temp_vertex->pneighbour[j]->visited)
                {
                    bfs_queue.push(temp_vertex->pneighbour[j]);
                    edge_weight=edge_weight+temp_vertex->weights[j]; 
                    temp_vertex->pneighbour[j]->visited=true; 
                    f++;
                }
         }
    }

    for(int i=0;i<main_graph->num_nodes;i++)
    {
            if(!main_graph->vtx[i].visited)
            {
                right_graph->vtx.push_back(main_graph->vtx[i]);
            }
    }
    cout<<"Total Weeight: "<<total_weight<<" "<<" edge_weight: "<<edge_weight<<endl;
    cout<<"Num of nodes in left Graph: "<<left_graph->vtx.size()<<" "<<f<<endl;
    cout<<"Num of nodes in right Graph: "<<right_graph->vtx.size()<<endl;
    cout<<"Total no of nodes Graph: "<<main_graph->vtx.size()<<endl;    
}

void coarse(graph &source){

    vector<graph *> all_graphs; 
    all_graphs.push_back(&source);

    for(int i=0;i<num_levels;i++)
    {

        vector < pair<vertex, vertex> > matching;
        // cout<<"Graph Size: "<<num_levels<<endl;
        // cout<<"Graph Size1: "<<all_graphs[i]->vtx[0].pneighbour.size()<<endl;
        randomMatch(all_graphs[i], &matching); 
        // cout<<"Graph Size: "<<matching.<<endl;
        // print_match(matching);

        map< int, int > mappings;
        graph temp_graph;
        int temp_ids=1; 

        temp_graph.num_nodes = all_graphs[i]->num_nodes - matching.size(); 
        for(int j=0;j<matching.size();j++)
        {
            vertex new_vertex;
            vector <int> temp_neighbours; 
            new_vertex.init(matching[j].first.deg+matching[j].second.deg-2, 0, temp_ids,temp_neighbours, matching[j].first.id, matching[j].second.id);  //    void init(uint deg1, bool match1, int id1, vector<int> &neighbour1)
            mappings.insert(pair<int, int>(matching[j].first.id, temp_ids));             
            mappings.insert(pair<int, int> (matching[j].second.id, temp_ids));
            // all_vertices.push_back(new_vertex); 
            // temp_graph.vtx.push_back(all_vertices[all_vertices.size()-1]);
            temp_graph.vtx.push_back(new_vertex);
            temp_ids++; 
        }
        for(int j=0;j<all_graphs[i]->num_nodes;j++)
        {
            if(!all_graphs[i]->vtx[j].match)
            {
                vertex new_vertex;
                vector <int> temp_neighbours; 
                new_vertex.init(all_graphs[i]->vtx[j].deg, 0, temp_ids,temp_neighbours, all_graphs[i]->vtx[j].id, -1);  //    void init(uint deg1, bool match1, int id1, vector<int> &neighbour1)
                mappings.insert(pair<int,int> (all_graphs[i]->vtx[j].id, temp_ids)); 
                // all_vertices.push_back(new_vertex); 
                // temp_graph.vtx.push_back(all_vertices[all_vertices.size()-1]);
                temp_graph.vtx.push_back(new_vertex);
                temp_ids++;                
            }
        }

        // cout<<"Temp Ids: "<<temp_ids<<endl;
        map< int, int > mappings_neighbours;
        set< pair<int, int> > txt;
        for(int j=0; j< all_graphs[i]->vtx.size();j++)
        {
            for(int k=0; k< all_graphs[i]->vtx[j].neighbour.size();k++) 
                {
                    int num1= mappings[all_graphs[i]->vtx[j].id]; 
                    int num2= mappings[all_graphs[i]->vtx[j].pneighbour[k]->id]; 
                    // cout<<j<<" "<<num1<<" "<<num2<<endl;
                    if(num1!=num2)
                        {
                            mappings_neighbours.insert(pair<int, int>(num1, num2));
                            txt.insert(make_pair(num1, num2));
                            // temp_graph.vtx[num1-1].neighbour.push_back(num2);
                            // temp_graph.vtx[num1-1].pneighbour.push_back(&temp_graph.vtx[num2-1]);
                        }
                }
        }       


        all_GRAPHS.push_back(temp_graph); 
        set < pair<int, int> > :: iterator itr;
        for(itr= txt.begin();itr!=txt.end();itr++)
        {
            all_GRAPHS[all_GRAPHS.size()-1].vtx[itr->first-1].neighbour.push_back(itr->second);
            all_GRAPHS[all_GRAPHS.size()-1].vtx[itr->first-1].weights.push_back(1);  //have to change it based on number of edges. 
            all_GRAPHS[all_GRAPHS.size()-1].vtx[itr->first-1].pneighbour.push_back(&all_GRAPHS[all_GRAPHS.size()-1].vtx[itr->second-1]);
        }

        all_graphs.push_back(&all_GRAPHS[all_GRAPHS.size()-1]);
        // all_GRAPHS[all_GRAPHS.size()-1].print_graph();
        // cout<<"hello"<<endl;
        // cout<<"YoYo1"<<endl;
        // temp_graph.print_graph();
        // print_match(matching);
    }


    graph left_graph;
    graph right_graph;  
    partition(&all_GRAPHS[all_GRAPHS.size()-1], &left_graph, &right_graph);
    cout<<all_GRAPHS[all_GRAPHS.size()-1].num_nodes<<endl;
}
    


void buildGraph( graph &init_graph ){
    
    string str;      //string to read data 
    vector<int> v;  //vector to store parsed numbers

    ifstream myfile ("input2.txt");
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
            temp.init(v.size(), false, id, v, -1, -1);
            init_graph.vtx.push_back(temp);
            id++;
            // if(id==2)
            // {
            //     for(int i=0;i<v.size();i++)
            //         cout<<" "<<v[i];
            // }
            // cout<<id<<endl;
        }
    }
    // cout<<"hello brother"<<endl;
    for(int i4 = 0; i4<init_graph.num_nodes;i4++){      // update the pointers to neighbors --> inefficient !
       // cout<<i4<<endl;
        for(int i5 = 0; i5<init_graph.vtx[i4].deg;i5++){
            int n=init_graph.vtx[i4].neighbour[i5];
            // cout<<n<<" "<<init_graph.vtx[i4].deg<<" "<<init_graph.vtx[n-1].id<<endl;   
            
            if(n== init_graph.vtx[n-1].id){        //if the ith element has id i --> faster than search for id i
                
                init_graph.vtx[i4].pneighbour.push_back(&init_graph.vtx[n-1]);       //in the list of pointers to neighbours, add the adress of this neighbour
            }
                
        }
    }
}

int main() {

vector < pair<vertex, vertex> > matching;
const clock_t begin_time = clock();
graph init_graph;

buildGraph (init_graph) ;
/*init_graph.print_graph();*/
cout<<"Read All Data"<<endl;
coarse(init_graph);
// randomMatch( init_graph, &matching);


std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;


// cout<< "matching 1 " <<matching.size()<<endl;

for(int j =0; j< matching.size(); j++){
    cout<<matching[j].first.id<<" "<<matching[j].second.id<<endl;
}


// init_graph.print_graph();
}


