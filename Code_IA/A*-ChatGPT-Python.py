import heapq

class Graph:
    def __init__(self):
        self.edges = {}
        self.heuristics = {}

    def add_edge(self, node1, node2, cost):
        self.edges.setdefault(node1, []).append((node2, cost))
        self.edges.setdefault(node2, []).append((node1, cost))

    def set_heuristic(self, node, heuristic):
        self.heuristics[node] = heuristic

def astar(graph, start, goal):
    priority_queue = [(0, start)]
    visited = set()
    path_costs = {start: 0}
    came_from = {start: None}

    while priority_queue:
        current_cost, current_node = heapq.heappop(priority_queue)

        if current_node in visited:
            continue

        visited.add(current_node)

        if current_node == goal:
            path = []
            while current_node is not None:
                path.insert(0, current_node)
                current_node = came_from[current_node]
            return path

        for neighbor, cost in graph.edges.get(current_node, []):
            new_cost = path_costs[current_node] + cost
            if neighbor not in path_costs or new_cost < path_costs[neighbor]:
                path_costs[neighbor] = new_cost
                priority = new_cost + graph.heuristics[neighbor]
                heapq.heappush(priority_queue, (priority, neighbor))
                came_from[neighbor] = current_node

    return None

if __name__ == "__main__":
    graph = Graph()

    graph.add_edge('A', 'B', 2)
    graph.add_edge('A', 'C', 10)
    graph.add_edge('A', 'D', 3)
    graph.add_edge('B', 'E', 8)
    graph.add_edge('D', 'C', 2)
    graph.add_edge('D', 'F', 4)
    graph.add_edge('C', 'G', 2)
    graph.add_edge('E', 'F', 5)
    graph.add_edge('F', 'G', 5)
    graph.add_edge('E', 'H', 10)
    graph.add_edge('G', 'H', 1)

    graph.set_heuristic('A', 9)
    graph.set_heuristic('B', 3)
    graph.set_heuristic('C', 5)
    graph.set_heuristic('D', 6)
    graph.set_heuristic('E', 8)
    graph.set_heuristic('F', 4)
    graph.set_heuristic('G', 2)
    graph.set_heuristic('H', 0)

    start_node = 'A'
    goal_node = 'H'

    path = astar(graph, start_node, goal_node)

    if path:
        print(f"Chemin trouvé de {start_node} à {goal_node}: {path}")
    else:
        print(f"Aucun chemin trouvé de {start_node} à {goal_node}")
