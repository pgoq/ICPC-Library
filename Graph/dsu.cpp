// DSU 
//
struct Dsu {
    vector<int> sz, ds;
    vector<pair<int, int>> changes;
    int cnt_cmp;
    Dsu(int n) : sz(n, 1), ds(n), cnt_cmp(n) {
        iota(ds.begin(), ds.end(), 0);
    }
    int find(int i) {
        return (i == ds[i] ? i : find(ds[i]));
    }
    void merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) {
            changes.push_back({ -1, -1 });
            return;
        }
        cnt_cmp--;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        ds[b] = a;
        changes.push_back({ a, b });
    }
    void rollback() {
        assert(!changes.empty());
        auto [a, b] = changes.back();
        changes.pop_back();
        if (a == -1) return;
        cnt_cmp++;
        sz[a] -= sz[b];
        ds[b] = b;
    }
};
