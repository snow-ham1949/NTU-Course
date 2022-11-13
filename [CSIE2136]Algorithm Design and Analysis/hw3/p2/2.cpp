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
#define sep " "
// #define DEBUG

/***
    Author : @csypt
    Time : 2021:11:25  00:40:25
***/

/***
reference:
1. https://cp-algorithms.com/graph/strongly-connected-components.html#toc-tgt-3
***/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int maxn = 1000 + 10;
const int mod = 1e9 + 7;

class Edge
{
public:
    int u, v;
    Edge(int u, int v)
    {
        this->u = u, this->v = v;
    }
};

void tarjanDFS(int id, vector<int> &low, vector<int> &dfn, vector<bool> &in_stk, vector<int> &root, vector<int> &root_nodes,
               const vector<vector<int> > &g, stack<int> &stk, int &timestamp, int &numSCC)
{
    dfn[id] = low[id] = ++timestamp;
    stk.push(id), in_stk[id] = 1;
    for (auto i : g[id])
    {
        if (dfn[i] == 0)
        {
            tarjanDFS(i, low, dfn, in_stk, root, root_nodes, g, stk, timestamp, numSCC);
            low[id] = min(low[id], low[i]);
        }
        else if (in_stk[i])
        {
            low[id] = min(low[id], dfn[i]);
        }
    }

    if (low[id] == dfn[id])
    {
        root_nodes.pb(id);
        root[id] = id;
        int tp;
        do
        {
            tp = stk.top();
            stk.pop();
            root[tp] = id;
            in_stk[tp] = 0;
        } while (id != tp and !stk.empty());
        numSCC++;
    }
}

void tarjan(int n, vector<int> &root, vector<int> &root_nodes, int &numSCC, const vector<vector<int> > &g)
{
    vector<int> low(n + 1, 0), dfn(n + 1, 0);
    vector<bool> in_stk(n + 1, false);
    stack<int> stk;
    int timestamp = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dfn[i] == 0)
        {
            tarjanDFS(i, low, dfn, in_stk, root, root_nodes, g, stk, timestamp, numSCC);
        }
    }
}

int dfs(int v, vector<bool> &vis, const vector<vector<int> > &g)
{
    if (vis[v])
    {
        return -1;
    }
    vis[v] = 1;
    if (g[v].size() == 0)
    {
        return v;
    }
    for (int u : g[v])
    {
        int res = dfs(u, vis, g);
        if (res != -1)
        {
            return res;
        }
    }

    return -1;
}

int main()
{
    AC;
    int t, flag;
    cin >> t >> flag;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int> > g(n + 1, vector<int>()), scc_g(n + 1, vector<int>());
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].pb(v);
        }

        // find SCC
        vector<int> root(n + 1, -1), root_nodes;
        int numSCC = 0;
        tarjan(n, root, root_nodes, numSCC, g);

        if (numSCC == 1)
        {
            cout << "0\n";
            continue;
        }
        // cout << "0\n";

        // connect SCC (directed graph into DAG)
        for (int v = 1; v <= n; v++)
        {
            for (auto u : g[v])
            {
                if (root[u] != root[v])
                {
                    scc_g[root[v]].pb(root[u]);
                }
            }
        }

        // find source / sink
        vector<bool> in(n);
        vector<int> tmp_source, tmp_sink;
        for (int v : root_nodes)
        {
            if (scc_g[v].size() == 0)
            {
                tmp_sink.pb(v);
                continue;
            }
            for (int u : scc_g[v])
            {
                in[u] = 1;
            }
        }
        for (int v : root_nodes)
        {
            if (!in[v])
            {
                tmp_source.pb(v);
            }
        }

        // connect source / sink
        vector<int> MatchedSource, MatchedSink, NeverMatchedSource, NeverMatchedSink, source, sink;
        vector<bool> vis(n + 1, false);
        vector<Edge> connect;

        for (int v : tmp_source)
        {
            int matching_sink = dfs(v, vis, scc_g);
            if (matching_sink != -1)
            {
                MatchedSource.pb(v), MatchedSink.pb(matching_sink);
            }
            else
            {
                NeverMatchedSource.pb(v);
            }
        }

        for (int v : tmp_sink)
        {
            if (!vis[v])
            {
                NeverMatchedSink.pb(v);
            }
        }

        source.insert(source.end(), MatchedSource.begin(), MatchedSource.end());
        source.insert(source.end(), NeverMatchedSource.begin(), NeverMatchedSource.end());
        sink.insert(sink.end(), MatchedSink.begin(), MatchedSink.end());
        sink.insert(sink.end(), NeverMatchedSink.begin(), NeverMatchedSink.end());

        int ms_sz = MatchedSource.size(), source_sz = source.size(), sink_sz = sink.size();
        int source_sink_min = min(source_sz, sink_sz);
        connect.pb(Edge(sink[0], source[ms_sz - 1]));
        for (int i = 1; i < ms_sz; i++)
        {
            connect.pb(Edge(sink[i], source[i - 1]));
        }
        for (int i = ms_sz; i < source_sink_min; i++)
        {
            connect.pb(Edge(sink[i], source[i]));
        }
        for (int i = source_sink_min; i < source_sz; i++)
        {
            connect.pb(Edge(sink[0], source[i]));
        }
        for (int i = source_sink_min; i < sink_sz; i++)
        {
            connect.pb(Edge(sink[i], source[0]));
        }

        cout << connect.size() << "\n";
        if (flag)
        {
            for (auto [u, v] : connect)
            {
                cout << u << sep << v << "\n";
            }
        }
    }

    return 0;
}