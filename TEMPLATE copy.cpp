#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip> 
#include <string>
#include <queue>
#include <set>
#include <fstream>
#include <ctime>
#include <random>
#include <bitset>
#include <array>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

template <typename T>

using pair2 = pair <T, T>;
using pii = pair <int, int>;
using pli = pair <ll, int>;
using pll = pair <ll, ll>;

#define lb lower_bound
#define ub upper_bound
#define pop pop_back
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define fastboi ios::sync_with_stdio(false); cin.tie(0);

clock_t startTime;
double timing() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

const ll MOD = 1e9 + 7;
const ll INF = 1e18;
//const ld PI = acos(-1);

using graph = vector< vector <int> >;

int order = 0;
void dfs(int u, graph &g, vector <int> &res) {
    if (res[u] != -1) {
        return;
    }
    
    res[u] = order;
    
    order++;
    
    for (auto v : g[u]) { // visit all the vertices of a node
        dfs(v, g, res); // recursive call
    }
}

int main() {
    
    fastboi
    
    int n, m, k;
    cin >> n >> m >> k;
    
    --k;
    
    graph g(n);
    
    for (int i = 0; i < m; ++i) {
        
        int u, v;
        cin >> u >> v;
        
        --u;
        --v;
        
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    vector<int> res(n, -1); // path of our traversal
    
    dfs(k, g, res);
    
    for (auto v : res) {
        cout << v << ' ';
    }
}