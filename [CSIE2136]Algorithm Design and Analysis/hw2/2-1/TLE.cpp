#include <climits>
#include <cstring>
#include <iostream>
#include <stack>
#include <stdio.h>
#include <string>
using namespace std;
int main()
{
    int T;
    scanf("%d ", &T);
    while (T--)
    {
        int n, m, k;
        string in_str;
        scanf("%d%d%d ", &n, &m, &k);
        long long a[n + 2][m + 2], s[n + 2][m + 2];
        pair<int, int> bt[n + 2][m + 2];
        memset(s, 0, sizeof(s));
        // memset(bt, 0, sizeof(bt))
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> in_str;
                if (in_str == "X")
                    a[i][j] = LLONG_MIN;
                else
                    a[i][j] = stoll(in_str);
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (i == 1 && j == 1)
                {
                    s[i][j] = 0;
                    continue;
                }
                if (a[i][j] == LLONG_MIN)
                    continue;
                pair<int, int> bt_now = make_pair(INT_MIN, INT_MIN);
                long long now = LLONG_MIN;
                for (int p = i - k; p <= i; p++)
                {
                    for (int q = j - k; q <= j; q++)
                    {
                        int dis = abs(p - i) + abs(q - j);
                        if (dis > k || dis < 1 || p < 1 || p > n || q < 1 || q > m)
                            continue;
                        if (a[p][q] == LLONG_MIN || s[p][q] == LLONG_MIN)
                            continue;
                        if (s[p][q] + a[i][j] > now)
                        {
                            now = s[p][q] + a[i][j];
                            bt_now = make_pair(p, q);
                        }
                    }
                }
                bt[i][j] = bt_now;
                s[i][j] = now;
            }
        }
        //  printf("\n");
        // for (int i = 1; i <= n; i++)
        // {
        //     for (int j = 1; j <= m; j++)
        //     {
        //         printf("%lld ", s[i][j]);
        //     }
        //     printf("\n");
        // }
        if (s[n][m] == LLONG_MIN)
        {
            printf("Impassable\n");
        }
        else
        {
            printf("Passable\n");
            printf("%lld\n", s[n][m]);
            stack<pair<int, int> > stk;
            pair<int, int> p;
            p = make_pair(n, m);
            stk.push(p);
            while (p != make_pair(1, 1))
            {
                p = bt[p.first][p.second];
                stk.push(p);
            }
            printf("%lu\n", stk.size());
            while (!stk.empty())
            {
                printf("%d %d\n", stk.top().first, stk.top().second);
                stk.pop();
            }
        }
    }
}