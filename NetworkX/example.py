import networkx as nx

G = nx.DiGraph()
G = nx.DiGraph([(1,2),(2,3)])
H = nx.DiGraph(G, graph_name = "test")

G.add_edge(1,2)
new_edge = (2,3)
G.add_edge(*new_edge)

new_edges = [(3,4),(4,5)]
G.add_edges_from(new_edges)

# edges can be set with a list of edge with a dictionary of properties at the end1  ww
new_edges = [(5,6, {'weight':7}), 
             (6,7, {'weight':8})]

G.add_edges_from(new_edges)

print(list(G.successors(1)))
print(G.edges)

print(list(G.nodes))
print(list(G.edges))

print(list(G.adj[1]))
print(G.degree[1])

print(G.edges([1,2]))
print(G.degree([1,2]))