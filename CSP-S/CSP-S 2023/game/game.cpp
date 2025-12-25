#include <bits/stdc++.h>
using namespace std;

const int N = 2000005;

string s;
int g[N][26]; // 决策点
long long f[N], ans;
int n;

int main() {
    cin >> n >> s;
    s = ' ' + s;
    for (int i = 1; i <= n; i++) {
        if (s[i] == s[i - 1]) {
            memcpy(g[i], g[i - 2], sizeof(g[i - 2]));
            if (i > 2) g[i][s[i - 2] - 'a'] = i - 2;
            f[i] = f[i - 2] + 1;
        } else {
            int pos = g[i - 1][s[i] - 'a'];
            if (pos == 0) continue;
            memcpy(g[i], g[pos - 1], sizeof(g[pos - 1]));
            if (pos > 1) g[i][s[pos - 1] - 'a'] = pos - 1;
            f[i] = (pos ? f[pos - 1] + 1 : 0);
        }
        ans += f[i];
        // printf("f[%d] = %lld\n", i, f[i]);
    }
    cout << ans << endl;
    return 0;
}