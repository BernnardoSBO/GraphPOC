#include <iostream>
#include <sstream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/tuple/tuple.hpp>

struct VertexData
{
    std::string m_vertexName;
    uint8_t id;
};

struct EdgeData
{
    std::string m_edgeName;
    uint8_t id;
};

typedef boost::adjacency_list<boost::vecS,
                                boost::vecS,
                                boost::undirectedS,
                                VertexData, // using struct defined above to store data
                                boost::property<boost::edge_weight_t, double, EdgeData> // using boost predefined properties and also a custom data
                                > MyGraph;


void PrintVerticesNames(MyGraph &g);

void example0 ()
{
    typedef boost::adjacency_list<boost::vecS, // class on how to store outEdges (in this case, a vector, see EdgeList)
                                  boost::vecS, // class on how to store vertices (in this case, a vector, see VertexList)
                                  boost::directedS, // directedS, undirectedS
                                  boost::no_property, // vertex properties
                                  boost::no_property  // edge properties
                                  > NewGraph;

    NewGraph G; // alternatively G(start_EdgeArray, end_EdgeArray, numVertices)
    auto v1 = add_vertex(G); // templated global function, take graph G as a parameter, return the recently added vertex
    auto v2 = add_vertex(G); 
    auto e = add_edge(v1,v2,G);

    auto vpair = vertices(G); // returns a pair consisting of <first, last>

    for (auto i = vpair.first; i != vpair.second; i++)
    {
        std::cout << "vertex " << *i << std::endl;
    }

}


void example0a()
{
    std::cout << "Starting Example0a.."  << std::endl;


    // creating graph with 4 vertices

    MyGraph g(4); 

    // creating vertex descriptor type for this graph
    //      this corresponds to a vertex
    typedef boost::graph_traits<MyGraph>::vertex_descriptor MyVertex; // this type is a size_t

    // adding another vertex to the graph
    MyVertex v = add_vertex(g);
 
    // accessing vertex and then vertex struct data


    for (size_t iter = 0; iter < num_vertices(g); iter++)
    {
        std::stringstream ss;
        ss << "AP_0" << iter;
        g[iter].m_vertexName = ss.str();
    }

    PrintVerticesNames(g);

    std::cout << "The total amount of vertices in the graph G is " << num_vertices(g) << std::endl;

    // creating edge descriptor type for this graph
    //      this corresponds to an edge
    typedef boost::graph_traits<MyGraph>::edge_descriptor MyEdge; // this type is not a size_t

    // creating type corresponding to what is returned by add_edge where:
    //      first = edge descriptor
    //      second = bool if operation was successful or not
    typedef std::pair<MyEdge, bool> NewEdgeReturn;

    // adding an edge to the graph
    NewEdgeReturn e = add_edge(1,2, g);
    

    // accessing edge and then edge struct data
    g[e.first].m_edgeName = "LINK5Mbps";


    std::cout << "New edge from vertex 1 to vertex 2 was created" << std::endl;


    g[1].m_vertexName = "ROUTER_01";


    PrintVerticesNames(g);

    
    // retrieving data from the graph
    //      to retrieve data, we usually use descriptors
    //      descriptor consist of a generic way to identify something, in this case vertices and edges


    // there are plenty of ways to retrieve properties from the graph components
    // the following will serve as an example on how to do it


    // suppose we want to change the property m_edgeName of the only edge we added to the graph above
    //  1st -


    // a) retrieving the vertices
    //      vertex iterator
    typedef boost::graph_traits<MyGraph>::vertex_iterator MyVertexIterator; // defines iterator type. This type is a pointer to the vertex_descriptor
    MyVertexIterator vi, vi_end;

    int vertexFound = 0;
    MyVertex v1, v2;

    for (boost::tie(vi,vi_end) = boost::vertices(g); vi != vi_end; ++vi) // boost::vertices returns a pair of the first/last vertex
    {
        if (*vi == 0)
        {
            vertexFound++;
            v1 = *vi;
            break;
        }

        else if (*vi == 1)
        {
            vertexFound++;
            v2 = *vi;
            break;
        }
        
    }

    // b) retrieving the edge

    if (vertexFound == 2)
    {
        NewEdgeReturn retrievedEdge = edge(v1,v2,g); // boost::edge tries to retrieve an edge. It returns a pair where the first element consists of the edge descriptor and the second

        if (retrievedEdge.second) // sucessfully retrieval of the edge
        {
            std::string edgeName = g[retrievedEdge.first].m_edgeName;
            g[retrievedEdge.first].m_edgeName;
        }
    }

    // or

    boost::graph_traits<MyGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    {
        if (source(*ei, g) == v1 && target(*ei, g) == v2)
            break;
    }

    MyEdge edge1 = *ei;


    // also, we can get a property map of an specific property and iterate through the graph to retrieve/change it
    
    // this map maps each component(descriptor) in the graph to it's name
    boost::property_map<MyGraph, std::string EdgeData::*>::type 
    edgeNameMap = get(&EdgeData::m_edgeName, g);

    // 
    boost::property_map<MyGraph, boost::edge_weight_t>::type
    edgeWeightMap = get(boost::edge_weight, g);

    // the method get can have two signatures
    // the first method was observed above:
        // \param first parameter is a reference to where in the custom struct the data will be retrieved
        // \param second parameter is the graph
        // \returns it returns a map that maps descriptor to data

    // the second signature consists of
        // \param first parameter is a property_map
        // \param second parameter is the component descriptor (edge/vector)
        // \returns it returns the associated property value in the given descriptor
    
    double edgeWeight = get(edgeWeightMap, edge1);
}



void PrintVerticesNames(MyGraph &g)
{

    size_t VertexCardinality= boost::num_vertices(g);

    std::cout << "The current vertices names are.." << std::endl;
    for (int i = 0; i < VertexCardinality; i++)
    {
        std::cout << "new vertex " << i + 1 << " name is " << g[i].m_vertexName << std::endl;
    }
}

int main () {
    example0();
    example0a();
    return 0;
}