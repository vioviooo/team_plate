#include <bits/stdc++.h>

using ll = long long;
const ll INF = 1e18;

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

using namespace std;

struct network {
	struct edge {
		int u, v;
		ll f, c;
		edge(int _u, int _v, ll _c) : u(_u), v(_v), f(0), c(_c){}
	};

	int n;
	vector<edge> edges;
	vector<vector<int>> g;
	vector<int> d;
	vector<size_t> ptr;

	network(int _n) : n(_n), g(n){}

	void add_edge(int u, int v, ll c) {
		g[u].push_back(edges.size());
		edges.push_back(edge(u, v, c));
		g[v].push_back(edges.size());
		edges.push_back(edge(v, u, 0));
	}

	friend ostream& operator <<(ostream& out, const network& g) {
		int n = g.edges.size();
		for (int i = 0; i < n; i++) {
			edge elem = g.edges[i];
			if(elem.f > 0)
				out << elem.u + 1 << ' ' << elem.v + 1 << ' ' << elem.f << '\n';
		}
		return out;
	}
	void bfs(int u, ll b) {
		d.assign(n, -1);
		queue<int> q;
		q.push(u);
		d[u] = 0;
		while (!q.empty()) {
			u = q.front();
			q.pop();
			for (int ind : g[u]) {
				ll c = edges[ind].c;
				ll f = edges[ind].f;
				if (c - f < b) {
					continue;
				}
				int v = edges[ind].v;
				if (d[v] == -1) {
					d[v] = d[u] + 1;
					q.push(v);
				}
				if (d[v] % 2 == d[u] % 2) {
					cout << -1;
					return;
				}
			}
		}
	}
	ll dfs(int u, int finish, ll b, ll fp) {
		if (u == finish) {
			return fp;
		}
		for (; ptr[u] < g[u].size(); ptr[u]++) {
			int ind = g[u][ptr[u]];
			ll c = edges[ind].c;
			ll f = edges[ind].f;
			if (c - f < b) {
				continue;
			}
			int v = edges[ind].v;
			if (d[v] != d[u] + 1) {
				continue;
			}
			ll tmp = dfs(v, finish, b, min(c - f, fp));
			if (tmp > 0) {
				edges[ind].f += tmp;
				edges[ind ^ 1].f -= tmp;
				return tmp;
			}
		}
		return 0;
	}

	ll dinic(int start, int finish, ll b) {
		ll res = 0;
		while (1) {
			bfs(start, b);
			if (d[finish] == -1) {
				break;
			}
			ptr.assign(n, 0);
			while (1) {
				ll f = dfs(start, finish, b, INF);
				if (f > 0) {
					res += f;
				}
				else {
					break;
				}
			}
		}
		return res;
	}
	ll max_flow(int start, int finish) {
		d.clear();
		d.resize(n, -1);
		ptr.clear();
		ptr.resize(n, 0);
		ll res = 0;
		for (int pow = 30; pow >= 0; pow--) {
			res += dinic(start, finish, 1ll << pow);
		}
		return res;
	}
};

void solve()
{
    // let's go kid
	int start, finish, ans;
	int n, m;
	cin >> n >> m;
	network g(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		ll c;
		cin >> u >> v >> c;
		u--;
		v--;
		if (u == v) {
			cout << -1;
			goto A;
		}
		g.add_edge(u, v, c);
	}
	start = 1;
	finish = n;
	ans = g.max_flow(start - 1, finish - 1);
	cout << ans << endl;
	cout << g;
	A:
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