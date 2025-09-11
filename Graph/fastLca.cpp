// Fast LCA

struct LCA {
    int T = 0;
    vector<int> time, path, ret;
    Table<int> rmq;

    LCA(vector<vector<int>>& C) : time(size(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vector<int>>& C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};