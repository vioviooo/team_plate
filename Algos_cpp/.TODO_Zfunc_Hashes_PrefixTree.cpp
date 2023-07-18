#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()

using ll = long long;
using namespace std;
const ll MOD = 1e9 + 7;
const int MAX_N = 1e5;
vector<ll> b(MAX_N + 1);
vector<ll> inv_b(MAX_N + 1);

ll bpow(ll x, ll y) {
	ll z = 1;
	while (y) {
		if (y & 1) {
			z = (z * x) % MOD;
		}
		x = (x * x) % MOD;
		y = y >> 1;
	}
	return z;
}
ll inv(ll x) {
	return bpow(x, MOD - 2);
}
const ll B = 29;
const ll B_INV = inv(B);
void prepare() {
	b[0] = 1;
	inv_b[0] = 1;
	for (int i = 1; i <= MAX_N; i++) {
		b[i] = (b[i - 1] * B) % MOD;
		inv_b[i] = (inv_b[i - 1] * B_INV) % MOD;
	}
}
vector<int> z_func(const string& s) {
	int n = s.size();
	vector<int> z(n);
	z[0] = n;
	int l = 0,r = 0;
	for (int i = 1; i < n; i++) {
		if (i < r) {
			z[i] = min(z[i - l], r - i);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			z[i]++;
		}
		if (l + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

void azz() {
	string P, T;
	cin >> P >> T;
	string for_z_func = P + "#" + T;
	vector<int> z_res = z_func(for_z_func);
	int cnt = 0;
	for (int i = 0; i < z_res.size(); i++) {
		if (z_res[i] == P.size())
			cnt++;
	}
	cout << cnt << '\n';
	//---------------------
	string s;
	cin >> s;
	vector<int> z = z_func(s);
	for (int elem : z) {
		cout << elem << ' ';
	}
	cout << endl;
}
int res = 0;
struct trie {
	using dict = map<char, int>;
	trie() {
		create_node();
	}
	struct node {
		dict go;
		int end = 0;
	};
	vector<node> data;
	int create_node() {
		data.push_back(node());
		res++;
		return data.size() - 1;
	}
	bool can_go(int u, char c) {
		return data[u].go[c];
	}
	int go(int u, char c) {
		return data[u].go[c];
	}
	void insert(const string& s) {
		int u = 0;
		for (char c : s) {
			if (!can_go(u, c)) {
				data[u].go[c] = create_node();
			}
			u = go(u, c);
		}
		data[u].end++;
	}
	int count(const string& s) {
		int u = 0;
		for (char c : s) {
			if (!can_go(u, c)) {
				return 0;
			}
			u = go(u, c);
		}
		return data[u].end;
	}
	void erase(const string& s) {
		int u = 0;
		for (char c : s) {
			u = go(u, c);
		}
		data[u].end--;
	}
};

void bzz() {
	trie t;
	t.insert("abac");
	t.insert("abca");
	t.insert("ababa");
	t.insert("acab");
	cout << t.count("abac") << endl;
	cout << t.count("abab") << endl;
	cout << t.count("abaa") << endl;
	t.erase("ababa");
	cout << t.count("ababa") << endl;
}
void czz() {
	string p, t;
	cin >> p >> t;
	prepare();
	ll h1 = 0;
	int m = p.size();
	for (int i = 1; i <= m; i++) {
		h1 = (h1 + (p[i] - 'a' + 1) * b[i]) % MOD;
	}
	int n = t.size();
	vector<ll> pref(n + 1);
	for (int i = 1; i <= n; i++) {
		pref[i] = (pref[i - 1] + (t[i - 1] - 'a' + 1) * b[i - 1]) % MOD;

	}
	for (int i = 1; i <= n; i++) {
		int r = i + m - 1;
		ll h2 = ((pref[r] - pref[i - 1]) * inv_b[i - 1]) % MOD;
		h2 = (h2 + MOD) % MOD;
		if (h1 == h2)
			cout << i << endl;
	}



}
int main() {
	cout << "Compiled";
}