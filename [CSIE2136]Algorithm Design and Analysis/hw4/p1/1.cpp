/* discuss with p10922001 黃佳琪、b07207063 廖政華 */

#include "ypglpk.hpp"
#include <bits/stdc++.h>

using namespace std;

#define AC                       \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
#define pb(a) push_back(a)
#define rep(i, j, k) for (int i = j; i < k; i++)

const int maxn = 80;

void DFS(bitset<maxn> R, bitset<maxn> P, bitset<maxn> X, vector<bitset<maxn> > &maxClique_vec, vector<vector<int> > &edge, int n) // find all maxClique
{
    bitset<maxn> PorX = P | X;

    if (PorX.none())
    {
        maxClique_vec.pb(R);
    }
    else
    {
        size_t id = 0;
        int pivot = -1, maxNeighbor = -1;
        while ((int)id < n && PorX.any())
        {
            if (PorX.test(id))
            {
                int Neighbor = edge[id].size();
                if (Neighbor > maxNeighbor)
                {
                    maxNeighbor = Neighbor;
                    pivot = id;
                }
            }
            id++;
        }

        bitset<maxn> pivotNeighbor;
        rep(i, 0, maxNeighbor)
        {
            pivotNeighbor.set(edge[pivot][i]);
        }

        bitset<maxn> tmp; // P \ NeighborofPivot
        rep(i, 0, n)
        {
            tmp[i] = P[i] & (~pivotNeighbor[i]);
        }

        size_t v = 0;
        while ((int)v < n && tmp.any())
        {
            if (tmp.test(v))
            {
                bitset<maxn> vNeighbor;
                rep(i, 0, int(edge[v].size()))
                {
                    vNeighbor.set(edge[v][i]);
                }

                bitset<maxn> V;
                V.set(v);

                DFS(R | V, P & vNeighbor, X & vNeighbor, maxClique_vec, edge, n);
                P.set(v, 0);
                X | V;
            }
            v++;
        }
    }

    return;
}

void solve(vector<vector<int> > &edge, int n)
{
    bitset<maxn> R, P, X;

    rep(i, 0, n)
    {
        P.set(i);
    }

    vector<bitset<maxn> > maxClique_vec;
    DFS(R, P, X, maxClique_vec, edge, n);

    int sz = maxClique_vec.size();

    vector<vector<double> > A(2 * sz + n, vector<double>(sz, 0));
    vector<double> b(2 * sz + n, 0);
    vector<double> c(sz, -1);
    vector<bool> isint(sz, true);

    // constraint: 0 <= x <= 1
    rep(i, 0, sz)
    {
        A[i][i] = b[i] = 1;
        A[i + sz][i] = -1;
    }

    rep(i, 2 * sz, 2 * sz + n)
    {
        b[i] = -1;
    }

    vector<vector<int> > clique(sz, vector<int>());
    rep(i, 0, sz)
    {
        bitset<maxn> tmp = maxClique_vec[i];
        size_t id = 0;
        while ((int)id < n && tmp.any())
        {
            if (tmp.test(id))
            {
                clique[i].pb(id);
                A[2 * sz + id][i] = -1;
            }
            id++;
        }
    }

    vector<double> y = ypglpk::mixed_integer_linear_programming(A, b, c, isint).second;
    vector<vector<int> > ans;
    vector<bool> pick(n, false);

    rep(i, 0, sz)
    {
        if (!y[i])
        {
            continue;
        }
        vector<int> PickClique;
        for (auto &v : clique[i])
        {
            if (!pick[v])
            {
                PickClique.pb(v);
                pick[v] = true;
            }
        }
        if (!PickClique.empty())
        {
            ans.pb(PickClique);
        }
    }

    int times = ans.size();
    cout << times << "\n";
    rep(i, 0, times)
    {
        int vertices = ans[i].size();
        cout << vertices << " ";
        rep(j, 0, vertices)
        {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int> > edge(n, vector<int>());
        rep(i, 0, m)
        {
            int u, v;
            cin >> u >> v;
            edge[u].pb(v);
            edge[v].pb(u);
        }

        solve(edge, n);
    }

    return 0;
}