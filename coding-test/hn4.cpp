#include <vector>

using namespace std;

struct Node {
    int dst, cost;
};

vector<vector<Node>> adjList(100);
int minCost = 2147000000;

void DFS(int pos1, int pos2, int cost, int mask) {
    // visited all
    if (mask == 0) {
        // update minimum cost
        minCost = (minCost < cost) ? minCost : cost;
        return;
    }

    // possible 
    for (Node next1 : adjList[pos1]) {
        // if visited, continue
        if (mask & (1 << next1.dst) == 0) continue;

        // pos1 move
        DFS(next1.dst, pos2, cost + next1.cost, mask & ~(1 << next1.dst));  

        for (Node next2 : adjList[pos2]) {
            // if visited, continue
            if (mask & (1 << next2.dst) == 0) continue;

            // pos2 move
            DFS(pos1, next2.dst, cost + next2.cost, mask & ~(1 << next2.dst));

            // pos1 & pos2 move
            DFS(next1.dst, next2.dst, cost + next1.cost + next2.cost, mask & ~((1 << next1.dst) | (1 << next2.dst)));
        }
    }
}

int solution(vector<vector<int>> dist, int pos1, int pos2) {
    int bitMask = 0;

    for (vector<int> d : dist) {
        // bidirectional graph
        adjList[d[0]].push_back({d[1], d[2]});
        adjList[d[1]].push_back({d[0], d[2]});
        bitMask |= (1 << d[0]) | (1 << d[1]);
    }

    DFS(pos1, pos2, 0, bitMask);

    return minCost;
}