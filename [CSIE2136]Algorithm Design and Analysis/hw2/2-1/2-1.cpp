/* discuss with 沈家睿、李旻翰、徐晨祐、花雲鴻、黃佳琪*/

#include <climits>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

#define AC                            \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);
#define ll long long
#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)

using namespace std;

ll max(ll a, ll b)
{
    return a > b ? a : b;
}

void solve()
{
    vector<vector<ll> > arr, dp;
    vector<vector<vector<ll> > > dq;
    deque<pii> path;
    deque<int> offset;
    int n, m, k;
    cin >> n >> m >> k;
    arr.resize(n + 1, vector<ll>(m + 5));
    dp.resize(n + 1, vector<ll>(m + 1, LLONG_MIN));
    // vector<vector<ll> > arr(n + 5, vector<ll>(m + 5)), dp(n + 1, vector<ll>(m + 1, LLONG_MIN));
    string str;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> str;
            if (str == "X")
            {
                arr[i][j] = LLONG_MIN;
            }
            else
            {
                arr[i][j] = stoll(str);
            }
        }
    }

    int len = 0, tmp = k, prev = -1;
    while (tmp - tmp / 3 > 0)
    {
        prev = tmp;
        if (tmp <= 2)
        {
            tmp--;
        }
        tmp -= tmp / 3;
        len++;
        offset.push_front(prev - tmp);
    }

    dq.resize(n + 1, vector<vector<ll> >(m + 1, vector<ll>(len + 1, LLONG_MIN)));
    //vector<vector<vector<ll> > > dq(n + 1, vector<vector<ll> >(m + 1, vector<ll>(len + 1, LLONG_MIN)));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i == 1 and j == 1)
            {
                dp[i][j] = dq[i][j][0] = 0;
                for (int z = 1; z < len; z++)
                {
                    dq[i][j][z] = 0;
                }
                continue;
            }

            ll money_up = (i > 1) ? dq[i - 1][j][len - 1] : LLONG_MIN;
            ll money_left = (j > 1) ? dq[i][j - 1][len - 1] : LLONG_MIN;
            ll money_up_offset = (i > offset[len - 1]) ? dq[i - offset[len - 1]][j][len - 1] : LLONG_MIN;
            ll money_left_offset = (j > offset[len - 1]) ? dq[i][j - offset[len - 1]][len - 1] : LLONG_MIN;
            if (arr[i][j] == LLONG_MIN || (money_up == LLONG_MIN and money_left == LLONG_MIN and money_up_offset == LLONG_MIN and money_left_offset == LLONG_MIN))
            {
                dp[i][j] = dq[i][j][0] = LLONG_MIN;
            }
            else
            {
                dp[i][j] = dq[i][j][0] = max(money_up, max(money_up_offset, max(money_left, money_left_offset))) + arr[i][j];
            }

            for (int z = 1; z < len; z++)
            {
                money_up = (i > offset[z - 1]) ? dq[i - offset[z - 1]][j][z - 1] : LLONG_MIN;
                money_left = (j > offset[z - 1]) ? dq[i][j - offset[z - 1]][z - 1] : LLONG_MIN;
                dq[i][j][z] = max(dq[i][j][z - 1], max(money_up, money_left));
            }
        }
    }
    if (dp[n][m] == LLONG_MIN)
    {
        cout << "Impassable\n";
    }
    else
    {
        cout << "Passable\n";

        int i = n, j = m;
        int tmp_len = len - 1;
        while (i > 0 and j > 0)
        {
            if (dq[i][j][tmp_len] == dp[i][j])
            {
                path.push_front(mp(i, j));
                tmp_len = len - 1;
            }
            else
            {
                tmp_len--;
            }
            ll money_up = (i > 1) ? dq[i - 1][j][tmp_len] : LLONG_MIN;
            ll money_left = (j > 1) ? dq[i][j - 1][tmp_len] : LLONG_MIN;
            ll money_up_offset = (i > offset[tmp_len]) ? dq[i - offset[tmp_len]][j][tmp_len] : LLONG_MIN;
            ll money_left_offset = (j > offset[tmp_len]) ? dq[i][j - offset[tmp_len]][tmp_len] : LLONG_MIN;

            ll maxx = max(money_up, max(money_up_offset, max(money_left, money_left_offset)));

            if (maxx == money_up)
            {
                i--;
            }
            else if (i > offset[tmp_len] and maxx == money_up_offset)
            {
                i -= offset[tmp_len];
            }
            else if (maxx == money_left)
            {
                j--;
            }
            else if (j > offset[tmp_len] and maxx == money_left_offset)
            {
                j -= offset[tmp_len];
            }
        }

        cout << dp[n][m] << "\n"
             << path.size() << "\n";

        deque<pii>::iterator it = path.begin();
        while (it != path.end())
        {
            cout << it->first << " " << it->second << "\n";
            it++;
        }
    }
}

int main()
{
    AC;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
