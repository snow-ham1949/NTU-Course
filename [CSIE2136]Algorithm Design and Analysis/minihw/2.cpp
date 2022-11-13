#include <algorithm>
#include <iostream>
#include <queue>
#include <string.h>
#include <utility>
#include <vector>

using namespace std;

#define pb(a) push_back(a)
#define pii pair<int, int>
#define mp(a, b) make_pair(a, b)

vector<vector<int> > g;
vector<bool> visited;
priority_queue<pii, vector<pii>, greater<pii> > pq;
int n, m;

void dfs(int i)
{
    printf("%d ", i);
    visited[i] = 1;
    for (int j = 0; j < g[i].size(); j++)
    {
        if (!visited[g[i][j]])
        {
            dfs(g[i][j]);
        }
    }
}

inline void bfs()
{
    pq.push(mp(0, 1));
    visited[1] = 1;

    while (!pq.empty())
    {
        pii go = pq.top();
        pq.pop();
        printf("%d ", go.second);
        for (auto v : g[go.second])
        {
            if (!visited[v])
            {
                visited[v] = 1;
                pq.push(mp(go.first + 1, v));
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    g.resize(n + 1, vector<int>());
    visited.resize(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int s, e;
        scanf("%d %d", &s, &e);
        g[s].pb(e);
        g[e].pb(s);
    }

    for (int i = 1; i <= n; i++)
    {
        sort(g[i].begin(), g[i].end());
    }

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }
    printf("\n");

    visited.assign(n + 1, 0);

    bfs();

    return 0;
}
