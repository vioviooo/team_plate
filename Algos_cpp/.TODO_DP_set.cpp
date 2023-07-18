#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
!!
using namespace std;
const int INF = 1e9;
vector<vector<int>> g;
vector<vector<int>> dp;
const int M = 100;
//const int M = 4;
using bs = bitset<M>;
using ll = long long;
const ll MOD = 1e9 + 7;
//ДП по профилю. Надо разобраться
int solve(int i, int mask, int n) {
	if (dp[i][mask] == -1) {
		return dp[i][mask];
	}
	int res = INF;
	int mask2 = mask ^ (1 << i);
	for (int j = 0; j < n; j++) {
		if (0 == (mask2 & (1 << j))) {
			continue;
		}
		res = min(res, g[j + 1][i + 1] + solve(j, mask2, n));
	}
	dp[i][mask] = res;
	return res;
}
void forsolve() {
	int n = 22;
	cin >> n;
	g.resize(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
		}
	}
	int m = n - 1;
	dp.resize(m, vector<int>(1 << (m), -1));
	for (int i = 0; i < m; i++) {
		dp[i][1 << (i)] = g[0][i + 1];
	}
	int ans = INF;
	for (int i = 0; i < m; i++) {
		ans = min(ans, solve(i, (1 << m) - 1, m));
	}
	cout << ans << endl;
}
bool compat(int mask1, int mask2, int m) {
	bs m1(mask1), m2(mask2);
	for (int i = 0; i < m - 1; i++) {
		if (m1[i] == m1[i + 1] && m1[i] == m2[i] && m2[i] == m2[i + 1]) {
			return false;
		}
	}
	return true;
}
bool compat2(int mask1, int mask2, int m) {
	bs m1(mask1), m2(mask2);
	for (int i = 0; i < m; i++) {
		if (m1[i] == 0) {
			if (m2[i] == 1) {
				m2[i] = 0;
			}
			else {
				return false;
			}
		}
	}
}
void forcompat() {
	int n = 1000, m = 8;
	cin >> n >> m;
	int full_mask = 1 << m;
	vector<ll> dp_prev(full_mask, 1);
	vector<ll> dp_next(full_mask);
	vector<vector<ll>> memo(full_mask, vector<ll>(full_mask));
	for (int i = 0; i < full_mask; i++) {
		for (int j = 0; j < full_mask; j++) {
			memo[i][j] = compat2(i, j, m);
		}
	}
	for (int i = 2; i <= n; i++) {
		dp_next.assign(full_mask, 0);
		for (int mask2 = 0; mask2 < full_mask; mask2++) {
			for (int mask1 = 0; mask1 < full_mask; mask1++) {
				dp_next[mask2] = (dp_next[mask2] + dp_prev[mask1] * memo[mask1][mask2]) % MOD;

			}
		}
		swap(dp_prev, dp_next);
	}
	ll ans = 0;
	for (int i = 0; i < full_mask; i++) {
		ans = (ans + dp_prev[i]) % MOD;
	}
	cout << ans << endl;
}

void forcompat2() {
	int n = 1000, m = 8;
	cin >> n >> m;
	int full_mask = 1 << m;
	vector<ll> dp_prev(full_mask, 1);
	dp_prev[full_mask - 1] = 1;
	vector<ll> dp_next(full_mask);
	vector<vector<ll>> memo(full_mask, vector<ll>(full_mask));
	for (int i = 0; i < full_mask; i++) {
		for (int j = 0; j < full_mask; j++) {
			memo[i][j] = compat2(i, j, m);
		}
	}
	for (int i = 2; i <= n; i++) {
		dp_next.assign(full_mask, 0);
		for (int mask2 = 0; mask2 < full_mask; mask2++) {
			for (int mask1 = 0; mask1 < full_mask; mask1++) {
				dp_next[mask2] = (dp_next[mask2] + dp_prev[mask1] * memo[mask1][mask2]) % MOD;

			}
		}
		swap(dp_prev, dp_next);
	}
	ll ans = 0;
	for (int i = 0; i < full_mask; i++) {
		ans = (ans + dp_prev[i]) % MOD;
	}
	cout << ans << endl;
}
void voyager() {
	int n;
	cin >> n;
	vector<vector<int>> g(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> g[i][j];
		}
	}
	vector<int> a(n);
	iota(all(a), 0);
	int min_cost = 1e9;
	do {
		int tmp = 0;
		for (int i = 0; i < n - 1; i++) {
			tmp += g[a[i]][a[i + 1]];
		}
		min_cost = min(tmp, min_cost);
		for (int i = 0; i < n; i++) {
			cout << a[i] << ' ';
		}
		cout << endl;
	} while (next_permutation(all(a)));
	cout << min_cost << endl;
}



int main() {
}