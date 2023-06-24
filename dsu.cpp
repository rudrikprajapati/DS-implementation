#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> rank, size, parent;

public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Find the ultimate parent (representative) of a node with path compression
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Union two sets by rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;  // Already in the same set

        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    // Union two sets by size
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v)
            return;  // Already in the same set

        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

int main() {
    DisjointSet ds(7);

    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);

    // Check if nodes 3 and 7 belong to the same set
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Nodes 3 and 7 belong to the same set.\n";
    } else {
        cout << "Nodes 3 and 7 do not belong to the same set.\n";
    }

    ds.unionByRank(3, 7);

    // Check again if nodes 3 and 7 belong to the same set
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Nodes 3 and 7 belong to the same set.\n";
    } else {
        cout << "Nodes 3 and 7 do not belong to the same set.\n";
    }

    return 0;
}
