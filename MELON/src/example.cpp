#include <iostream>
#include "melon/algorithm/dijkstra.hpp"
#include "melon/container/static_digraph.hpp"
#include "melon/utility/static_digraph_builder.hpp"

using namespace fhamonic::melon;

int main () {
    // utility to build graph
    static_digraph_builder<static_digraph, double> builder(8);

    builder.add_arc(0, 1, 7)
           .add_arc(0, 5, 14)
           .add_arc(0, 2, 9)
           .add_arc(1, 0, 7)
           .add_arc(1, 2, 10)
           .add_arc(1, 3, 15)
           .add_arc(2, 0, 9)
           .add_arc(2, 1, 10)
           .add_arc(2, 3, 12)
           .add_arc(2, 5, 2)
           .add_arc(3, 1, 15)
           .add_arc(3, 2, 12)
           .add_arc(3, 4, 6)
           .add_arc(4, 3, 6)
           .add_arc(4, 5, 9)
           .add_arc(5, 0, 14)
           .add_arc(5, 2, 2)
           .add_arc(5, 4, 9);

    auto [graph, length_map] = builder.build();

    auto v1 = vertices(graph)[1];
    

    dijkstra djks(graph, length_map, 0);

    djks.run();

    // couldn't find the next step

}