// Mo Update
//
// Q*((2 * N * N)^(1/3)) * F
const int B = 2700; // Block size = (2 * N * N) ^ (1/3)
struct MoUpdate {
    struct Query {
        int l, r, t, idx; // [l, r], t representa quantos updates tiveram antes dessa query, idx é o indice da query
        Query(int l, int r, int t, int idx) : l(l), r(r), t(t), idx(idx) {}
        bool operator < (const Query& p) const {
            if (l / B != p.l / B) return l < p.l;
            if (r / B != p.r / B) return r < p.r;
            return t < p.t;
        }
    };
    struct Update {
        int i, old, now;
        Update(int i, int old, int now) : i(i), old(old), now(now) {}
    };

    vector<Query> queries;
    vector<Update> updates;

    void addQuery(int l, int r, int t, int idx) { queries.push_back(Query(l, r, t, idx)); } // t = quantos updates tiveram antes dessa query
    void addUpdate(int i, int old, int now) { updates.push_back(Update(i, old, now)); }

    void add(int x) {} // F
    void rem(int x) {} // F
    int getAns() {}
    void update(int novo, int idx, int l, int r) {
        if (l <= idx && idx <= r) rem(idx);
        arr[idx] = novo;
        if (l <= idx && idx <= r) add(idx);
    }

    void solve() {
        int l = 0, r = -1, t = 0;
        sort(queries.begin(), queries.end());
        for (Query q : queries) {
            while (l > q.l) add(--l);
            while (r < q.r) add(++r);
            while (l < q.l) rem(l++);
            while (r > q.r) rem(r--);
            while (t < q.t) {
                auto u = updates[t++];
                update(u.now, u.i, l, r);// troca o valor de arr[i] para u.now (antes tava como u.old)
            }
            while (t > q.t) {
                auto u = updates[--t];
                update(u.old, u.i, l, r); // troca o valor de arr[i] para u.old (antes tava como u.now)
            }
            ans[q.idx] = getAns();
        }
    }
};