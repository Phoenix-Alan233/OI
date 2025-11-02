// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

void sc() {
    int n;
    scanf("%d", &n);

    vector<array<int, 3>> a(n);
    vector<int> pick(n);
    int cnt[3] = {0};
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        a[i] = {x, y, z};
        if (x >= y && x >= z) pick[i] = 0, cnt[0]++, ans += x;
        else if (y >= x && y >= z) pick[i] = 1, cnt[1]++, ans += y;
        else pick[i] = 2, cnt[2]++, ans += z;
    }

    int pos = max_element(cnt, cnt + 3) - cnt;
    if (cnt[pos] > n / 2) {
        int ban = cnt[pos] - n / 2;
        vector<int> candidate;
        for (int i = 0; i < n; i++) {
            if (pick[i] == pos) {
                int cur_val = 0;
                for (int j = 0; j < 3; j++) {
                    if (j != pos && a[i][j] > cur_val) {
                        cur_val = a[i][j];
                    }
                }
                candidate.push_back(cur_val - a[i][pos]);
            }
        }
        sort(candidate.begin(), candidate.end(), greater<int>());
        for (int i = 0; i < ban; i++) {
            ans += candidate[i];
        }
    }

    printf("%lld\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) sc();
    return 0;
}