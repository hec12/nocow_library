//

int edit(string a, string b) {
	int n = a.size(), m = b.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

	rep(i, n + 1) dp[i][0] = i;
	rep(j, m + 1) dp[0][j] = j;

	rep(i, 1, n + 1)rep(j, 1, m + 1) {
		int cost = 1;
		if (a[i - 1] == b[j - 1]) cost = 0;
		dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
	}

	return dp[n][m];
}