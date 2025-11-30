#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("candy.in", "r", stdin);
    freopen("candy.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long m;
    int n;
    cin >> n >> m;
    vector<array<long long, 2>> value;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        value.push_back({x, 1});
        value.push_back({x + y, -1});
    }
    sort(value.begin(), value.end(), [&](auto x, auto y) {
        if (x[1] == y[1]) return x[0] < y[0];
        long long k1 = (x[1] == -1 ? 1 : 2) * x[0];
        long long k2 = (y[1] == -1 ? 1 : 2) * y[0];
        return k1 < k2; 
    });
    long long cnt = 0;
    int idx = 0;
    for (auto [price, num] : value) {
        idx++;
        if (num == -1) {
            cnt += (m / price) * 2;
            m %= price;
        } else {
            if (price <= m) {
                if (idx < value.size() && value[idx][1] == -1 && value[idx][0] <= m && m < price + value[idx][0]) {
                    cnt++;
                } 
                m -= price;
                cnt++;
            }
        }
    }
    cout << cnt << endl;
    return 0;
}