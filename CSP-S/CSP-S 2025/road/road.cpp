// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

struct road {
    int u, v, w;
    road(int _u = 0, int _v = 0, int _w = 0): u(_u), v(_v), w(_w) {}
    bool operator<(const road &other) const {
        return w < other.w;
    }
};

class DSU {
private:
    vector<int> parent;
public:
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<road> edges, mst;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.push_back({u, v, w});
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n);
    for (auto &edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst.push_back(edge);
        }
    }
    assert(mst.size() == n - 1);

    vector<int> c(k);
    vector<vector<road>> extra_edge(k);

    for (int i = 0; i < k; i++) {
        int id = n + i;
        cin >> c[i];
        for (int j = 0; j < n; j++) {
            int w;
            cin >> w;
            extra_edge[i].push_back({id, j, w});
        }
        sort(extra_edge[i].begin(), extra_edge[i].end());
    }

    long long ans = LLONG_MAX;

    auto dfs = [&](auto &&dfs, int idx, vector<road> edges, long long extra_cost) -> void {
        if (idx == k) {
            long long cost = extra_cost;
            DSU dsu_final(n + k);
            for (auto &edge : edges) {
                if (dsu_final.find(edge.u) != dsu_final.find(edge.v)) {
                    dsu_final.unite(edge.u, edge.v);
                    cost += edge.w;
                }
            }
            ans = min(ans, cost);
            return;
        }
        dfs(dfs, idx + 1, edges, extra_cost);
        vector<road> merged_edges(edges.size() + extra_edge[idx].size());
        merge(edges.begin(), edges.end(),
              extra_edge[idx].begin(), extra_edge[idx].end(),
              merged_edges.begin());
        dfs(dfs, idx + 1, merged_edges, extra_cost + c[idx]);
    };
    dfs(dfs, 0, mst, 0);

    cout << ans << endl;
    return 0;
}