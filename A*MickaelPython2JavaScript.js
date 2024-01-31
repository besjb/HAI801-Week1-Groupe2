class Graph {
    constructor(adjacencyList) {
        this.adjacencyList = adjacencyList;
    }

    getNeighbors(v) {
        return this.adjacencyList[v];
    }

    // heuristic function with equal values for all nodes
    h(n) {
        const H = {
            'A': 9,
            'B': 3,
            'C': 5,
            'D': 6,
            'E': 8,
            'F': 4,
            'G': 2,
            'H': 0
        };

        return H[n];
    }

    aStarAlgorithm(startNode, stopNode) {
        let openList = new Set([startNode]); // List of nodes visited who's neighbours haven't been visited
        let closedList = new Set([]); // List of nodes already visited and neighbours been visited

        let g = {}; // Distance 
        g[startNode] = 0;

        let parents = {}; // Adjacency map
        parents[startNode] = startNode;

        while (openList.size > 0) {
            let n = null;

            // find a node with the lowest value of f() - evaluation function
            for (let v of openList) {
                if (n === null || g[v] + this.h(v) < g[n] + this.h(n)) {
                    n = v;
                }
            }

            // No path available
            if (n === null) {
                console.log('Path does not exist!');
                return null;
            }
            
            // Path found
            if (n === stopNode) {
                let reconstPath = [];

                while (parents[n] !== n) {
                    reconstPath.push(n);
                    n = parents[n];
                }

                reconstPath.push(startNode);

                reconstPath.reverse();

                console.log('Path found: ' + reconstPath);
                return reconstPath;
            }

            // Parcour all of Neighbors
            for (let [m, weight] of this.getNeighbors(n)) {
                if (!openList.has(m) && !closedList.has(m)) {
                    openList.add(m);
                    parents[m] = n;
                    g[m] = g[n] + weight;
                } else {
                    if (g[m] > g[n] + weight) {
                        g[m] = g[n] + weight;
                        parents[m] = n;

                        if (closedList.has(m)) {
                            closedList.delete(m);
                            openList.add(m);
                        }
                    }
                }
            }

            openList.delete(n);
            closedList.add(n);
        }

        console.log('Path does not exist!');
        return null;
    }
}

function main() {
    const adjacencyList = {
        'A': [['B', 2], ['C', 10], ['D', 3]],
        'B': [['E', 8], ['A', 2]],
        'C': [['D', 6], ['A', 9], ['G', 2]],
        'D': [['A', 3], ['C', 5], ['F', 4]],
        'E': [['B', 8], ['F', 5], ['H', 10]],
        'F': [['D', 4], ['G', 5], ['E', 5]],
        'G': [['H', 1], ['F', 5], ['C', 2]]
    };

    const graph1 = new Graph(adjacencyList);
    graph1.aStarAlgorithm('A', 'H');

    return 1;
}

// Call main function
main()
