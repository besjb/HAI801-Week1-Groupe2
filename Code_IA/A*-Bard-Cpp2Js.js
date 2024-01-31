const Node = function (name, cost, heuristic, parent, neighbors) {
  this.name = name;
  this.cost = cost;
  this.heuristic = heuristic;
  this.parent = parent;
  this.neighbors = neighbors || [];
};

const const_iterator = function (node) {
  return node;
};

function main() {
  // Initialisation du graphe
  const nodes = [
    new Node('A', 0, 9, null),
    new Node('B', 2, 3, null),
    new Node('C', 10, 5, null),
    new Node('D', 3, 6, null),
    new Node('E', 8, 8, null),
    new Node('F', 4, 4, null),
    new Node('G', 2, 2, null),
    new Node('H', 0, 0, null)
  ];

  // Initialisation des voisins
  for (let i = 0; i < 8; i++) {
    for (let j = 0; j < 8; j++) {
      if (nodes[i].neighbors.length < nodes[j].neighbors.length) {
        nodes[i].neighbors.push(nodes[j]);
      }
    }
  }

  // Initialisation de la liste ouverte
  const openList = [nodes['A']];

  // Initialisation de la liste fermée
  const closedList = [];

  // Boucle principale
  while (openList.length) {
    // Récupération du nœud le plus prometteur
    const current = openList[0];
    openList.splice(0, 1);

    // Vérification si le nœud est le but
    if (current.name === 'H') {
      // Affichage du chemin
      while (current !== nodes['A']) {
        console.log(current.name);
        current = current.parent;
      }
      console.log();
      return 0;
    }

    // Ajout du nœud à la liste fermée
    closedList.push(current);

    // Parcours des voisins du nœud actuel
    for (const neighbor of openList) {
      // Calcul du coût estimé
      const estimatedCost = current.cost + current.heuristic + neighbor.heuristic;

      // Si le nœud n'est pas dans la liste ouverte ou que son coût estimé est inférieur
      if (openList.find(const_iterator(neighbor)) === openList.length - 1 || estimatedCost < neighbor.cost) {
        neighbor.cost = estimatedCost;
        neighbor.parent = current;

        // Ajout du nœud à la liste ouverte
        openList.push(const_iterator(neighbor));
      }
    }
  }

  // Le but n'a pas été trouvé
  console.log('Le but n\'a pas été trouvé');
  return 0;
}

main();
