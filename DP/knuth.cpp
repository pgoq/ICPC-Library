// Knuth
// dp[i][j] = min{dp[i][k] + dp[k][j]} + cost[i][j]
//              i < k < j
// pode usar se opt[i][j-1] <= opt[i][j] <= opt[i+1][j]

int n, opt[ms][ms];
ll dp[ms][ms];
void knuth() {
    for (int i = n; i >= 0; i--) { // limites entre 0 e n
        dp[i][i + 1] = 0; opt[i][i + 1] = i; // caso base
        for (int j = i + 2; j <= n; j++) {
            dp[i][j] = inf; // long long inf
            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
                if (dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    opt[i][j] = k;
                }
            }
            dp[i][j] += c(i, j); // custo associado ao intervalo [i, j]
        }
    }
}