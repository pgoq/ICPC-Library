// Centroid Decomposition

// dis[i][j] -> distancia de i para o j-esimo ancestral dele na arvore de centroid
vector<int> g[ms];
int sz[ms], dis[ms][mlg], par[ms], h[ms];
bool marked[ms];

int calc_sz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v != p && !marked[v]) sz[u] += calc_sz(v, u);
    }
    return sz[u];
}

int get_centroid(int u, int p, int tot) {
    for (int v : g[u]) {
        if (v != p && !marked[v] && (sz[v] > (tot / 2))) return get_centroid(v, u, tot);
    }
    return u;
}

void get_dist(int u, int p, const int lvl) {
    for (int v : g[u]) {
        if (v != p && !marked[v]) {
            dis[v][lvl] = dis[u][lvl] + 1;
            get_dist(v, u, lvl);
        }
    }
}

void decomp(int u, int p = -1, int lvl = 0) { // p é o pai de cent na arvore de centroid
    calc_sz(u, -1);
    int cent = get_centroid(u, -1, sz[u]);
    marked[cent] = true;
    h[cent] = lvl;
    par[cent] = p;
    get_dist(cent, -1, lvl);
    for (int v : g[cent]) {
        if (!marked[v]) decomp(v, cent, lvl + 1);
    }
}

void solve_cent(int n) {
    decomp(0);
    for (int i = 0; i < n; i++) reverse(dis[i], dis[i] + h[i] + 1);
}
