#include <bits/stdc++.h>
#define ll long long

using namespace std;

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

//бинарное возведение в степень два варианта
ll binpow(ll a, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}
ll bin_pow(ll a, ll n, ll mod) {
	ll res = 1;
	while (n) {
		if (n & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		n >>= 1;
	}
	return res;
}

//%, работающий верно и при отрицательных числах
ll mod(ll a, ll b) {
	return (a % b + b) % b;
}

//величайший расширенный алгоритм Евклида, который
//никогда не запомню
ll extended_gcd(ll a, ll b, ll& x, ll& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	ll x1, y1;
	ll d = extended_gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

//Функция Эйлера
ll euler(ll n) {
	ll res = n;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		while (n % i == 0) {
			n /= i;
		}
		res = (res - res / i);
	}
	if (n > 1) {
		res = (res - res / n);
	}
	return res;
}

//есть по расш. алг. Евклида
//есть по функции Эйлера
//если mod простое, то fi(a) = a-1, то вообще изи
ll inverse_evkl(ll a, ll m) {
	ll x1, y1;
	ll g = extended_gcd(a, m, x1, y1);
	if (g != 1) {
		return -1;
	}
	else {
		return mod(x1, m);
	}
}
ll inverse_primemod(ll a, ll primemod) {
	return bin_pow(a, primemod - 2, primemod);
}
ll inverse_euler(ll a, ll mod) {
	return bin_pow(a, euler(mod) - 1, mod);
}

void solve()
{
    // let's go kid
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