// Hungaro

// cost[i][j], custo de X[i] ser pareado com Y[j]
// retorna (menor custo, match ideal), onde X[i] é pareado com Y[match[i]]
// para achar maior custo, cost[i][j] = -cost[i][j]
// requer N <= M
// O(N * N * M)

pair<ll, vector<int>> hungarian(const vector<vector<ll>>& a) {
    if (a.empty()) return { 0, {} };
    int n = a.size() + 1, m = a[0].size() + 1;
    vector<ll> u(n), v(m), p(m);
    vector<int> ans(n - 1);
    for (int i = 1; i < n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<ll> dist(m, LLONG_MAX), pre(m, -1);
        vector<bool> done(m + 1);
        do {
            done[j0] = true;
            ll i0 = p[j0], j1 = -1, delta = LLONG_MAX;
            for (int j = 1; j < m; j++) {
                if (!done[j]) {
                    ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                    if (dist[j] < delta) delta = dist[j], j1 = j;
                }
            }
            for (int j = 0; j < m; j++) {
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            }
            assert(j1 != -1);
            j0 = j1;
        } while (p[j0]);
        while (j0) {
            int j1 = pre[j0];
            p[j0] = p[j1], j0 = j1;
        }
    }
    for (int j = 1; j < m; j++) {
        if (p[j]) ans[p[j] - 1] = j - 1;
    }
    return { -v[0], ans }; // min cost
}
