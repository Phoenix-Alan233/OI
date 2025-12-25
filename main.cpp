#include <bits/stdc++.h>
using namespace std;

const int N = 4000;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

uint64_t value[N];

struct SAM {
    vector<int> adj[3 * N];
    int ch[3 * N][27], fail[3 * N], len[3 * N], tag[3 * N];
    
    uint64_t endpos[3 * N];
    unordered_map<uint64_t, int> f;

    int tot, last;

    SAM() {
        memset(ch, 0, sizeof(ch));
        memset(fail, 0, sizeof(fail));
        memset(len, 0, sizeof(len));
        memset(tag, 0, sizeof(tag));
        memset(endpos, 0, sizeof(endpos));
        tot = last = 1;
    }

    void extend(int x, int pos) {
        int u = last; last = ++tot;
        len[last] = len[u] + 1;
        endpos[last] = value[pos];
        for (; !ch[u][x]; u = fail[u]) ch[u][x] = last;
        if (!u) {
            fail[last] = 1;
            return;
        }
        int v = ch[u][x];
        if (len[v] == len[u] + 1) {
            fail[last] = v;
            return;
        }
        int w = ++tot;
        len[w] = len[u] + 1, fail[w] = fail[v];
        memcpy(ch[w], ch[v], sizeof(ch[v]));
        fail[v] = fail[last] = w;
        for (; ch[u][x] == v; u = fail[u]) ch[u][x] = w; 
    }

    void dfs(int u) {
        for (auto v : adj[u]) {
            dfs(v);
            endpos[u] += endpos[v];
        }
        f[endpos[u]] = u;
    }

    void build() {
        for (int i = 1; i <= tot; i++) {
            tag[i] = len[i];
        }
        for (int i = 2; i <= tot; i++) {
            adj[fail[i]].push_back(i);
        }
        dfs(1);
    }

    int getans() {
        int ans = 0;
        for (int i = 2; i <= tot; i++) {
            ans += max(0, tag[i] - len[fail[i]]);
        }
        return ans;
    }
} sam_init;

char s[N], s_init[N];
int n, n_init, q;

void run(SAM &sam, int u, int fa) {
    if (sam_init.f.count(sam.endpos[u])) {
        int node = sam_init.f[sam.endpos[u]];
        sam_init.tag[node] = min(sam_init.tag[node], sam.len[fa]);
    }
    for (auto v : sam.adj[u]) {
        run(sam, v, u);
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        value[i] = rng();
    }

    scanf("%s", s);
    n = strlen(s);
    
    memcpy(s_init, s, sizeof(s));
    n_init = n;
    for (int i = 0; i < n_init; i++) {
        sam_init.extend(s_init[i] - 'a', i);
    }
    sam_init.build();

    scanf("%d", &q);
    while (q--) {
        char opt;
        scanf("%*[^IDQ]%c", &opt);
        if (opt == 'I') {
            int x;
            char c;
            scanf("%d %c", &x, &c);
            for (int i = n; i > x; i--) s[i] = s[i - 1];
            s[x] = c;
            ++n;
        } else if (opt == 'D') {
            int x;
            scanf("%d", &x);
            for (int i = x; i < n - 1; i++) s[i] = s[i + 1];
            --n;
        } else {
            printf("%d\n", sam_init.getans());
        }

        if (opt != 'Q') {
            SAM sam;
            for (int i = 0; i < n_init; i++) {
                sam.extend(s_init[i] - 'a', i);
            }
            sam.extend(26, n_init);
            for (int i = 0; i < n; i++) {
                sam.extend(s[i] - 'a', i + n_init + 1);
            }
            sam.build();
            run(sam, 1, 0);
        }
    }
    return 0;
}

/*
gzuow
2
I 4 o
Q
*/

// gzuow
// gzuoow

// g z u o w
// gz zu uo ow
// gzu zuo
// gzuo