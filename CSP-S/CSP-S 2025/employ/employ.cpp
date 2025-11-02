// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

void add(int &x, int y) {
    if ((x += y) >= mod) x -= mod;
}

int main() {
    int n, m;
    string s;
    cin >> n >> m;
    cin >> s;

    vector<int> a(n + 1), prea(n + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }

    prea[0] = a[0];
    for (int i = 1; i <= n; i++) {
        prea[i] = prea[i - 1] + a[i];
    }

    vector<int> fac(n + 1);
    vector binom(n + 1, vector<int> (n + 1, 0));
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }
    binom[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
        }
    }

    /* dp[i][j][k]
    - i: 考虑了 p[1] ~ p[i]
    - j: 有 j 个人没被录用
    - k: 选的这 i 个人中, 有 k 个 c[*] > j 的
    - dp[i][j][k]: 方案数 (c[*] > j 的贡献稍后计入)

    可以滚动数组
    */
    vector f(n + 1, vector<int> (n + 1, 0));
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            vector g(n + 1, vector<int> (n + 1, 0));
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k <= i; k++) {
                    if (f[j][k] == 0) continue;
                    // c[p[i]] <= j + 1
                    for (int t = 0; t <= a[j + 1] && t <= k; t++) {
                        add(g[j + 1][k - t], 1ll * f[j][k] * binom[a[j + 1]][t] % mod 
                                                * binom[k][t] % mod * fac[t] % mod * (prea[j + 1] - i + (k - t)) % mod);
                    }
                    // c[p[i]] > j + 1
                    for (int t = 0; t <= a[j + 1] && t <= k; t++) {
                        add(g[j + 1][k - t + 1], 1ll * f[j][k] * binom[a[j + 1]][t] % mod
                                                     * binom[k][t] % mod * fac[t] % mod);
                    }
                }
            }
            f.swap(g);
        } else {
            vector g(n + 1, vector<int> (n + 1, 0));
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k <= i; k++) {
                    if (f[j][k] == 0) continue;
                    // c[p[i]] <= j
                    for (int t = 0; t <= a[j + 1] && t <= k; t++) {
                        add(g[j + 1][k - t], 1ll * f[j][k] * binom[a[j + 1]][t] % mod 
                                                 * binom[k][t] % mod * fac[t] % mod * (prea[j] - i + k) % mod);
                    }
                    // c[p[i]] > j
                    add(g[j][k + 1], f[j][k]);
                }
            }
            f.swap(g);
        }
    }

    int ans = 0;
    for (int j = 0; j <= n - m; j++) {
        add(ans, 1ll * f[j][n - prea[j]] * fac[n - prea[j]] % mod);
    }
    cout << ans << endl;
    return 0;
}