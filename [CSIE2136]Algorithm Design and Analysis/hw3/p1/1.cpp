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

/***
    Author : @csypt
    Time : 2021:11:25  16:11:35
***/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;

vector<int> g[maxn], path, frm, to, dp1, dp2, depth, parent;
int n, another;

void dfs(int s, int father) // find tree diameter
{
    parent[s] = father;
    for (int e : g[s])
    {
        if (e == father)
        {
            continue;
        }
        depth[e] = depth[s] + 1;
        if (depth[e] > depth[another])
        {
            another = e;
        }
        dfs(e, s);
    }
}

void cal(int v, int father, vector<int> &dp1, vector<int> &dp2)
{
    int first = -1, second = -1;
    for (auto &u : g[v])
    {
        if (u == father)
        {
            continue;
        }
        cal(u, v, dp1, dp2);
        if (first == -1)
        {
            first = dp1[u];
        }
        else if (dp1[u] >= first)
        {
            second = first;
            first = dp1[u];
        }
        else if (dp1[u] > second)
        {
            second = dp1[u];
        }
    }

    dp1[v] = 1;
    if (first != -1)
    {
        dp1[v] += first;
    }
    if (second != -1)
    {
        dp2[v] = 1 + first + second;
    }

    return;
}

int main()
{
    AC;
    cin >> n;
    depth.resize(n + 1, 0), parent.resize(n + 1, 0);
    for (int i = 0; i < n - 1; i++)
    {
        int s, e;
        cin >> s >> e;
        g[s].pb(e);
        g[e].pb(s);
    }

    another = 1;
    dfs(1, 0);
    depth[another] = 0;
    int start, end;
    start = another;
    dfs(another, 0);
    end = another;

    // memory vertices on diameter
    int tmp = end;
    path.pb(tmp);
    while (tmp != start)
    {
        tmp = parent[tmp];
        path.pb(tmp);
    }

    int path_sz = path.size();
    dp1.resize(n + 1, 0), dp2.resize(n + 1, 0);
    to.resize(n + 1), frm.resize(n + 1);

    cal(end, end, dp1, dp2);

    int pre, v = start;
    to[v] = max(dp1[v], dp2[v]) - 1;

    for (int i = path_sz - 2; i >= 0; i--)
    {
        v = path[i], pre = path[i + 1];
        to[v] = max(to[pre], max(dp1[v], dp2[v]) - 1);
    }

    cal(start, start, dp1, dp2);
    v = end;
    frm[v] = max(dp1[v], dp2[v]) - 1;
    for (int i = 1; i < path_sz; i++)
    {
        v = path[i], pre = path[i - 1];
        frm[v] = max(frm[pre], max(dp1[v], dp2[v]) - 1);
    }

    int u, res = INT_MAX;
    for (int i = 1; i < path_sz; i++)
    {
        u = path[i], v = path[i - 1];
        int temp = max({to[u], frm[v], 1 + (to[u] + 1) / 2 + (frm[v] + 1) / 2});
        res = min(res, temp);
    }

    cout << res;

    return 0;
}