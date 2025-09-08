// Bridges
//

vector<int> g[ms];
int low[ms], tin[ms];
bool vis[ms];
int t;

void dfs(int u = 0, int p = -1) {
    vis[u] = true;
    low[u] = tin[u] = t++;
    for (auto v : g[u]) {
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);
        }
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) { // (low[v] >= tin[u] && p != -1), eh ponto de articulacao
                // eh ponte
            }
            // children++
        }
    }
    // if(children > 1 && p == -1) raiz é um ponto de articulação
}
