#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>

struct Node {
    int id;     // Identifiant du nœud
    int g;      // Coût actuel depuis le point de départ
    int h;      // Heuristique (estimation du coût restant jusqu'à l'arrivée)
    Node* parent; // Pointeur vers le nœud parent pour reconstruire le chemin
    std::vector<std::pair<int, int>> neighbors; // Liste des voisins avec le poids de l'arête

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
    // Ajouter un nœud au graphe avec une heuristique spécifique
    void addNode(int id, int heuristic) {
        nodes[id] = new Node(id, 0, nullptr, heuristic);
    }

    // Ajouter une arête pondérée entre deux nœuds
    void addEdge(int from, int to, int weight) {
        nodes[from]->neighbors.push_back(std::make_pair(to, weight));
        nodes[to]->neighbors.push_back(std::make_pair(from, weight));
    }

    // Exécuter l'algorithme A* pour trouver le chemin optimal entre deux nœuds
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
                // Chemin trouvé, reconstruction
                std::vector<Node*> path;
                while (current != nullptr) {
                    path.push_back(current);
                    current = current->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            closedSet[current->id] = current;

            // Générer les voisins
            for (const auto& neighbor : current->neighbors) {
                int neighborId = neighbor.first;
                int edgeWeight = neighbor.second;

                if (closedSet.find(neighborId) != closedSet.end()) {
                    continue;  // Ignore les nœuds déjà visités
                }

                int tentative_g = current->g + edgeWeight;
                Node* neighborNode = nodes[neighborId];

                // Vérifier s'il est dans la liste ouverte
                auto itOpen = std::find_if(openSet.begin(), openSet.end(), [neighborId](const Node* node) {
                    return node->id == neighborId;
                });

                if (itOpen == openSet.end() || tentative_g < (*itOpen)->g) {
                    // Mettre à jour ou ajouter à la liste ouverte
                    neighborNode->parent = current;
                    neighborNode->g = tentative_g;
                    //neighborNode->h = current->heuristic;
                    if (itOpen == openSet.end()) {
                        openSet.push_back(neighborNode);
                    }
                    std::push_heap(openSet.begin(), openSet.end(), CompareNode());
                }
            }
        }

        // Aucun chemin trouvé
        return std::vector<Node*>();
    }

private:
    std::unordered_map<int, Node*> nodes;
};

// Exemple d'heuristique personnalisée (distance euclidienne entre les nœuds)
int customHeuristic(int current, int goal) {
    return std::abs(current - goal);
}

int main() {
    Graph graph;

    // Ajouter des nœuds avec des heuristiques spécifiques
    graph.addNode(0, 9);
    graph.addNode(1, 3);
    graph.addNode(2, 4);
    graph.addNode(3, 6);
    graph.addNode(4, 8);
    graph.addNode(5, 4);
    graph.addNode(6, 2);
    graph.addNode(7, 0);

    // Ajouter des arêtes pondérées
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

    // Exécuter A* avec des heuristiques personnalisées
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
