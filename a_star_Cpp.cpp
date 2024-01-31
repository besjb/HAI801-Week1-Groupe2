#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>

struct Node {
    int id;
    int g;
    int h;
    Node* parent; 
    std::vector<std::pair<int, int>> neighbors;

    Node(int id, int g, Node* parent, int heuristic)
        : id(id), g(g), h(heuristic), parent(parent) {}

    // Fonction de coût total f(n) = g(n) + h(n)
    int getF() const {
        return g + h;
    }
};

struct CompareNode {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->getF() > rhs->getF();
    }
};

class Graph {
public:
    void addNode(int id, int heuristic) {
        nodes[id] = new Node(id, 0, nullptr, heuristic);
    }
    void addEdge(int from, int to, int weight) {
        nodes[from]->neighbors.push_back(std::make_pair(to, weight));
        nodes[to]->neighbors.push_back(std::make_pair(from, weight));
    }

    std::vector<Node*> aStar(int startId, int goalId) {
        std::vector<Node*> openSet;
        std::unordered_map<int, Node*> closedSet;

        openSet.push_back(nodes[startId]);
        std::make_heap(openSet.begin(), openSet.end(), CompareNode());

        while (!openSet.empty()) {
            std::pop_heap(openSet.begin(), openSet.end(), CompareNode());
            Node* current = openSet.back();
            openSet.pop_back();

            if (current->id == goalId) {
                std::vector<Node*> path;
                while (current != nullptr) {
                    path.push_back(current);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            closedSet[current->id] = current;

            for (const auto& neighbor : current->neighbors) {
                int neighborId = neighbor.first;
                int edgeWeight = neighbor.second;

                if (closedSet.find(neighborId) != closedSet.end()) {
                    continue;
                }

                int tentative_g = current->g + edgeWeight;
                Node* neighborNode = nodes[neighborId];

                auto itOpen = std::find_if(openSet.begin(), openSet.end(), [neighborId](const Node* node) {
                    return node->id == neighborId;
                });

                if (itOpen == openSet.end() || tentative_g < (*itOpen)->g) {
                    neighborNode->parent = current;
                    neighborNode->g = tentative_g;
                    if (itOpen == openSet.end()) {
                        openSet.push_back(neighborNode);
                    }
                    std::push_heap(openSet.begin(), openSet.end(), CompareNode());
                }
            }
        }
        return std::vector<Node*>();
    }

private:
    std::unordered_map<int, Node*> nodes;
};

int main() {
    Graph graph;

    /*===Nodes===*/
    graph.addNode(0, 9);
    graph.addNode(1, 3);
    graph.addNode(2, 4);
    graph.addNode(3, 6);
    graph.addNode(4, 8);
    graph.addNode(5, 4);
    graph.addNode(6, 2);
    graph.addNode(7, 0);

    /*===Edges===*/
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 3);
    graph.addEdge(0, 2, 10);

    graph.addEdge(1, 5, 8);

    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 6, 2);

    graph.addEdge(3, 1, 2);
    graph.addEdge(3, 5, 4);

    graph.addEdge(4, 5, 5);
    graph.addEdge(4, 7, 10);

    graph.addEdge(5, 6, 5);

    graph.addEdge(6, 7, 2);
    
    int startId = 0;
    int goalId = 7;
    std::vector<Node*> path = graph.aStar(startId, goalId);

    if (path.empty()) {
        std::cout << "Aucun chemin trouvé." << std::endl;
    } else {
        std::cout << "Chemin trouvé :" << std::endl;
        for (const auto& node : path) {
            std::cout << (char)(node->id+65) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
