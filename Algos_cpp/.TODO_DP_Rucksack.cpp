#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//O(nW)
ll R_classic_w(ll n, vector<ll> &mass, vector<ll> &vals, ll mx) {
    //max value = ?
    //пусть A(k,s) = max value, где макс вместимость = s, если
    //дано только первые k предметов
    vector<vector<ll>> dp(n + 1, vector<ll>(mx + 1));
    //  dp(i,j)=max(
    //              A(i−1,j),
    //              A(i−1,j−Wi)+Pi          wi = вес k-го прдемета
    //              )                       pi = стоимость k-го предмета
    //
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= mx; j++) {
            if (j - mass[i] >= 0)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - mass[i]] + vals[i]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][mx];
}

//O(nP)
ll R_classic_v(ll n, vector<ll>& mass, vector<ll>& vals, ll mx)
{




}
int main()
{
    int n, mx;
    cin >> n >> mx;
    vector<ll> mass(n+1);
    vector<ll> vals(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> mass[i];
        cin >> vals[i];
    }
    cout << R_classic_w(n, mass, vals, mx);
}