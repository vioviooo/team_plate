#include <bits/stdc++.h>
using ll = long long;

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

using namespace std;
struct wedge {
	int u, v;
	ll w;
};
using wgraph = vector<vector<wedge>>;
using matrix = vector<vector<ll>>;
const ll INF = 1e18;
using item = pair<ll, int>;
//Алгоритм Форда-Беллмана
//От одной вершины до всех. Отрицательные веса
void FordBellman() {
	int n, m, start;
	cin >> n >> m >> start;
	start--;
	vector<wedge> edges;
	for (int i = 0; i < m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--;
		v--;
		edges.push_back({ u,v,w });
		//edges.push_back({v,u,w});
	}
	bool haschanged = true;
	vector<ll> dp(n, INF);
	dp[start] = 0;
	for (int i = 0; i < n; i++) {
		haschanged = false;
		for (wedge elem : edges) {//перебираем все ребра, ВООБЩЕ ВСЕ
			//и перезабись с INF, где надо
			int u = elem.u;
			int v = elem.v;
			ll w = elem.w;
			//сахар!
			if (dp[v] > dp[u] + w) {
				dp[v] = dp[u] + w;
				haschanged = true;
			}
		}
		if (!haschanged) {
			break;
		}
	}
	if (haschanged) {
		cout << "Negative cycle";
	}
	else {
		for (int i = 0; i < n; i++) {
			cout << dp[i] << ' ';
		}
	}
}

//Алгоритм Дейкстры
//Зачем проходить по всем ребрам, если можно релаксировать быстрее?
//Но тогда нужно поставить условие неотрицательности весов!
void dijkstra_slow(wgraph& g, const int u, vector<ll>& d, vector<int>& prev) {
	int n = g.size();
	d[u] = 0;
	prev[u] = 0;
	vector<char> visited(n, false);
	for (int i = 0; i < n; i++) {
		//Два параметра во время поиска в Дейкстре
		int min_id = -1;
		ll val = INF;
		
		//линейно находим минимал
		for (int j = 0; j < n; j++) {
			if (!visited[j] and d[j] < val) {
				min_id = j;
				val = d[j];
			}
		}
		int u = min_id;
		visited[u] = true;
		//обработка ребра заменой
		for (wedge el : g[u]) {
			int v = el.v;
			ll w = el.w;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				prev[v] = u;
			}
		}
	}
}
void dijkstra_fast(wgraph& g, const int u, vector<ll>& d, vector<int>& prev) {
	int n = g.size();
	d[u] = 0;
	prev[u] = 0;
	set<item> pq;
	for (int i = 0; i < n; i++) {
		pq.insert({ d[i], i });
	}
	vector<char> visited(n, false);
	while (!pq.empty()) {
		item curind = *pq.begin();
		pq.erase(curind);
		int u = curind.second;
		visited[u] = true;
		for (wedge elem : g[u]) {
			int v = elem.v;
			if (visited[v]) continue;
			ll w = elem.w;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				prev[v] = u;
				pq.insert({ d[v], v });//пока что не понял этой строчки
			}
		}
	}
}

//solve for dijkstra вычисление от одной ко всем
void solve_dijkstra(){
	int n, m, start;
	cin >> n >> m >> start;
	start--;
	wgraph g(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--;
		v--;
		g[u].push_back({ u,v,w });
		//g[v].push_back({v,u,w});
		vector<ll> distances(n, INF);
		vector<int> prev(n, -1);
		dijkstra_slow(g, start, distances, prev);
	}
}

// Алгоритм Флойда-Уоршелла вычисление между всеми парами вершин
void solve_floyd(){
	int n, m;
	cin >> n >> m;
	matrix g(n, vector<ll>(n, INF));
	for (int i = 0; i < m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--;
		v--;
		g[u][v] = w;
	}
	for (int i = 0; i < n; i++) {
		g[i][i] = 0;
	}
	matrix d(g);
	for (int k = 0; k < n; k++) {
		for (int u = 0; u < n; u++) {
			for (int v = 0; v < n; v++) {
				d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
			}
		}
	}
	for (int u = 0; u < n; u++) {
		for (int v = 0; v < n; v++) {
			if (d[u][v] == INF)
				cout << setw(4) << "INF" << ' ';
			else
				cout << setw(4) << d[u][v] << ' ';
		}
		cout << endl;
	}


}

void solve()
{
    // let's go kid
	solve_dijkstra();
	solve_floyd();
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