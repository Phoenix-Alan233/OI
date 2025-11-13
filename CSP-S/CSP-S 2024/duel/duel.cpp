// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int a[100001], n;
    memset(a, 0, sizeof(a));
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x; a[x]++;
    }
    int ans = 0, kill = 0;
    for (int i = 100000; i >= 1; i--) {
        ans += min(kill, a[i]);
        kill = max(kill, a[i]);
    }
    cout << n - ans << endl;
    return 0;
}