// Min Cost Max Flow

// #include <ext/pb_ds/priority_queue.hpp>
// #include <bits/extc++.h> /// include-line, keep-include

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct edge {
        int from, to, rev;
        ll cap, cost, flow;
    };
    int N;
    vector<vector<edge>> ed;
    vector<int> seen, vis;
    vector<ll> dist, pi;
    vector<edge*> par;

    MCMF(int N) : N(N), ed(N), seen(N), vis(N), dist(N), pi(N), par(N) {}

    void addEdge(int from, int to, ll cap, ll cost) { // aresta de retorno tem cap = 0
        if (from == to || cap == 0) return;
        ed[from].push_back(edge{ from,to, (int)ed[to].size(),cap,cost,0 });
        ed[to].push_back(edge{ to,from,(int)ed[from].size() - 1,0,-cost,0 });
    }

    void path(int s) {
        fill(seen.begin(), seen.end(), 0);
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        ll di;
        __gnu_pbds::priority_queue<pair<ll, int>> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({ 0, s });

        while (!q.empty()) {
            s = q.top().second; q.pop();
            seen[s] = 1; di = dist[s] + pi[s];
            for (edge& e : ed[s]) {
                if (!seen[e.to]) {
                    ll val = di - pi[e.to] + e.cost;
                    if (e.cap - e.flow > 0 && val < dist[e.to]) {
                        dist[e.to] = val;
                        par[e.to] = &e;
                        if (its[e.to] == q.end()) {
                            its[e.to] = q.push({ -dist[e.to], e.to });
                        }
                        else {
                            q.modify(its[e.to], { -dist[e.to], e.to });
                        }
                    }
                }
            }
        }
        for (int i = 0; i < N; i++) {
            pi[i] = min(pi[i] + dist[i], INF);
        }
    }

    pair<ll, ll> maxflow(int s, int t) {
        setpi(s, t);
        ll totflow = 0, totcost = 0;
        while (path(s), seen[t]) {
            ll fl = INF;
            for (edge* x = par[t]; x; x = par[x->from]) {
                fl = min(fl, x->cap - x->flow);
            }
            totflow += fl;
            for (edge* x = par[t]; x; x = par[x->from]) {
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        for (int i = 0; i < N; i++) {
            for (edge& e : ed[i]) {
                totcost += e.cost * e.flow;
            }
        }
        return { totflow, totcost / 2 };
    }

    // If some costs can be negative, call this before maxflow:
    void setpi(int s, int t) { // if graph is a DAG pi can be calculated with DP instead of Bellman ford
        fill(pi.begin(), pi.end(), INF);
        pi[s] = 0;
        int it = N, ch = 1;
        ll v;
        while (ch-- && it--) {
            for (int i = 0; i < N; i++) {
                if (pi[i] != INF) {
                    for (edge& e : ed[i]) {
                        if (e.cap) {
                            if ((v = pi[i] + e.cost) < pi[e.to]) {
                                pi[e.to] = v, ch = 1;
                            }
                        }
                    }
                }
            }
        }
        assert(it >= 0); // negative cost cycle
    }
};