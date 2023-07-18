#include <bits/stdc++.h>
using ll = long long;
using namespace std;

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
ll inverse_primemod(ll a, ll primemod) {
    return bin_pow(a, primemod - 2, primemod);
}


ll Factorial(ll a) {//То же самое, что и P
    ll res = 1;
    for (ll i = 1; i <= a; i++) {
        res *= i;
    }
    return res;
}
ll A(ll n, ll k) {
    ll res = 1;
    for (ll i = k + 1; i <= n; i++) {
        res *= i;
    }
    return res;
}
ll C(ll n, ll k) {
    ll res = A(n, k);
    for (ll i = 1; i <= k; i++) {
        res /= i;
    }
    return res;
}
//___________________________________________
ll Factorial(ll a, ll mod) {//То же самое, что и P
    ll res = 1;
    for (ll i = 1; i <= a; i++) {
        res *= i;
        res %= mod;
    }
    return res;
}
ll A(ll n, ll k, ll mod) {
    ll res = 1;
    for (ll i = k + 1; i <= n; i++) {
        res *= i;
        res %= mod;
    }
    return res;
}
ll C(ll n, ll k, ll primemod) {
    ll res = A(n, k, primemod);
    for (ll i = 1; i <= k; i++) {
        res *= inverse_primemod(i,primemod);
        res %= primemod;
    }
    return res;
}


//если большое кол-во запросов, то можно высчитать все С/P/A и с помощью
//ДП занести их в матрицу, переход там легкий, откуда запросто вытаскивать

//напишем рекурсивную штуку, вдруг нам нужно будет посчитать кол-во перестановок с доп. условием или сумму
//или еще хрень какую-нибудь
ll Anagrams(string s)//перестановки с повторениями 
{
    ll res = 1;
    s = "#" + s;
    ll cnt_rep = 1;
    for (ll i = 1; i < s.size(); i++) {
        res *= i;
        if (s[i] != s[i - 1]) {
            res /= Factorial(cnt_rep);
            cnt_rep = 1;
        }
        else
            cnt_rep++;
    }
    res /= Factorial(cnt_rep);
    return res;
}

vector<vector<ll>> result_perms = {};
void A_Show(vector<ll> vec, ll k, vector<ll> res) {
    if (k != 0) {
        for (ll i = 0; i < vec.size(); i++) {
            vector<ll> cop = vec;
            cop.erase(cop.begin() + i);
            vector<ll> cop2 = res;
            cop2.push_back(vec[i]);
            A_Show(cop, k - 1, cop2);
        }
    }
    else {
        for (ll i = 0; i < res.size(); i++) {
            cout << res[i] << ' ';
        }
        cout << '\n';
    }
}

set<set<ll>> remembered = {};
void C_Show(vector<ll> vec, ll k, vector<ll> res) {
    if (k != 0) {
        for (ll i = 0; i < vec.size(); i++) {
            vector<ll> cop = vec;
            cop.erase(cop.begin() + i);
            vector<ll> cop2 = res;
            cop2.push_back(vec[i]);
            C_Show(cop, k - 1, cop2);
        }
    }
    else {
        set<ll> s;
        copy(res.begin(), res.end(), inserter(s,s.end()));
        if (remembered.contains(s)) return;
        else {
            for (ll i = 0; i < res.size(); i++) {
                cout << res[i] << ' ';
            }
            cout << '\n';
            remembered.insert(s);
        }
    }
}

//Повторения можно исключить с помощью remembered;
void P_Show(vector<ll> vec) {
    sort(vec.begin(), vec.end());
    do {
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] << ' ';
        }
        cout << '\n';
    } while (next_permutation(vec.begin(), vec.end()));
}

//числа Каталана рекурсивно, сколько нужно вывести
vector<ll> Catalans(int cnt, ll primemod = 1e9+7) {
    if (cnt <= 0)
        return {};
    if (cnt == 1)
        return { 1 };
    if (cnt == 2) {
        return { 1,1 };
    }
    vector<ll> Catalans(cnt);
    Catalans[0] = 1;
    Catalans[1] = 1;
    for (int i = 3; i <= cnt; i++) {
        ll cur = Catalans[i - 2] * (4 * (i - 1) - 2);
        cur %= primemod;
        cur *= inverse_primemod(i, primemod);
        cur %= primemod;
        Catalans[i - 1] = cur;
    }
    return Catalans;
}
ll GetCatalan(int n, ll primemod) {
    if (n <= 2)
        return 1;
    else
        n--;
    ll j = inverse_primemod(n + 1, primemod);
    ll g = C(2 * n, n, primemod);
    return (g * j) % primemod;
}
ll GetCatalan(int n) {
    if (n <= 2)
        return 1;
    else
        n--;
    return C(2 * n, n) / (n + 1);
}

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

void solve()
{
    cout << GetCatalan(5,1e9+7) << '\n';
    cout << GetCatalan(2, 1e9 + 7) << '\n';
    cout << GetCatalan(3, 1e9 + 7) << '\n';
    vector<ll> g;
    g = Catalans(5, 1e9 + 7);
    cout << g[4] << '\n';
    cout << g[3] << '\n';
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