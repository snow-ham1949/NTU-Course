#include <iostream>
#include <utility>
#include <stack>

using namespace std;

typedef long long ll;

const int maxn = 100000 + 10;
const ll inf = 1000000000000000000 + 10;

#define f first
#define s second

ll a[maxn];

void solve(int flag)
{
    int ans_index[maxn];            // ans_index: memory ans array index order
    pair<ll, int> max_pos, max_neg; // {max value, the last element's index of the max value}
    int used_pos = -1, used_neg = -1;

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &(a[i]));
        ans_index[i] = i;
    }

    max_pos.f = max_neg.f = -inf;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
        {
            if (used_neg == -1)
            {
                if (a[i] > max_pos.f)
                {
                    max_pos.f = a[i], max_pos.s = i;
                }
            }
            else
            {
                if (max_neg.f > 0)
                {
                    if (max_pos.f < max_neg.f + a[i])
                    {
                        max_pos.f = max_neg.f + a[i], max_pos.s = i;
                        ans_index[i] = max_neg.s;
                    }
                }
                else
                {
                    if (max_pos.f < a[i])
                    {
                        max_pos.f = a[i], max_pos.s = i;
                    }
                }
            }
            used_pos = 1;
        }
        else if (a[i] < 0)
        {
            if (used_pos == -1)
            {
                if (a[i] > max_neg.f)
                {
                    max_neg.f = a[i], max_neg.s = i;
                }
            }
            else
            {
                if (max_pos.f > 0)
                {
                    if (max_neg.f < max_pos.f + a[i])
                    {
                        max_neg.f = max_pos.f + a[i], max_neg.s = i;
                        ans_index[i] = max_pos.s;
                    }
                }
                else
                {
                    if (max_neg.f < a[i])
                    {
                        max_neg.f = a[i], max_neg.s = i;
                    }
                }
            }
            used_neg = 1;
        }
        else // a[i] == 0
        {
            if (used_neg == -1 and used_pos == -1)
            {
                max_pos.f = 0, max_pos.s = i;
                max_neg.f = 0, max_pos.s = i;
            }
            else if (used_neg == 1 and used_pos == -1)
            {
                if (max_neg.f < 0)
                {
                    max_neg.f = 0, max_neg.s = i;
                    ans_index[i] = i;
                }
                else
                {
                    ans_index[i] = max_neg.s;
                }
                max_pos.f = max_neg.f, max_pos.s = i;
            }
            else if (used_neg == -1 and used_pos == 1)
            {
                if (max_pos.f < 0)
                {
                    max_pos.f = 0, max_pos.s = i;
                }
                else
                {
                    ans_index[i] = max_pos.s;
                }
                max_neg.f = max_pos.f, max_neg.s = i;
            }
            else // used_neg == 1 and used_pos == 1
            {
                if (max_pos.f > max_neg.f)
                {
                    if (max_pos.f < 0)
                    {
                        max_pos.f = max_neg.f = 0;
                        max_pos.s = max_neg.s = i;
                    }
                    else
                    {
                        ans_index[i] = max_pos.s;
                        max_pos.s = i;
                        max_neg.f = max_pos.f;
                        max_neg.s = i;
                    }
                }
                else
                {
                    if (max_neg.f < 0)
                    {
                        max_neg.f = max_pos.f = 0;
                        max_neg.s = max_pos.f = i;
                    }
                    else
                    {
                        ans_index[i] = max_neg.s;
                        max_neg.s = i;
                        max_pos.f = max_neg.f;
                        max_pos.s = i;
                    }
                }
            }
            used_pos = used_neg = 1;
        }

        //printf("max_pos: %lld, max_neg: %lld\n", max_pos.f, max_neg.f);
    }
    /*
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", i, ans_index[i]);
    }
    */
    // TODOs: 處理輸出
    pair<ll, int> tmp;
    if (used_pos == -1 and used_neg == -1)
    {
        tmp.f = tmp.s = 1;
    }
    else if (used_pos == 1 and used_neg == -1)
    {
        tmp = max_pos;
    }
    else if (used_pos == -1 and used_neg == 1)
    {
        tmp = max_neg;
    }
    else
    {
        if (max_pos.f > max_neg.f)
        {
            tmp = max_pos;
        }
        else
        {
            tmp = max_neg;
        }
    }

    printf("%lld\n", tmp.f);

    stack<int> ans_stk; // for output
    int id = tmp.second;
    // printf("id: %d\n", id);
    if (flag == 1)
    {
        while (ans_index[id] != id)
        {
            ans_stk.push(id);
            id = ans_index[id];
        }

        printf("%lu %d", ans_stk.size() + 1, id + 1);
        while (!ans_stk.empty())
        {
            printf(" %d", ans_stk.top() + 1);
            ans_stk.pop();
        }
        printf("\n");
    }
}

int main()
{
    int t, flag;
    scanf("%d%d", &t, &flag);

    while (t--)
    {
        solve(flag);
    }

    return 0;
}

/*

3 1
1
-1
3
5 0 1
4
-1 -2 -3 -4

*/

/*
1 1 
3
5 0 1
*/