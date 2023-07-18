#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

bool check(int m, int N, int a, int b) {
	return !((N - 1) <= (m / a + m / b));//some formula
}
//00000000000000001111111111111111
//               lr
// 
//binary search ans
//Задача о двух принтерах: за сколько времени
//Два принтера со скороятми печати a и b напечатают N копий?
//Сначала имеется только 1 оригинал, поэтому есть доп. условие
//С запуском второго принтера

void solve()
{
    // let's go kid
	int N, a, b;
	cin >> N >> a >> b;
	if (N == 1) cout << min(a, b);
	else {
		int l = 0;
		int r = 1e9;
		int m = r;
		while (r - l > 1) {
			m = (l + r) / 2;
			if (check(m, N, a, b)) {
				l = m;
			}
			else {
				r = m;
			}
		}
		cout << r + min(a, b);
	}
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
