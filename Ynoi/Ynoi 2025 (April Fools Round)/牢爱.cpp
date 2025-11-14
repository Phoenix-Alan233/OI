// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> bits;
    int n;
    Fenwick(int _n) : n(_n) {
        bits.resize(n + 1, 0);
    }
    void add(int i, int x) {
        i++;
        for (; i <= n; i += i & -i) bits[i] += x;
    }
    int sum(int i) {
        i++;
        int res = 0;
        for (; i > 0; i -= i & -i) res += bits[i];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, V;
    cin >> n >> m >> V;

    // L doesn't exceed 14
    int bits = __lg(m), L = 0;
    while ((1 << L) - 1 <= L * V) L++;

    vector<int> a(n);
    Fenwick tree(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector trans = vector(V, vector<int>(bits + 1, 0));
    for (int i = 0; i < V; i++) trans[i][0] = 1ll * i * i * i % V;
    for (int j = 1; j <= bits; j++) {
        for (int i = 0; i < V; i++) {
            trans[i][j] = trans[trans[i][j - 1]][j - 1];
        }
    }

    while (m--) {
        int opt, l, r;
        cin >> opt >> l >> r;
        l--, r--;
        if (opt == 1) {
            if (r - l + 1 >= L) cout << "Yuno" << endl;
            else {
                // L ~ O(log V)
                // O(L*(V*L)/w + L*logN) = O(V*(logV)^2/w + logV*logN)
                bitset<1000 * 13> bs;
                bs.set(0);
                for (int i = l; i <= r; i++) {
                    int x = a[i], e = tree.sum(i);
                    for (int j = bits; j >= 0; j--) {
                        if (e >> j & 1)
                            x = trans[x][j];
                    }
                    x++;
                    if ((bs & (bs >> x)).any()) {
                        cout << "Yuno" << endl;
                        goto end;
                    }
                    bs |= bs << x;
                }
                cout << "Yuki" << endl;
                end: ;
            }
        } else {
            tree.add(l, 1);
            tree.add(r + 1, -1);
        }
    }
    return 0;
}