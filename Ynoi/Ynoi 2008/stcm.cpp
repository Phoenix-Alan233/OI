#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

vector<int> adj[N];
int L[N], R[N], idfn[N], sz[N], dtot;

void dfs1(int u) {
    L[u] = ++dtot;
    idfn[dtot] = u;
    sz[u] = 1;
    for (auto v : adj[u]) {
        dfs1(v);
        sz[u] += sz[v];
    }
}

void solve(int l, int r, vector<int> qry) {
    if (l > r) return;
    // 处理所有跨越点 idfn[mid] 的询问
    int mid = l + r >> 1;
    vector<int> qryL, qryR;
    int ptrl = l, ptrr = r;
    for (auto i : qry) {
        if (R[i] < mid) {
            qryL.push_back(i);
        } else if (L[i] > mid) {
            qryR.push_back(i);
        } else {
            while (ptrl < L[i]) printf("+%d", idfn[ptrl]), ptrl++;
            while (ptrr > R[i]) printf("+%d", idfn[ptrr]), ptrr--;
            printf("=%d", i);
        }
    }
    while (ptrr < r) ++ptrr, putchar('-');
    while (ptrl > l) --ptrl, putchar('-');
    if (qryL.size()) {
        for (int i = mid; i <= r; i++) printf("+%d", idfn[i]);
        solve(l, mid - 1, qryL);
        for (int i = mid; i <= r; i++) putchar('-');
    }
    if (qryR.size()) {
        for (int i = l; i <= mid; i++) printf("+%d", idfn[i]);
        solve(mid + 1, r, qryR);
        for (int i = l; i <= mid; i++) putchar('-');
    }
}

int main() {
    int n;
    while (cin >> n) {
        dtot = 0;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        for (int i = 2; i <= n; i++) {
            int fa; cin >> fa;
            adj[fa].push_back(i);
        }
        dfs1(1);
        vector<int> qry;
        for (int i = 1; i <= n; i++) {
            R[i] = L[i] + sz[i] - 1;
            qry.push_back(i);
        }
        sort(qry.begin(), qry.end(), [&](int x, int y) {
            return L[x] < L[y];
        });
        solve(1, n, qry);
        puts("!");
    }
    return 0;
}