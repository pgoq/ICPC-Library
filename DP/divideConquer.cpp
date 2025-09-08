// Divide and Conquer DP

// O(m n log n)
// nesse caso eu to mantendo o custo, mas eh possivel que o custo seja calculado na hora tambem
// ta tudo 1-based aqui
// condicao pra usar: opt[i][j] <= opt[i][j+1]
int dp[MAXM][MAXN]; // da p otimizar memoria aqui usando so duas linhas
int arr[MAXN];

void add(int idx) {}
void rem(int idx) {}

void divideConquer(int i, int l, int r, int optL, int optR) { // mantenho o custo [optL, r]
    if (l > r) return;
    int j = (l + r) / 2;

    for (int k = r; k > j; k--) rem(k); // cost = custo[optL, j]
    int opt = optL;
    for (int k = optL; k <= min(optR, j); k++) {
        int val = dp[i - 1][k - 1] + cost; // custo [k, j]
        if (val < dp[i][j]) {
            dp[i][j] = val;
            opt = k;
        }
        rem(k);
    }
    // cost =  custo[min(optR, j) + 1, j]
    for (int k = min(optR, j); k >= optL; k--) add(k); // cost = custo[optL, j]
    rem(j); // cost = custo[optL, j-1]
    divideConquer(i, l, j - 1, optL, opt);

    for (int k = j; k <= r; k++) add(k); // cost = custo[optL, r]
    for (int k = optL; k < opt; k++) rem(k); // cost = custo[opt, r]
    divideConquer(i, j + 1, r, opt, optR);

    for (int k = optL; k < opt; k++) add(k); // cost = custo[optL, r]
}

int solve(int N, int M) { // 1-based
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = inf; // CASO BASE
        }
    }
    cost = 0; // valor neutro
    for (int i = 1; i <= N; i++) add(i);
    for (int i = 1; i <= M; i++) {
        divideConquer(i, 1, N, 1, N);
    }
    return dp[M][N];
}
