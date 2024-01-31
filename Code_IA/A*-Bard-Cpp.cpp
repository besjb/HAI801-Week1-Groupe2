#include <iostream>
#include <vector>

using namespace std;

struct Node {
  char name;
  int cost;
  int heuristic;
  Node* parent;
  vector<Node*> neighbors;
};

const Node* const_iterator(const Node* node) {
  return node;
}

int main() {
  // Initialisation du graphe
  Node nodes[] = {
    {'A', 0, 9, nullptr},
    {'B', 2, 3, nullptr},
    {'C', 10, 5, nullptr},
    {'D', 3, 6, nullptr},
    {'E', 8, 8, nullptr},
    {'F', 4, 4, nullptr},
    {'G', 2, 2, nullptr},
    {'H', 0, 0, nullptr}
  };

  // Initialisation des voisins
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (nodes[i].neighbors.size() < nodes[j].neighbors.size()) {
        nodes[i].neighbors.push_back(&nodes[j]);
      }
    }
  }

  // Initialisation de la liste ouverte
  vector<Node*> openList(1);
  openList[0] = &nodes['A'];

  // Initialisation de la liste fermée
  vector<Node*> closedList;

  // Boucle principale
  while (!openList.empty()) {
    // Récupération du nœud le plus prometteur
    Node* current = openList[0];
    openList.erase(openList.begin());

    // Vérification si le nœud est le but
    if (current->name == 'H') {
      // Affichage du chemin
      while (current != &nodes['A']) {
        cout << current->name << " ";
        current = current->parent;
      }
      cout << endl;
      return 0;
    }

    // Ajout du nœud à la liste fermée
    closedList.push_back(current);

    // Parcours des voisins du nœud actuel
    for (Node* neighbor : openList) {
      // Calcul du coût estimé
      int estimatedCost = current->cost + current->heuristic + neighbor->heuristic;

      // Si le nœud n'est pas dans la liste ouverte ou que son coût estimé est inférieur
      if (find(openList.begin(), openList.end(), const_iterator(neighbor)) == openList.end() || estimatedCost < neighbor->cost) {
        neighbor->cost = estimatedCost;
        neighbor->parent = current;

        // Ajout du nœud à la liste ouverte
        openList.push_back(const_iterator(neighbor));
      }
    }
  }

  // Le but n'a pas été trouvé
  cout << "Le but n'a pas été trouvé" << endl;
  return 0;
}
