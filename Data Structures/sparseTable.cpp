// Sparse Table
//

template<typename T> struct Table {
    vector<vector<T>> dp;
    int lg2(int x) { return 31 - __builtin_clz(x); } // floor log 2
    Table(const vector<T>& a) {
        int n = (int)a.size(), lgn = lg2(n);
        dp.resize(lgn + 1, vector<T>(n));
        dp[0] = a;
        for (int i = 1; i <= lgn; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T query(int l, int r) { // [l, r]
        int k = lg2(r - l + 1);
        return min(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
};

