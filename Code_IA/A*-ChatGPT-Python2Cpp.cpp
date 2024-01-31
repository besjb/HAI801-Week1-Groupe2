#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

class Graph {
public:
    std::unordered_map<char, std::vector<std::pair<char, int>>> edges;
    std::unordered_map<char, int> heuristics;

    void add_edge(char node1, char node2, int cost) {
        edges[node1].emplace_back(node2, cost);
        edges[node2].emplace_back(node1, cost);
    }

    void set_heuristic(char node, int heuristic) {
        heuristics[node] = heuristic;
    }
};

std::vector<char> astar(Graph& graph, char start, char goal) {
    using NodeCostPair = std::pair<int, char>;
    std::priority_queue<NodeCostPair, std::vector<NodeCostPair>, std::greater<NodeCostPair>> priority_queue;
    std::unordered_set<char> visited;
    std::unordered_map<char, int> path_costs;
    std::unordered_map<char, char> came_from;

    priority_queue.push({0, start});
    path_costs[start] = 0;
    came_from[start] = '\0';

    while (!priority_queue.empty()) {
        auto [current_cost, current_node] = priority_queue.top();
        priority_queue.pop();

        if (visited.count(current_node) > 0) {
            continue;
        }

        visited.insert(current_node);

        if (current_node == goal) {
            std::vector<char> path;
            while (current_node != '\0') {
                path.insert(path.begin(), current_node);
                current_node = came_from[current_node];
            }
            return path;
        }

        for (auto& [neighbor, cost] : graph.edges[current_node]) {
            int new_cost = path_costs[current_node] + cost;
            if (path_costs.find(neighbor) == path_costs.end() || new_cost < path_costs[neighbor]) {
                path_costs[neighbor] = new_cost;
                int priority = new_cost + graph.heuristics[neighbor];
                priority_queue.push({priority, neighbor});
                came_from[neighbor] = current_node;
            }
        }
    }

    return std::vector<char>();
}

int main() {
    Graph graph;

    graph.add_edge('A', 'B', 2);
    graph.add_edge('A', 'C', 10);
    graph.add_edge('A', 'D', 3);
    graph.add_edge('B', 'E', 8);
    graph.add_edge('D', 'C', 2);
    graph.add_edge('D', 'F', 4);
    graph.add_edge('C', 'G', 2);
    graph.add_edge('E', 'F', 5);
    graph.add_edge('F', 'G', 5);
    graph.add_edge('E', 'H', 10);
    graph.add_edge('G', 'H', 1);

    graph.set_heuristic('A', 9);
    graph.set_heuristic('B', 3);
    graph.set_heuristic('C', 5);
    graph.set_heuristic('D', 6);
    graph.set_heuristic('E', 8);
    graph.set_heuristic('F', 4);
    graph.set_heuristic('G', 2);
    graph.set_heuristic('H', 0);

    char start_node = 'A';
    char goal_node = 'H';

    std::vector<char> path = astar(graph, start_node, goal_node);

    if (!path.empty()) {
        std::cout << "Chemin trouvé de " << start_node << " à " << goal_node << ": ";
        for (char node : path) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Aucun chemin trouvé de " << start_node << " à " << goal_node << std::endl;
    }

    return 0;
}
