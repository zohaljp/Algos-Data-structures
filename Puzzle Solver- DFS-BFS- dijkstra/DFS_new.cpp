#include <bits/stdc++.h>
using namespace std;

#define D 3

struct Node
{
    Node* parent;

    int puzzle[D][D];
    int x, y;
    int cost;
    int level;
};

int printMatrix(int puzzle[D][D])

{
    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++) printf("%d ", puzzle[i][j]);
        printf("\n");
    }
}

Node* newNode(int puzzle[D][D], int x, int y, int newX, int newY, int level, Node* parent)

{
    Node* node = new Node;

    node->parent = parent;

    memcpy(node->puzzle, puzzle, sizeof node->puzzle);
    swap(node->puzzle[x][y], node->puzzle[newX][newY]);

    node->cost = INT_MAX;

    node->level = level;
    node->x = newX;
    node->y = newY;

    return node;
}

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

int calculateCost(int startState[D][D], int goalState[D][D])

{
    int count = 0;

    for (int i = 0; i < D; i++)
      for (int j = 0; j < D; j++)
        if (startState[i][j] && startState[i][j] != goalState[i][j]) count++;
    
    return count;
}

int isValid(int x, int y)

{
    return (x >= 0 && x < D && y >= 0 && y < D);
}

void printSteps(Node* root)
{
    if (root == NULL) return;

    printSteps(root->parent);
    printMatrix(root->puzzle);

    printf("\n");
}

struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }

};

void DFS(int startState[D][D], int x, int y, int goalState[D][D])
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    Node* root = newNode(startState, x, y, x, y, 0, NULL);

    root->cost = calculateCost(startState, goalState);
    pq.push(root);

    int totalCost = 0;

    while (!pq.empty())
    {
        Node* min = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            if (isValid(min->x + row[i], min->y + col[i]))
            {
                Node* child = newNode(
                    min->puzzle, 
                    min->x,
                    min->y, min->x + row[i],
                    min->y + col[i],
                    min->level + 1, min
                );
                
                child->cost = calculateCost(child->puzzle, goalState);
                totalCost += child->cost;

                pq.push(child);
            }
        }

        if (min->cost == 0)
        {
            printSteps(min);
            printf("Success!\nThe total cost for the DFS is: %d\n\n", totalCost);
            return;
        }
    }
}

int main()
{

    // First test case
        // {1, 3, 4},
        // {8, 0, 2},
        // {7, 6, 5}

    int startState[D][D] =
    {
        // Second test case
        {1, 3, 4},
        {8, 0, 6},
        {7, 5, 2}
    };

    int goalState[D][D] =

    {
        {1, 2, 3},
        {8, 0, 4},
        {7, 6, 5}
    };

    int x = 1, y = 2;
    DFS(startState, x, y, goalState);

    return 0;
}