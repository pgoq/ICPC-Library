// Seg Persistente
//

struct SegPersitente {
    struct Node {
        ll v; // comecar com valor neutro
        int l, r;
        Node(ll v = 0, int l = 0, int r = 0) : v(v), l(l), r(r) {}
    };
    vector<Node> seg;
    int n, CNT;
    SegPersitente(int _n, int upd) : seg(20 * (upd + _n)), n(_n), CNT(1) {}
    ll merge(ll a, ll b) {
        return a + b;
    }
    int update(int root, int pos, int val, int l, int r) {
        int idx = CNT++;
        seg[idx] = seg[root];
        if (l == r) {
            seg[idx].v += val;
            return idx;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            seg[idx].l = update(seg[idx].l, pos, val, l, mid);
        }
        else seg[idx].r = update(seg[idx].r, pos, val, mid + 1, r);
        seg[idx].v = merge(seg[seg[idx].l].v, seg[seg[idx].r].v);
        return idx;
    }
    int query(int idx, int L, int R, int l, int r) {
        if (l > R || r < L) return 0; // valor neutro
        if (L <= l && r <= R) return seg[idx].v;
        int mid = (l + r) / 2;
        return merge(query(seg[idx].l, L, R, l, mid), query(seg[idx].r, L, R, mid + 1, r));
    }
    int update(int root, int pos, int val) {
        return update(root, pos, val, 0, n - 1);
    }
    int query(int root, int L, int R) {
        return query(root, L, R, 0, n - 1);
    }
};
