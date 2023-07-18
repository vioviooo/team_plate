#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

const ll INF = 1e18;
const int INF_int = 1e9;
const ll MOD = 1e9 + 7;
const double PI = acos(-1.0);

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP printf("Process finished in: "); printf("%f", (double)(clock() - __speedstart__)/CLOCKS_PER_SEC); printf(" seconds");


void solve()
{
    // let's go kid
}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    SPEEDTEST_START
    solve();
    SPEEDTEST_STOP
}