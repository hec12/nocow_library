int dp[nmax][nmax];
int C[nmax][nmax];

int main(void) {
	for (int i = 0; i <= k; ++i)
		for (int j = 0; j <= n; ++j)
			dp[i][j] = inf;
	for (int i = 0; i < n; ++i) dp[i][i] = 0, C[i][i] = i;

	for (int d = 2; d <= n; ++d) {
		for (int i = 0; i + d - 1 < n; ++i) {
			int L = i, R = i + d - 1;
			int idx = C[L][R - 1];
			for (int j = C[L][R - 1]; j <= C[L + 1][R]; ++j) {
				if (dp[L][R] > dp[L][j] + dp[j + 1][R] + cost[L][R])
					dp[L][R] = dp[L][j] + dp[j + 1][R] + cost[L][R], idx = j;
			}
			C[L][R] = idx;
		}
	}
	cout << dp[0][n - 1] << endl;
	return 0;
}