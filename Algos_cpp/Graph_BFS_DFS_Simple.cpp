#include <bits/stdc++.h>

using namespace std;
using graph = vector<vector<int>>;

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

vector<int> bfs(int u, const graph& g) {
	int n = g.size();
	vector<int> d(n, -1);
	queue<int> q;
	d[u] = 0;
	q.push(u);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (int v : g[u]) {
			if (d[v] == -1) {
				d[v] = 1 + d[u];
				q.push(v);
			}
		}
	}
	return d;
}

bool dfs(int u, const graph& g, vector<int>& mt, vector<int>& visited) {
	if (visited[u])
		return false;
	visited[u] = true;
	for (int v : g[u]) {
		if (mt[v] == -1) {
			mt[v] = u;
			return true;
		}
		bool tmp = dfs(mt[v], g, mt, visited);
		if (tmp) {
			mt[v] = u;
			return true;
		}
	}
	return false;
}

void solve()
{
    // let's go kid
	int n, m;
	cin >> n >> m;
	n *= 2;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		v += n / 2;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector<int> d = bfs(0, g);
	int ans = 0;
	vector<int> mt(n, -1);
	for (int i = 0; i < n / 2; i++) {
		vector<int> visited(n, false);
		ans += dfs(i, g, mt, visited);
	}
	cout << ans << '\n';
	for (int i = 0; i < n; i++) {
		if (mt[i] == -1) {
			continue;
		}
		cout << mt[i] + 1 << ' ' << i + 1 - n / 2 << '\n';
	}
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    SPEEDTEST_START
    solve();
    SPEEDTEST_STOP
}