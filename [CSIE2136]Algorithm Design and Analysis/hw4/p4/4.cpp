/* discuss with p10922001 黃佳琪 */

#include <bits/stdc++.h>

using namespace std;

#define AC                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
#define pb(a) push_back(a)
#define pf(a) push_front(a)
#define pob pop_back()
#define pof pop_front()
#define mp(a, b) make_pair(a, b)
#define F first
#define S second
#define endl '\n'
#define sep ' '
// #define DEBUG

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int maxn = 1000 + 10;
const int mod = 1e9 + 7;
const ll inf = 1e18;

int main()
{
    AC;
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    random_device rd;
    mt19937 gen = mt19937(rd());
    uniform_int_distribution<int> dis(0, n - 1);
    auto myrand = bind(dis, gen);

    int nRandom = 4 * n / m; // number of times that should randomly pick a break point letting the ring become a rod

    ll ans = inf;
    unordered_set<ll> used;

    while (nRandom--)
    {
        vector<vector<ll> > dp(n, vector<ll>(m, inf));
        int bp = myrand(); // breakpoint
        if (used.find(bp) == used.end())
        {
            used.insert(bp);
        }
        else
        {
            continue;
        }
        vector<ll> arr;
        arr.insert(arr.end(), a.begin() + bp, a.end());
        arr.insert(arr.end(), a.begin(), a.begin() + bp);

        // base case
        dp[0][0] = arr[0];
        dp[1][0] = dp[0][0] + arr[1] - abs(arr[1] - arr[0]);
        for (int i = 2; i < n; i++)
        {
            dp[i][0] = dp[i - 1][0] + arr[i] - abs(arr[i] - arr[i - 1]) +
                       arr[i - 1] * ((arr[i - 2] & arr[i - 1]) ^
                                     (arr[i - 1] | arr[i]) ^ (arr[i - 2] + arr[i]));
        }

        // recursive case
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j <= i and j < m; j++)
            {
                vector<ll> add(3, 0);
                if (i == 1)
                {
                    add[0] = arr[i] - abs(arr[i] - arr[i - 1]);
                }
                else
                {
                    add[0] = arr[i] - abs(arr[i] - arr[i - 1]) +
                             arr[i - 1] * ((arr[i - 2] & arr[i - 1]) ^
                                           (arr[i - 1] | arr[i]) ^ (arr[i - 2] + arr[i]));
                }
                add[1] = arr[i];
                add[2] = arr[i - 1] + arr[i] - abs(arr[i] - arr[i - 1]);

                if (i >= 2)
                {
                    dp[i][j] = min({dp[i - 1][j] + add[0], dp[i - 1][j - 1] + add[1], dp[i - 2][j - 1] + add[2]});
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j] + add[0], dp[i - 1][j - 1] + add[1]);
                }
            }
        }
#ifdef DEBUG
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << dp[i][j] << sep;
            }
            cout << endl;
        }
        cout << endl;
#endif
        ans = min(ans, dp[n - 1][m - 1]);
    }

    cout << ans << endl;

    return 0;
}
