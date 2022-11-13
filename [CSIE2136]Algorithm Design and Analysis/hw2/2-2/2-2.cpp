#include <iostream>
#include <climits>
#include <string.h>

using namespace std;

#define ll long long

const ll maxn = 500 + 10;

ll arr[maxn], dp[maxn][maxn], gcd[maxn][maxn];

ll max(ll a, ll b)
{
    return a > b ? a : b;
}

ll __gcd(ll a, ll b)
{
    if (b == 0)
    {
        return a;
    }
    return __gcd(b, a % b);
}

ll cal_gcd(ll x, ll y)
{
    if (gcd[x][y] != -1)
    {
        return gcd[x][y];
    }
    else
    {
        gcd[x][y] = gcd[y][x] = __gcd(arr[x], arr[y]);
        return gcd[x][y];
    }
}

ll solve(int l, int r) // [l, r)
{
    if (dp[l][r] != -1)
    {
        return dp[l][r];
    }
    //printf("Start processing l: %d, r: %d\n", l, r);
    ll ans = LLONG_MIN;
    if (r - l == 2)
    {
        ll _gcd = cal_gcd(l, l + 1);
        if (_gcd == 1)
        {
            dp[l][r] = LLONG_MIN;
            //printf("dp[l][r]: %lld, l: %d, r: %d\n", dp[l][r], l, r);
            return dp[l][r];
        }
        else
        {
            dp[l][r] = _gcd;
            //printf("dp[l][r]: %lld, l: %d, r: %d\n", dp[l][r], l, r);
            return _gcd;
        }
    }
    else if (r - l == 3)
    {
        ll gcd_1 = cal_gcd(l, l + 1), gcd_2 = cal_gcd(l + 1, l + 2), gcd_3 = cal_gcd(l, l + 2);
        if (gcd_1 == 1 or gcd_2 == 1 or gcd_3 == 1)
        {
            dp[l][r] = LLONG_MIN;
            //printf("dp[l][r]: %lld, l: %d, r: %d\n", dp[l][r], l, r);
            return dp[l][r];
        }
        else
        {
            dp[l][r] = gcd_1 + gcd_2;
            //printf("dp[l][r]: %lld, l: %d, r: %d\n", dp[l][r], l, r);
            return dp[l][r];
        }
    }

    for (int m = l + 2; m < r - 1; ++m) // [l, r) 中間找切點 m
    {
        ll left = solve(l, m), right = solve(m, r);
        if (left != LLONG_MIN and right != LLONG_MIN)
        {
            ans = max(ans, left + right);
        }
    }

    // a (...) a
    ll medium = solve(l + 1, r - 1);
    ll _gcd = cal_gcd(l, r - 1);
    if (medium != LLONG_MIN and _gcd != 1)
    {
        ans = max(ans, medium + _gcd);
    }

    if (r - l >= 5)
    {
        // aa (...) a
        medium = solve(l + 2, r - 1);
        ll gcd_1 = cal_gcd(l, l + 1), gcd_2 = cal_gcd(l + 1, r - 1), gcd_3 = cal_gcd(l, r - 1);
        if (medium != LLONG_MIN and gcd_1 != 1 and gcd_2 != 1 and gcd_3 != 1)
        {
            ans = max(ans, medium + gcd_1 + gcd_2);
        }

        // a (...) aa
        medium = solve(l + 1, r - 2);
        gcd_1 = cal_gcd(l, r - 1), gcd_2 = cal_gcd(r - 1, r - 2), gcd_3 = cal_gcd(l, r - 2);
        if (medium != LLONG_MIN and gcd_1 != 1 and gcd_2 != 1 and gcd_3 != 1)
        {
            ans = max(ans, medium + gcd_2 + gcd_3);
        }

        // a (...) a (...) a
        for (int m = l + 3; m < r - 3; ++m)
        {
            ll left = solve(l + 1, m), right = solve(m + 1, r - 1);
            ll gcd_1 = cal_gcd(l, r - 1), gcd_2 = cal_gcd(l, m), gcd_3 = cal_gcd(m, r - 1);
            if (left != LLONG_MIN and right != LLONG_MIN and gcd_1 != 1 and gcd_2 != 1 and gcd_3 != 1)
            {
                ans = max(ans, left + right + gcd_2 + gcd_3);
            }
        }
    }

    dp[l][r] = ans;

    //printf("dp[l][r]: %lld, l: %d, r: %d\n", dp[l][r], l, r);
    return dp[l][r];
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &(arr[i]));
    }

    memset(gcd, -1, sizeof(gcd[0][0]) * maxn * maxn);
    memset(dp, -1, sizeof(dp[0][0]) * maxn * maxn);
    //OK
    ll res = solve(0, n);

    if (res != LLONG_MIN)
    {
        printf("%lld\n", res);
    }
    else
    {
        printf("-1\n");
    }

    return 0;
}
