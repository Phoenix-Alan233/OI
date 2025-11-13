// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

void sc() {
    static vector<int> last(1000001, -1);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int64_t> f(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int64_t> pre(n);
    for (int i = 1; i < n; i++) {
        pre[i] = pre[i - 1] + (a[i] == a[i - 1] ? a[i] : 0);
    }

    for (int i = 0; i < n; i++) {
        if (~last[a[i]]) {
            if (last[a[i]] == i - 1) {
                f[i] = f[i - 1] + a[i];
            } else {
                f[i] = f[last[a[i]] + 1] + a[i] + (pre[i - 1] - pre[last[a[i]] + 1]);
            }
        }
        if (i) f[i] = max(f[i], f[i - 1]);
        last[a[i]] = i;
    }
    cout << f[n - 1] << endl;
    for (int i = 0; i < n; i++) {
        last[a[i]] = -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) sc();
    return 0;
}