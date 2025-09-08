// Euler Path
//

vector<ii> eulerPath(const vector<vector<ii>>& g, int nedges, int src) {
    int n = g.size();
    vector<int> deg(n, 0), its(n, 0), used(nedges + 1, 0);
    vector<ii> s = { {src, -1} };  // nó, indice da aresta que ele veio
    //deg[src]++; // para permitir paths, não só circuitos
    vector<ii> ret;
    while (!s.empty()) {
        int u = s.back().first, & it = its[u];
        if (it == g[u].size()) {
            ret.push_back(s.back());
            s.pop_back();
            continue;
        }
        auto& [nxt, id] = g[u][it++];
        if (!used[id]) {
            deg[u]--, deg[nxt]++;
            used[id] = 1;
            s.push_back({ nxt, id });
        }
    }

    for (int x : deg) {
        if (x < 0 || ret.size() != (nedges + 1)) return {};
    }
    reverse(ret.begin(), ret.end());
    return ret;
}
