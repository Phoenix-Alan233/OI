// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

constexpr double eps = 1e-6;

void sc() {
    int n, m;
    double L, V;
    cin >> n >> m >> L >> V;

    vector<array<double, 2>> car;
    for (int i = 0; i < n; i++) {
        double d, v, a;
        cin >> d >> v >> a;
        // [d1, d2]
        if (a > eps) {
            double d1 = d + max(0., (V * V - v * v) / (2 * a) + eps);
            double d2 = L;
            if (d1 <= d2) car.push_back({d1, d2});
        } else if (fabs(a) < eps) {
            double d1 = d;
            double d2 = L;
            if (d1 <= d2 && v > V) car.push_back({d1, d2});
        } else {
            double d1 = d;
            double d2 = min(d + (V * V - v * v) / (2 * a) - eps, L);
            if (d1 <= d2) car.push_back({d1, d2});
        }
    }

    vector<int> detect;
    vector<array<int, 2>> seg;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        detect.push_back(x);
    }
    sort(detect.begin(), detect.end());
    for (auto &[L, R] : car) {
        int l = lower_bound(detect.begin(), detect.end(), L) - detect.begin();
        int r = upper_bound(detect.begin(), detect.end(), R) - detect.begin() - 1;
        if (l <= r) seg.push_back({l, r});
    }
    cout << seg.size() << ' ';
    sort(seg.begin(), seg.end(), [&](auto lhs, auto rhs) {
        return lhs[1] < rhs[1];
    });
    int las = -1, cnt = 0;
    for (auto &[l, r] : seg) {
        if (l > las) {
            las = r;
            cnt++;
        }
    }
    cout << (m - cnt) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) sc();
    return 0;
}
