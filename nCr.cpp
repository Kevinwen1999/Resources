dp[0][0] = 1;
for (int i = 1; i <= MAXN; i++){
    dp[i][0] = 1;
    for (int j = 1; j <= i; j++){
        dp[i][j] = (dp[i-1][j-1]%MOD + dp[i-1][j]%MOD)%MOD;
    }
}
