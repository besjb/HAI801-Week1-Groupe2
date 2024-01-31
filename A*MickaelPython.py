from collections import deque

class Graph:

    def __init__(self, adjacency_list):
        self.adjacency_list = adjacency_list

    def get_neighbors(self, v):
        return self.adjacency_list[v]

    # heuristic
    def h(self, n):
        H = {
            'A': 9,
            'B': 3,
            'C': 5,
            'D': 6,
            'E': 8,
            'F': 4,
            'G': 2,
            'H': 0
        }

        return H[n]

    def a_star_algorithm(self, start_node, stop_node):
        open_list = set([start_node]) # List of nodes visited who's neighbours haven't been visited
        closed_list = set([]) # List of nodes already visited and neighbours been visited

        g = {} # Distance
        g[start_node] = 0

        # parents contains an adjacency map of all nodes
        parents = {}
        parents[start_node] = start_node

        while len(open_list) > 0:
            n = None
            # find a node with the lowest value of f()
            for v in open_list:
                if n == None or g[v] + self.h(v) < g[n] + self.h(n):
                    n = v
            
            # No node found
            if n == None:
                print('Path does not exist!')
                return None

            if n == stop_node:
                reconst_path = []

                while parents[n] != n:
                    reconst_path.append(n)
                    n = parents[n]

                reconst_path.append(start_node)
                reconst_path.reverse()

                print('Path found: {}'.format(reconst_path))
                return reconst_path

            # for all neighbors of the current node do
            for (m, weight) in self.get_neighbors(n):
                # if the current node isn't in both open_list and closed_list
                # add it to open_list and note n as it's parent
                if m not in open_list and m not in closed_list:
                    open_list.add(m)
                    parents[m] = n
                    g[m] = g[n] + weight

                else:
                    if g[m] > g[n] + weight:
                        g[m] = g[n] + weight
                        parents[m] = n

                        if m in closed_list:
                            closed_list.remove(m)
                            open_list.add(m)

            # remove n from the open_list, and add it to closed_list
            open_list.remove(n)
            closed_list.add(n)

        print('Path does not exist!')


def main():

    # Nodes
    adjacency_list = {
    'A': [('B', 2), ('C', 10), ('D', 3)],
    'B': [('E', 8), ('A', 2)],
    'C': [('D', 6), ('A', 9), ('G', 2)],
    'D': [('A', 3), ('C', 5), ('F', 4)],
    'E': [('B', 8), ('F', 5), ('H', 10)],
    'F': [('D', 4), ('G', 5), ('E', 5)],
    'G': [('H', 1), ('F', 5), ('C', 2)]
    }

    graph1 = Graph(adjacency_list)
    graph1.a_star_algorithm('A', 'H')

if __name__ == '__main__':
    main()