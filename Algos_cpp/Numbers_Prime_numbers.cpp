#include <bits/stdc++.h>
using ll = long long;
using namespace std;

//Бинарное возведение в степень
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
//_____________________________________________________________________//

//Проверка на простоту банальная, кринж такое писать
bool check_prime(ll n) {
    bool OK = true;
    if (n == 2)
        return true;
    if (n % 2 == 0) 
        return false;
    for (ll i = 3; i < sqrt(n) + 1; i+= 2) {
        if (n % i == 0) OK = false;
    }
    return OK;
}

//Возвращает первые cnt Простых чисел
vector<ll> primeNums_cnt(ll cnt) {
    // n * ln(n) + n * ln(ln(n)) + n - ограничение простых чисел 
    //теорема о распределении простых чисел
    if (cnt == 1) return { 2 };
    cnt -= 1;//двойку уже посчитали
    ll n;
    if (cnt <= 6) n = 20;
    else n = ll(cnt * log(cnt) + cnt * log(log(cnt)) + cnt);

    vector<ll> res(n + 1, 1);
    vector<ll> ans = { 2 };
    ll len = 0;
    //решетом эратосфена
    for (ll i = 3; i < n; i += 2) {
        if (len == cnt) break;
        if (res[i] == 1) {
            ans.push_back(i);
            for (ll j = 2 * i; j <= n; j += i) {
                res[j] = 0;
            }
            len++;
        }
    }
    return ans;
}

//Возвращает простые числа в промежутке [1;N]
vector<ll> primeNums2N(ll n) {
    //решетом Эратосфена
    vector<bool> res(n + 1, 1);
    vector<ll> ans = { 2 };
    for (ll i = 3; i <= n; i += 2) {
        if (res[i] == 1) {
            ans.push_back(i);
            for (ll j = 2 * i; j <= n; j += i) {
                res[j] = 0;
            }
        }
    }
    return ans;
}

//Факторизация натурального числа (много запросов, маленькие числа)
void factorization(ll n, vector<ll>& numbers, vector<ll>& pow) {
    //Можно ускорить, если нужно много факторизаций.
    vector<ll> primes = primeNums2N(ll(sqrt(n) + 1));

    numbers = {};
    pow = {};
    for (int i = 0; i < primes.size(); i++) {
        if (n == 1) break;
        if (n % primes[i] == 0) {
            numbers.push_back(primes[i]);
            pow.push_back(1);
            n /= primes[i];
            while (n % primes[i] == 0) {
                pow[pow.size() - 1]++;
                n /= primes[i];
            }
        }
    }
}
//Факторизация натурального числа (мало запрсоов, большие числа)
void factorization2(ll n, vector<ll>& numbers, vector<ll>& pow) {
    numbers = {};
    pow = {};
    for (int i = 2; i < sqrt(n); i++) {
        if (n % i == 0) {
            numbers.push_back(i);
            pow.push_back(0);
        }
        while (n % i == 0) {
            pow[pow.size() - 1]++;
            n /= i;
        }
    }
}
//Нахождение суммы делителей числа
ll sum_divs(ll n) {
    //основано на факторизации
    ll res = 1;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i != 0)
            continue;
        ll al = 0;
        while (n % 2 == 0) {
            al++;
            n /= i;
        }
        res = res * (binpow(i, al + 1) - 1) / (i - 1);//Q(24)=Q(2^3)*Q(3)=Q(геом.прогр., где b1=1, q=2) * 3
    }
    if (n > 1) {
        res = res * (binpow(n, 2) - 1) / (n - 1);
    }
    return res;
}

//Нахождение массива делителей числа
vector<ll> divs(ll n) {
    vector<ll> res = {};
    for (int i = 1; i <= sqrt(n) + 1; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (n / i != i) res.push_back(n / i);
        }
    }
    return res;
}

//Стандартный gcd
ll gcd(ll a, ll b) {
    return a == 0 ? b : gcd(b % a, a);
}
//Стандартный lcm;
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

//%, работающий верно и при отрицательных числах
ll mod(ll a, ll b) {
    return (a % b + b) % b;
}

//О да, расширенный алгоритм Евклида
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

//Решение линейного диофантового, g == gcd
//out: x0,y0,g, true/false - существует решение или нет
bool Diofant(ll a, ll b, ll c, ll& x0, ll& y0, ll& g) {
    g = extended_gcd(abs(a), abs(b), x0, y0);
    if (c % g != 0)
        return false;
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0)   x0 *= -1;
    if (b < 0)   y0 *= -1;
    return true;
}
