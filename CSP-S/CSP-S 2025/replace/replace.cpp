// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

struct node {
    int cnt;
    node *fail, *son[27];
    node() {
        cnt = 0;
        fail = nullptr;
        for (int i = 0; i <= 26; i++) son[i] = nullptr;
    }
};

struct ACAM {
    node *root;
    ACAM() { root = new node(); }
    void insert(string s) {
        node *p = root;
        for (int i = 0; i < s.size(); i++) {
            int id = (s[i] == '$' ? 26 : s[i] - 'a');
            if (p->son[id] == nullptr) p->son[id] = new node();
            p = p->son[id];
        }
        p->cnt++;
    }

    void build() {
        queue<node *> q;
        root->fail = root;
        for (int i = 0; i <= 26; i++) {
            if (root->son[i] != nullptr) {
                q.push(root->son[i]);
                root->son[i]->fail = root;
            } else {
                root->son[i] = root;
            }
        }
        while (!q.empty()) {
            node *u = q.front(); q.pop();
            u->cnt += u->fail->cnt;
            for (int i = 0; i <= 26; i++) {
                if (u->son[i] != nullptr) {
                    q.push(u->son[i]);
                    u->son[i]->fail = u->fail->son[i];
                } else {
                    u->son[i] = u->fail->son[i];
                }
            }
        }
    }

    long long query(string s) {
        node *p = root;
        long long res = 0;
        for (int i = 0; i < s.size(); i++) {
            int id = (s[i] == '$' ? 26 : s[i] - 'a');
            p = p->son[id];
            res += p->cnt;
        }
        return res;
    }
};

const int mod = 998244353;
const int base = 137;

int getHash(string s) {
    int hash_value = 0;
    for (char c : s) {
        hash_value = (1ll * hash_value * base + (c - 'a')) % mod;
    }
    return hash_value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    map<long long, ACAM *> f;
    int fid = 0;

    for (int i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        long long hash_value;
        string s;
        if (s1 == s2) {
            s = s1;
            hash_value = 0;
        } else {
            int l = 0, r = s1.size() - 1;
            while (s1[l] == s2[l]) l++;
            while (s1[r] == s2[r]) r--;
            s = s1.substr(0, l) + '$' + s1.substr(r + 1);
            hash_value = 1ll * getHash(s1.substr(l, r - l + 1)) * mod + getHash(s2.substr(l, r - l + 1));
        }
#ifdef LOCAL
        cout << hash_value << " " << s << "\n";
#endif
        if (!f.count(hash_value)) {
            f[hash_value] = new ACAM();
        }
        f[hash_value]->insert(s);
    }
    for (auto &it : f) {
        it.second->build();
    }

    while (q--) {
        string t1, t2;
        cin >> t1 >> t2;
        if (t1.size() != t2.size()) {
            cout << "0\n";
            continue;
        }
        long long hash_value;
        string t;
        if (t1 == t2) {
            t = t1;
            hash_value = 0;
        } else {
            int l = 0, r = t1.size() - 1;
            while (t1[l] == t2[l]) l++;
            while (t1[r] == t2[r]) r--;
            t = t1.substr(0, l) + '$' + t1.substr(r + 1);
            hash_value = 1ll * getHash(t1.substr(l, r - l + 1)) * mod + getHash(t2.substr(l, r - l + 1));
        }
#ifdef LOCAL
        cout << hash_value << " " << t << "\n";
#endif
        if (!f.count(hash_value)) {
            cout << "0\n";
            continue;
        }
        cout << f[hash_value]->query(t) << '\n';
    }
    return 0;
}