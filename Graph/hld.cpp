// HLD

template<bool EDGE> struct HLD { // se for aresta, guarda valor no nó mais baixo
    int n, t;
    vector<vector<int>> g;
    vector<int> pai, rep, sz, pos, val, arr; // rep[i] = representante da chain do vertice i (nó mais alto)
    Seg seg;
    HLD(int n, const vector<vector<int>>& g, const vector<int>& val) :
        n(n), t(0), g(g), pai(n), rep(n), sz(n, 1), pos(n), val(val), arr(n) {
        calc_sz(0, -1);
        dfs(0, -1);
        seg.build(arr);
    }

    int calc_sz(int u, int p) {
        pai[u] = p;
        for (int& v : g[u]) {
            if (v == p) continue;
            sz[u] += calc_sz(v, u);
            if (sz[v] > sz[g[u][0]] || g[u][0] == p) swap(g[u][0], v);
        }
        return sz[u];
    }

    void dfs(int u, int p) {
        pos[u] = t++;
        arr[pos[u]] = val[u];
        for (int v : g[u]) {
            if (v == p) continue;
            rep[v] = (v == g[u][0] ? rep[u] : v);
            dfs(v, u);
        }
    }

    int query(int a, int b) { // query no caminho de a ate b
        int ans = 0; // valor neutro
        while (rep[a] != rep[b]) {
            if (pos[a] < pos[b]) swap(a, b);
            ans = max(ans, seg.query(pos[rep[a]], pos[a]));
            a = pai[rep[a]];
        }
        ans = max(ans, seg.query(min(pos[a], pos[b]) + EDGE, max(pos[a], pos[b])));
        return ans;
    }

    void update(int a, int x) {
        seg.update(pos[a], x);
    }
};