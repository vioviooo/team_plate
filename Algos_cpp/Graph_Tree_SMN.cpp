#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using ll = long long;

//Объявление ребра и его веса
struct wedge {
	int u, v;
	ll w;
};

//Сравнение ребер по весу
bool operator < (wedge a, wedge b) {
	return a.w < b.w;
};

using namespace std;
using wgraph = vector<vector<wedge>>;

//Ого, да это же система непересекающихся множеств
//И минимальное остовное дерево найдется, пока в системе не останется одного множества. Очевидно, да?
struct dsu {
	vector<int> leader;
	vector<int> size;
	int n;

	dsu(int _n) {
		n = _n;
		leader.resize(n);
		for (int i = 0; i < n; i++) {
			leader[i] = i;
		}
		size.resize(n, 1);
	}

	int find(int u) {
		if (leader[u] == u) {
			return u;
		}
		leader[u] = find(leader[u]);
		return leader[u];
	}

	bool unite(int u, int v) {
		int lu = find(u);
		int lv = find(v);
		if (lu == lv) {
			return false;
		}
		if (size[lu] > size[lv]) {
			swap(lu, lv);
		}
		leader[lu] = lv;
		size[lv] += size[lu];
		return true;
	}
};

int main() {
	int n, m; 
	cin >> n >> m;
	vector<wedge> edges;
	for (int i = 0; i < m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--;
		v--;
		edges.push_back({ u,v,w });
	}
	sort(all(edges));
	dsu d(n);
	ll w_total = 0;
	vector<wedge> wedges_mst;
	for (wedge elem : edges) {
		int u = elem.u;
		int v = elem.v;
		if (!d.unite(u, v)) {
			continue;
		}
		else {
			ll w = elem.w;
			w_total += w;
			wedges_mst.push_back({ u,v,w });
		}
	}
	cout << w_total << endl;
	for (int i = 0; i < n - 1; i++) {
		cout << wedges_mst[i].w << ' ';
	}
}