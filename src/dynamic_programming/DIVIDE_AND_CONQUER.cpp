int dp[kmax][nmax];
void solve(int i, int L, int R, int optL, int optR) {
	if (L > R) return;
	int M = (L + R) / 2;
	int optM = -1;
	for (int k = optL; k <= optR; ++k)
		if (dp[i + 1][M] > dp[i][k] + cost[k][M])
			dp[i + 1][M] = dp[i][k] + cost[k][M]	, optM = k;
	solve(i, L, M, optL, optM);
	solve(i, M, R, optM, optR);
	return;
}

int main(void) {
	for (int i = 0; i <= k; ++i)
		for (int j = 0; j <= n; ++j)
			dp[i][j] = inf;
	dp[0][0] = 0;
	for (int i = 0; i < k; ++i) solve(i, 0, n, 0, n);
	cout << dp[k][n] << endl;
	return 0;
}