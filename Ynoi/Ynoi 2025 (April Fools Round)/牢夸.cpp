// Author: Alan233
#include <bits/stdc++.h>
using namespace std;

namespace IO {
    const int SIZE = 1 << 20;
    char ibuf[SIZE]; int iS, iT;
    char obuf[SIZE]; int oT;
    inline char gc() {
        if (iS == iT) iS = 0, iT = fread(ibuf, 1, SIZE, stdin);
        return iS == iT ? EOF : ibuf[iS++];
    }
    inline void pc(char c) {
        obuf[oT++] = c;
        if (oT == SIZE) fwrite(obuf, 1, SIZE, stdout), oT = 0;
    }
    inline int read() {
        int x = 0, f = 0;
        char c = gc();
        while (!isdigit(c)) f |= c == '-', c = gc();
        while (isdigit(c)) x = 10 * x + c - '0', c = gc();
        return f ? -x : x;
    }
    inline void print(int64_t x) {
        static char buf[64];
        int len = 0;
        if (x < 0) pc('-'), x = -x;
        do { buf[++len] = x % 10 + '0', x /= 10; } while (x);
        while (len) pc(buf[len--]);
    }
    inline void print(int64_t x, char ch) {
        print(x), pc(ch);
    }
    struct Flusher {
        ~Flusher() {
            if (oT) fwrite(obuf, 1, oT, stdout);
        }
    } flusher;
}

struct fraction {
    int64_t fz, fm;
    fraction(int64_t _fz, int64_t _fm) {
        int t = __gcd(_fz, _fm);
        _fz /= t, _fm /= t;
        if (_fm < 0) _fz = -_fz, _fm = -_fm;
        fz = _fz, fm = _fm;
    }
    bool operator<(const fraction &b) const {
        return fz * b.fm < fm * b.fz;
    }
};

struct SegNode {
    int l, r;
    int64_t x, tag;
    SegNode *ls, *rs;
    SegNode(int _l, int _r) {
        l = _l, r = _r;
        x = tag = 0;
        ls = rs = nullptr;
    }
};

struct SegTree {
    SegNode *root;
    int type;
    SegTree() {}
    void push(SegNode *u) {
        if (u->tag) {
            u->ls->tag += u->tag;
            u->ls->x += u->tag;
            u->rs->tag += u->tag;
            u->rs->x += u->tag;
            u->tag = 0;
        }
    }
    void pull(SegNode *u) {
        if (u->ls->x > u->rs->x)
            u->x = u->ls->x;
        else
            u->x = u->rs->x;
    }
    void build(SegNode *u, vector<int> &a) {
        if (u->l == u->r) {
            int64_t x = 0;
            for (int t = u->l; t < u->l + type && t < a.size(); t++) {
                x += a[t];
            }
            u->x = x;
            return;
        }
        int mid = (u->l + u->r) >> 1;
        u->ls = new SegNode(u->l, mid);
        build(u->ls, a);
        u->rs = new SegNode(mid + 1, u->r);
        build(u->rs, a);
        pull(u);
    }
    void update(SegNode *u, int l, int r, int x) {
        if (l > r || l > u->r || r < u->l) return;
        if (l <= u->l && u->r <= r) {
            u->x += x;
            u->tag += x;
            return;
        }
        push(u);
        int mid = (u->l + u->r) >> 1;
        if (l <= mid) update(u->ls, l, r, x);
        if (r > mid) update(u->rs, l, r, x);
        pull(u);
    }
    int64_t query(SegNode *u, int l, int r) {
        if (l <= u->l && u->r <= r) {
            return u->x;
        }
        push(u);
        int mid = (u->l + u->r) >> 1;
        int64_t res = INT64_MIN;
        if (l <= mid) res = max(res, query(u->ls, l, r));
        if (r > mid) res = max(res, query(u->rs, l, r));
        return res;
    }
};

int main() {
    int n = IO::read(), m = IO::read();
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = IO::read();

    SegTree *tree1 = new SegTree(), *tree2 = new SegTree();
    tree1->root = new SegNode(0, n - 1);
    tree1->type = 2;
    tree1->build(tree1->root, a);

    tree2->root = new SegNode(0, n - 1);
    tree2->type = 3;
    tree2->build(tree2->root, a);

    while (m--) {
        int opt = IO::read(), l = IO::read(), r = IO::read();
        l--, r--;
        if (opt == 1) {
            int x = IO::read();
            // tree1
            tree1->update(tree1->root, l - 1, l - 1, x);
            tree1->update(tree1->root, l, r - 1, 2 * x);
            tree1->update(tree1->root, r, r, x);
            // tree2
            if (l == r) {
                tree2->update(tree2->root, max(0, l - 2), l, x);
            } else {
                tree2->update(tree2->root, l - 2, l - 2, x);
                tree2->update(tree2->root, l - 1, l - 1, 2 * x);
                tree2->update(tree2->root, l, r - 2, 3 * x);
                tree2->update(tree2->root, r - 1, r - 1, 2 * x);
                tree2->update(tree2->root, r, r, x);
            }
        } else {
            fraction ans = fraction(tree1->query(tree1->root, l, r - 1), 2);
            if (l <= r - 2) {
                fraction ans2 = fraction(tree2->query(tree2->root, l, r - 2), 3);
                if (ans < ans2) ans = ans2;
            }
            IO::print(ans.fz), IO::pc('/'), IO::print(ans.fm, '\n');
        }
    }
    return 0;
}