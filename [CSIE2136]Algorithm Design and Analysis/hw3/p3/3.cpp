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
    Time : 2021:11:25  00:40:22
***/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
class Edge
{
public:
    int e, w, id;
    Edge(){};
    Edge(int e, int w, int id)
    {
        this->e = e, this->w = w, this->id = id;
    }
};

const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;

vector<Edge> graph[maxn];
priority_queue<int, vector<int>, greater<int> > ans;
priority_queue<pll, vector<pll>, greater<pll> > pq, pq_1;

ll dijkstra(int src, int n)
{
    vector<ll> dist(n + 1, LLONG_MAX);
    vector<Edge> parent(n + 1);

    pq.push(mp(0LL, (ll)src));
    dist[src] = 0;
    ll minimum_cost = 0;

    while (!pq.empty())
    {
        pll frm = pq.top();
        pq.pop();
        for (auto [to, weight, iid] : graph[frm.S])
        {
            if (dist[to] > dist[frm.S] + (ll)weight)
            {
                dist[to] = dist[frm.S] + weight;
                parent[to].e = frm.S, parent[to].w = weight, parent[to].id = iid;
                pq.push(mp(dist[to], (ll)to));
            }
            else if (dist[to] == dist[frm.S] + (ll)weight and weight < parent[to].w)
            {
                parent[to].e = frm.S, parent[to].w = weight, parent[to].id = iid;
            }
        }
    }

    for (int i = 2; i <= n; i++)
    {
        minimum_cost += parent[i].w;
        ans.push(parent[i].id);
    }

    return minimum_cost;
}

ll prim(int src, int n)
{
    vector<ll> dist(n + 1, LLONG_MAX);
    vector<int> inMST(n + 1, 0);
    ll cost = 0;

    pq_1.push(mp(0LL, (ll)src));
    dist[src] = 0LL;

    while (!pq_1.empty())
    {
        pll frm = pq_1.top();
        pq_1.pop();

        if (inMST[frm.S] == 1)
        {
            continue;
        }

        inMST[frm.S] = 1;
        cost += frm.F;
        for (auto i : graph[frm.S])
        {
            int to = i.e, weight = i.w;
            if (inMST[to] == 0 and dist[to] > (ll)weight)
            {
                dist[to] = (ll)weight;
                pq_1.push(mp(dist[to], (ll)to));
            }
        }
    }

    return cost;
}

int main()
{
    AC;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int s, e, w;
        cin >> s >> e >> w;
        Edge edge(e, w, i + 1);
        graph[s].pb(edge);
        edge.e = s;
        graph[e].pb(edge);
    }

    ll cost_shortest_path = dijkstra(1, n);
    ll cost_spanning_tree = prim(1, n);
    //fprintf(stderr, "dijkstra: %lld, prim: %lld", cost_shortest_path, cost_spanning_tree);
    if (cost_shortest_path == cost_spanning_tree)
    {
        cout << "Yes\n";
        while (!ans.empty())
        {
            cout << ans.top() << " ";
            ans.pop();
        }
    }
    else
    {
        cout << "No";
    }

    return 0;
}