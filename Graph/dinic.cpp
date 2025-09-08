// Dinic
//

#define ll long long
struct Edge {
    Edge(int to, ll cap) : to(to), cap(cap) {}
    int to;
    ll cap;
};
struct Dinic {
    int n;
    vector<vector<int>> edges;
    vector<Edge> list;
    vector<int> dis, pt;

    Dinic(int _n) : n(_n) { edges.resize(n); }

    ll maxFlow(int src, int sink) {
        ll ans = 0;
        while (bfs(src, sink)) {
            // maybe random shuffle edges against bad cases?
            ll flow;
            pt.assign(n, 0);
            while ((flow = dfs(src, sink))) {
                ans += flow;
            }
        }
        return ans;
    }

    void addEdge(int from, int to, ll cap, ll other = 0) {
        edges[from].push_back(list.size());
        list.push_back(Edge(to, cap));
        edges[to].push_back(list.size());
        list.push_back(Edge(from, other));
    }

    ll dfs(int on, int sink, ll flow = 1e18) {
        if (on == sink) return flow;

        for (int& i = pt[on]; i < (int)edges[on].size(); i++) {
            int cur = edges[on][i];
            if (dis[on] + 1 != dis[list[cur].to] || list[cur].cap == 0) continue;

            ll f = dfs(list[cur].to, sink, min(flow, list[cur].cap));
            if (f) {
                list[cur].cap -= f;
                list[cur ^ 1].cap += f;
                return f;
            }
        }
        return 0;
    }

    bool bfs(int src, int sink) {
        dis.assign(n, n + 1);
        dis[src] = 0;
        queue<int> q;
        q.push(src);
        while (!q.empty()) {
            int on = q.front(); q.pop();

            for (auto a : edges[on]) {
                if (list[a].cap == 0) continue;
                int to = list[a].to;
                if (dis[to] > dis[on] + 1) {
                    dis[to] = dis[on] + 1;
                    q.push(to);
                }
            }
        }
        return dis[sink] != n + 1;
    }

    bool inCut(int u) const { return dis[u] == n + 1; }
};