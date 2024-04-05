#include <iostream>
#include <lemon/bfs.h>
#include <lemon/list_graph.h>
#include <lemon/dijkstra.h>

using namespace lemon;
void Tutorial() 
{
     ListDigraph g;

    ListDigraph::Node v[9];
    for (int i = 0; i < 9; ++i)
    {
        ListDigraph::Node node = g.addNode();
        v[i] = node;
    }



    ListDigraph::Node v1 = g.addNode();
    ListDigraph::Node v2 = g.addNode();
    ListDigraph::Node v3 = g.addNode();

    ListDigraph::Arc a1 = g.addArc(v1,v2);
    ListDigraph::Arc a2 = g.addArc(v2,v3);
    ListDigraph::Arc a3 = g.addArc(v3,v1);

    // parallel and loop arcs are supported
    ListDigraph::Arc a4_parallel = g.addArc(v1,v2);
    ListDigraph::Arc a5_loop = g.addArc(v1,v1);

    // methods source and target in graph
    if (g.source(a5_loop) == g.target(a5_loop))
        std::cout << "This is a loop arc" << std::endl;

    // arcs and nodes have an unique non-negative identifier in their respective categories
    std::cout << "Arc a1 has the id " << g.id(a1) << std::endl;
    std::cout << "Vertex a1 has the id " << g.id(v1) << std::endl;

    // In fact, Node and Arc types are normally wrapper classes for int values


    // iterators to traverse the graph
    int counter = 0;
    for (ListDigraph::NodeIt n(g); n != INVALID; ++n)
        counter++;

    std::cout << "The number of nodes is " << counter << std::endl;

    // iterators are automatically converted to the item type

    ListDigraph::NodeIt n(g);
    std::cout << "The id of the first node of the graph g is :"
              << g.id(n); // n is either an iterator and the object itself

    // WARNING: graph traversal order is undefined, although one can assume that the current order of traversal will not change if the graph doesn't change

    ListDigraph::NodeIt   nodeIt(g);            //!< iterates through nodes in graph
    ListDigraph::ArcIt    arcIt(g);             //!< iterates through arcs in graph
    ListDigraph::InArcIt  inArcIt(g, v1);       //!< iterates through in arcs of a vertex in the graph
    ListDigraph::OutArcIt outArcIt(g, v1);      //!< iterates through out arcs of a vertex in the graph

    // count methods -> best case O(1), worst case O(N) -> faster because many graphs maintain this data
    
    countNodes(g);
    countArcs(g);
    countInArcs(g,v1);
    countOutArcs(g,v1);

    // maps -> maps(hashtables) are used to store data about nodes/arcs.

    struct NodeData {
        uint8_t weight;
        std::string description;
    };

    ListDigraph::NodeMap<NodeData> map(g);

    map[v1] = NodeData{5, "This is a router. Hi from router!"};
    map[v2] = NodeData{60, "This is a datacenter. Hi from datacenter!"};

    // its also possible to initialize maps with default values

    // ListDigraph::NodeMap<int> map(g, 2);
    ListDigraph::ArcMap<int> edges_weight(g, 2);

    ListDigraph::NodeMap<int> totalDist(g);

    Dijkstra<ListDigraph> dijkstra(g, edges_weight);
    dijkstra.distMap(totalDist);
    dijkstra.init();
    dijkstra.addSource(v1);
    dijkstra.start();

    for (ListDigraph::NodeIt it(g); it != INVALID; ++it)
    {
        std::cout << "Distance of node " << g.id(it) << " to source is: " << totalDist[it];
    }

}

void Example1_Dijkstra()
{

    /*
     * This example is based on the graph available on 
     * http://siddarthareddy.weebly.com/blog/dijkstras-algorithm-example
     */

    typedef ListDigraph Graph;
    typedef ListDigraph::Node Node;
    typedef ListDigraph::Arc Arc;

    Graph g;

    ListDigraph::NodeMap<char> nameMap(g);
    Node S = g.addNode();
    nameMap[S] = 'S';
    Node A = g.addNode();
    nameMap[A] = 'A';
    Node B = g.addNode();
    nameMap[B] = 'B';
    Node C = g.addNode();
    nameMap[C] = 'C';
    Node D = g.addNode();
    nameMap[D] = 'D';
    
    ListDigraph::ArcMap<int> weightArcMap(g);

    Arc S_A = g.addArc(S, A);
    weightArcMap[S_A] = 10;
    Arc S_C = g.addArc(S, C);
    weightArcMap[S_C] = 5;

    Arc A_B = g.addArc(A, B);
    weightArcMap[A_B] = 1;
    Arc A_C = g.addArc(A, C);
    weightArcMap[A_C] = 2;

    Arc B_D = g.addArc(B, D);
    weightArcMap[B_D] = 4;
    
    Arc C_A = g.addArc(C, A);
    weightArcMap[C_A] = 3;
    Arc C_B = g.addArc(C, B);
    weightArcMap[C_B] = 9;
    Arc C_D = g.addArc(C, D);
    weightArcMap[C_D] = 2;

    Arc D_S = g.addArc(D, S);
    weightArcMap[D_S] = 7;
    Arc D_B = g.addArc(D, B);
    weightArcMap[D_B] = 6;

    Graph::NodeMap<int> totalDist(g);

    Dijkstra<Graph> dijkstra(g, weightArcMap);
    dijkstra.distMap(totalDist);
    dijkstra.init();
    dijkstra.addSource(S);
    dijkstra.start();

    for (ListDigraph::NodeIt it(g); it != INVALID; ++it)
    {
        std::cout << "Distance of node " << nameMap[it] 
                  << " to source is: " << totalDist[it]
                  << std::endl;
    }
}

int main ()
{
   Example1_Dijkstra();

}