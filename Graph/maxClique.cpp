// Max Clique

// passa um grafo em bitset
// retorna os vertices que pertencem ao maior clique
// roda em 1s para n=155
// pode pegar o max independent set se passar o grafo complementar como parametro

struct Maxclique {
    double limit = 0.025, pk = 0;
    struct Vertex { int i, d = 0; };
    vector<bitset<200>> e;
    vector<Vertex> V;
    vector<vector<int>> C;
    vector<int> qmax, q, S, old;

    void init(vector<Vertex>& r) {
        for (auto& v : r) v.d = 0;
        for (auto& v : r) {
            for (auto j : r) v.d += e[v.i][j.i];
        }
        sort(r.begin(), r.end(), [](auto a, auto b) { return a.d > b.d; });
        int mxD = r[0].d;
        for (size_t i = 0; i < r.size(); ++i) r[i].d = min(static_cast<int>(i), mxD) + 1;
    }

    void expand(vector<Vertex>& R, int lev = 1) {
        S[lev] += S[lev - 1] - old[lev];
        old[lev] = S[lev - 1];
        while (!R.empty()) {
            if (q.size() + R.back().d <= qmax.size()) return;
            q.push_back(R.back().i);
            vector<Vertex> T;
            for (auto v : R) {
                if (e[R.back().i][v.i]) T.push_back({ v.i });
            }
            if (!T.empty()) {
                if (S[lev]++ / ++pk < limit) init(T);
                int j = 0, mxk = 1, mnk = max(static_cast<int>(qmax.size()) - static_cast<int>(q.size()) + 1, 1);
                C[1].clear(), C[2].clear();
                for (auto v : T) {
                    int k = 1;
                    auto f = [&](int i) { return e[v.i][i]; };
                    while (any_of(C[k].begin(), C[k].end(), f)) k++;
                    if (k > mxk) mxk = k, C[mxk + 1].clear();
                    if (k < mnk) T[j++].i = v.i;
                    C[k].push_back(v.i);
                }
                if (j > 0) T[j - 1].d = 0;
                for (int k = mnk; k < mxk + 1; ++k) {
                    for (int i : C[k]) {
                        T[j].i = i, T[j++].d = k;
                    }
                }
                expand(T, lev + 1);
            }
            else if (q.size() > qmax.size()) {
                qmax = q;
            }
            q.pop_back(), R.pop_back();
        }
    }

    vector<int> maxClique() {
        init(V);
        expand(V);
        return qmax;
    }

    Maxclique(vector<bitset<200>> conn) : e(conn), C(e.size() + 1), S(C.size()), old(S) {
        for (size_t i = 0; i < e.size(); ++i) V.push_back({ static_cast<int>(i) });
    }
};