// LCA

int par[ms][mlg + 1], lvl[ms];
void dfs(int u, int p, int l = 0) { // chamar como dfs(root, root)
    lvl[u] = l;
    par[u][0] = p;
    for (int k = 1; k <= mlg; k++) {
        par[u][k] = par[par[u][k - 1]][k - 1];
    }
    for (int v : g[u]) {
        if (v != p) dfs(v, u, l + 1);
    }
}
int lca(int a, int b) {
    if (lvl[b] > lvl[a]) swap(a, b);
    for (int i = mlg; i >= 0; i--) {
        if (lvl[a] - (1 << i) >= lvl[b]) a = par[a][i];
    }
    if (a == b) return a;
    for (int i = mlg; i >= 0; i--) {
        if (par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    }
    return par[a][0];
}