// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

bool one_move(const array<int, 5>& p, const array<int, 5>& s) {
    int d[5];
    for (int i = 0; i < 5; i++) {
        d[i] = (s[i] - p[i] + 10) % 10;
    }

    // 统计非 0 的位置
    vector<int> nz;
    for (int i = 0; i < 5; i++) {
        if (d[i] != 0) nz.push_back(i);
    }

    // 情况 1：只动一个拨圈
    if (nz.size() == 1) {
        return true;
    }

    // 情况 2：动两个相邻拨圈，幅度相同
    if (nz.size() == 2) {
        int i = nz[0], j = nz[1];
        if (j == i + 1 && d[i] == d[j]) {
            return true;
        }
    }

    return false;
}

int main() {
    int n;
    scanf("%d", &n);

    vector<array<int, 5>> a(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int ans = 0;

    // 枚举正确密码
    for (int x = 0; x < 100000; x++) {
        array<int, 5> p;
        int t = x;
        for (int i = 4; i >= 0; i--) {
            p[i] = t % 10;
            t /= 10;
        }

        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (!one_move(p, a[i])) {
                ok = false;
                break;
            }
        }

        if (ok) ans++;
    }

    printf("%d\n", ans);
    return 0;
}
