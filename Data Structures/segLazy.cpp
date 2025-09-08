// Seg Lazy
//

struct Seg {
    vector<int> seg, lazy;
    int n;
    Seg(int n) : n(n), seg(4 * n), lazy(4 * n) {}

    int merge(int a, int b) {
        return a + b;
    }

    void build(vector<int>& v, int l, int r, int idx) {
        if (l == r) {
            seg[idx] = v[l];
            return;
        }
        int mid = (l + r) / 2;
        build(v, l, mid, 2 * idx + 1), build(v, mid + 1, r, 2 * idx + 2);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    void apply(int l, int r, int idx) {
        if (lazy[idx] == 0) return;
        if (l != r) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        seg[idx] += (r - l + 1) * lazy[idx];
        lazy[idx] = 0;
    }

    void update(int L, int R, int x, int l, int r, int idx) {
        apply(l, r, idx);
        if (l > R || r < L) return;
        if (L <= l && r <= R) {
            lazy[idx] += x;
            apply(l, r, idx);
            return;
        }
        int mid = (l + r) / 2;
        update(L, R, x, l, mid, 2 * idx + 1);
        update(L, R, x, mid + 1, r, 2 * idx + 2);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    int query(int L, int R, int l, int r, int idx) {
        apply(l, r, idx);
        if (l > R || r < L) return 0; // valor neutro
        if (L <= l && r <= R) return seg[idx];
        int mid = (l + r) / 2;
        return merge(query(L, R, l, mid, 2 * idx + 1), query(L, R, mid + 1, r, 2 * idx + 2));
    }

    void build(vector<int>& v) {
        build(v, 0, n - 1, 0);
    }
    void update(int L, int R, int x) {
        update(L, R, x, 0, n - 1, 0);
    }
    int query(int L, int R) {
        return query(L, R, 0, n - 1, 0);
    }
};