// Seg Iterativa
//
// segtree iterativa com point update

struct Seg {
    vector<int> t;
    int n;
    Seg(vector<int>& v) {
        n = (int)v.size();
        t.resize(2 * n);
        for (int i = 0; i < n; i++) t[i + n] = v[i];
        for (int i = n - 1; i > 0; i--) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }
    int merge(int a, int b) {
        return max(a, b);
    }
    // seg[idx] = value
    void update(int p, int value) {
        for (t[p += n] = value; p >>= 1; ) t[p] = merge(t[p << 1], t[p << 1 | 1]);
    }
    int query(int l, int r) { // [l, r]
        r++;
        int res = 0; // valor neutro
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, t[l++]);
            if (r & 1) res = merge(t[--r], res);
        }
        return res;
    }
};
