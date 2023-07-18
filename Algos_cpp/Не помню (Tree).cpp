#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v;
};

using graph = vector<vector<edge>>;

void dfs(int u, int p, const graph& g, vector<int>& d) {
    for (edge elem : g[u]) {
        int v = elem.v;
        if (v == p) {
            continue;
        }
        d[v] = 1 + d[u];
        dfs(v, u, g, d);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for (int t1 = 0; t1 < t; t1++) {
        int n;
        cin >> n;
        graph g(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            g[u].push_back({ u,v });
            g[v].push_back({ v,u });
        }
        int u = 0;
        vector<int> d1(n);
        dfs(u, u, g, d1);
        int v = 0;
        for (int i = 0; i < n; i++) {
            if (d1[i] > d1[v]) {
                v = i;
            }
        }
        vector<int> d2(n);
        dfs(v, v, g, d2);
        for (int i = 0; i < n; i++) {
            if (d2[i] > d2[u]) {
                u = i;
            }
        }
        cout << d2[u] << endl;
    }
}