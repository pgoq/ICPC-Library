// Tree Hash

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ull uniform(ull l, ull r) { // [l, r]
    uniform_int_distribution<ull> uid(l, r);
    return uid(rng);
}

const ull FIXED_RANDOM = uniform(1, UINT64_MAX);

struct TreeHash {
    int n;
    vector<vector<int>> g;
    ii cent;
    pair<ull, ull> hash;
    vector<int> sz;
    TreeHash(int n, vector<vector<int>>& g) : n(n), g(g), sz(n, 1) {
        dfs_sz(0, -1);
        cent = ii(-1, -1);
        get_cent(0, -1);
        if (cent.second == -1) cent.second = cent.first;
        hash = { get_hash(cent.first, -1), get_hash(cent.second, -1) };
        if (hash.first > hash.second) swap(hash.first, hash.second);
    }
    int dfs_sz(int u, int p) {
        for (int v : g[u]) {
            if (v != p) {
                sz[u] += dfs_sz(v, u);
            }
        }
        return sz[u];
    }
    void get_cent(int u, int p) {
        int maxi = n - sz[u];
        for (int v : g[u]) {
            if (v == p) continue;
            get_cent(v, u);
            maxi = max(maxi, sz[v]);
        }
        if (maxi <= (n / 2)) {
            cent.second = u;
            swap(cent.first, cent.second);
        }
    }
    ull hashify(ull sum) {
        sum += FIXED_RANDOM;
        sum += 0x9e3779b97f4a7c15;
        sum = (sum ^ (sum >> 30)) * 0xbf58476d1ce4e5b9;
        sum = (sum ^ (sum >> 27)) * 0x94d049bb133111eb;
        return sum ^ (sum >> 31);
    }
    ull get_hash(int u, int p) {
        ull sum = 0;
        for (int v : g[u]) {
            if (v == p) continue;
            sum += get_hash(v, u);
        }
        return hashify(sum);
    }
};
