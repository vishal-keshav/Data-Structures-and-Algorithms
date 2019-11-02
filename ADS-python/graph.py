# This file implements the graph data structure and solve some algorithms
class vertex(object):
    """
    This implements the vertex node, that holds all the nodes it is directly
    connected to. To maintain the weights on the edges, the dictionary value
    can have an edge weight also as a tuple.
    """
    def __init__(self, key):
        self.key = key
        self.neighbours = {}

    def add_neighbour(self, key, edge_weight = 1):
        self.neighbours[key] = edge_weight

    def get_neighbour(self):
        return list(self.neighbours.keys())

    def get_edgeWeight(self, key):
        return self.neighbours[key]
    def __getitem__(self, key):
        return self.get_edgeWeight(key)

class Graph(object):
    """
    This implements the Graph data structure, which holds vertex, which in turn
    holds all the neighbours. We have assumed the graph is wighted directed. But
    both this assumptions can be dropped if we operate this structure in another
    way.
    """
    def __init__(self):
        self.vertices = {} # Each vertex object meiantains a neighbours
        self.nr_vertex = 0

    def add_vertex(self,key):
        self.vertices[key] = vertex(key)
        self.nr_vertex+=1 # Assume that no vertex is added twice

    def add_edge(self, v1, v2, edge_weight=1):
        self.vertices[v1].add_neighbour(v2, edge_weight)

    def get_vertices(self):
        return list(self.vertices.keys())

## Testing scripts
"""v = vertex(3)
v.add_neighbour(0)
v.add_neighbour(2)
print(v.get_neighbour())
print(v.get_edgeWeight(2))"""

"""g = Graph()
for i in range(5):
    g.add_vertex(i)
g.add_edge(0,2)
g.add_edge(0,3)
g.add_edge(3,4)
print(g.get_vertices())
# Here we print all edges in g
vertices = g.get_vertices()
for v in vertices:
    neighbours = g.vertices[v].get_neighbour()
    for u in neighbours:
        print(v,u, g.vertices[v][u])"""
