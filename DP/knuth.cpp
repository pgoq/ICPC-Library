// Knuth

// dp[i][j] = min{dp[i][k] + dp[k][j]} + cost[i][j]
//              i < k < j
// pode usar se opt[i][j-1] <= opt[i][j] <= opt[i+1][j]

ll solve(int i, int j){
    if(i >= j) return 0ll;
    ll &ans = dp[i][j];
    if(~ans) return ans;
    solve(i, j-1);
    solve(i+1, j);
    int optL = (opt[i][j-1] == -1 ? 0 : opt[i][j-1]);
    int optR = (opt[i+1][j] == -1 ? n-1 : opt[i+1][j]);
    ans = INF;
    for(int k=max(i, optL); k<=min(j-1, optR); k++){
        ll now = solve(i, k) + solve(k+1, j) + cost(i, j);
        if(now <= ans){
            opt[i][j] = k;
            ans = now;
        }
    }
    return ans;
}

ll knuth(){
    memset(opt, -1, sizeof opt);
    for(int i=n-1; i>=0; i--){
        dp[i][i] = 0; // caso base
        opt[i][i] = i;
        for(int j=i+1; j<n; j++){
            int optL = (((j == 0) || opt[i][j-1] == -1) ? 0 : opt[i][j-1]);
            int optR = (opt[i+1][j] == -1 ? n-1 : opt[i+1][j]);
            ll cst = cost(i, j);
            dp[i][j] = INF;
            for(int k=max(i, optL); k<=min(j-1, optR); k++){
                ll now = dp[i][k] + dp[k+1][j] + cst;
                if(now <= dp[i][j]){
                    dp[i][j] = now;
                    opt[i][j] = k;
                }
            }
        }
    }
    return dp[0][n-1];
}