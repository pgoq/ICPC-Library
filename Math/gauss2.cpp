// Gauss Mod 2

pair<int, bitset<M>> gauss(vector<bitset<M>> eq) {
    int n = eq.size(), m = M - 1;
    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; col++) {
        for (int i = row; i < n; i++)
            if (eq[i][col]) {
                swap(eq[i], eq[row]);
                break;
            }
        if (!eq[row][col]) continue;
        where[col] = row;

        for (int i = 0; i < n; i++) {
            if (i != row && eq[i][col]) eq[i] ^= eq[row];
        }
        ++row;
    }

    bitset<M> ans;
    for (int i = 0; i < m; i++) {
        if (where[i] != -1) ans[i] = eq[where[i]][m];
    }
    for (int i = 0; i < n; i++) {
        int sum = (ans & eq[i]).count();
        sum %= 2;
        if (sum != eq[i][m]) return pair(0, bitset<M>());
    }
    for (int i = 0; i < m; i++) {
        if (where[i] == -1) return pair(INF, ans);
    }
    return pair(1, ans);
}
