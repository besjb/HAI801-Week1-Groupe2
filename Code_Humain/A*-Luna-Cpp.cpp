#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
    char name;
    int id;
    std::vector<int> neighbors;
    std::vector<int> costs;
    int g = 999999999;
    int h;
    Node *parent = nullptr;

    Node(char name, int id, int h, std::vector<int> neighbours, std::vector<int> costs) : name(name), id(id), h(h), neighbors(neighbours), costs(costs) {}
};

bool AStar(int start, int goal, std::vector<Node> &graph, std::vector<int> &path)
{
    std::vector<Node *> open;
    std::vector<Node *> closed;

    Node *startNode = &graph[start];
    Node *goalNode = &graph[goal];

    open.push_back(startNode);
    startNode->g = 0;
    Node *current = nullptr;

    while (current != goalNode)
    {
        int lowestF = 999999999;
        for (auto node : open)
        {
            int f = node->g + node->h;
            if (f < lowestF)
            {
                lowestF = f;
                current = node;
            }
        }

        std::cout << "Current: " << current->name << std::endl;

        // remove current from open
        for (int i = 0; i < open.size(); i++)
        {
            if (open[i] == current)
            {
                open.erase(open.begin() + i);
                break;
            }
        }

        // add current to closed
        closed.push_back(current);

        // check if goal
        if (current == goalNode)
        {
            break;
        }

        // for each neighbor of current
        for (int i = 0; i < current->neighbors.size(); i++)
        {
            Node *neighbor = &graph[current->neighbors[i]];
            int cost = current->costs[i];

            // if neighbor is in closed
            bool inClosed = false;
            for (auto node : closed)
            {
                if (node == neighbor)
                {
                    inClosed = true;
                    break;
                }
            }
            if (inClosed)
            {
                continue;
            }

            // if new path to neighbor is shorter
            if (current->g + cost < neighbor->g)
            {
                neighbor->g = current->g + cost;
                neighbor->parent = current;
            }

            // if neighbor is not in open
            bool inOpen = false;
            for (auto node : open)
            {
                if (node == neighbor)
                {
                    inOpen = true;
                    break;
                }
            }
            if (!inOpen)
            {
                neighbor->parent = current;
                open.push_back(neighbor);
            }
        }
    }

    // build path
    path.clear();
    Node *node = goalNode;
    while (node != nullptr)
    {
        path.push_back(node->id);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());

    return true;
}

int costFrom(Node from, Node to)
{
    // check if to is a neighbor of from
    for (int i = 0; i < from.neighbors.size(); i++)
    {
        if (from.neighbors[i] == to.id)
        {
            return from.costs[i];
        }
    }
    std::cout << "Error: " << to.name << " is not a neighbor of " << from.name << std::endl;
    return 999999999;
}

int main()
{
    Node A('A', 0, 9, {1, 2, 3}, {2, 10, 3});
    Node B('B', 1, 3, {0, 4}, {2, 8});
    Node C('C', 2, 5, {0, 3, 6}, {10, 2, 2});
    Node D('D', 3, 4, {0, 2, 5}, {3, 2, 4});
    Node E('E', 4, 8, {1, 5, 7}, {8, 5, 10});
    Node F('F', 5, 4, {3, 4, 6}, {4, 5, 5});
    Node G('G', 6, 2, {2, 5, 7}, {2, 5, 1});
    Node H('H', 7, 0, {3, 5}, {10, 1});

    std::vector<Node> graph = {A, B, C, D, E, F, G, H};

    std::vector<int> path;
    AStar(0, 7, graph, path);

    int cost = 0;
    for (int i = 0; i < path.size(); i++)
    {
        int node = path[i];
        std::cout << graph[node].name << " ";
        if (i > 0)
        {
            cost += costFrom(graph[path[i - 1]], graph[node]);
        }
    }

    std::cout << std::endl
              << "Cost: " << cost << std::endl;
}