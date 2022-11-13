#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <set>

#define pb(a) push_back(a)
#define ppb pop_back()
#define ppf pop_front()

#define ll long long

const int maxn = 1000000 + 10;
const ll inf = 10000000000000000;

using namespace std;

typedef struct min_and_index
{
    ll minn;
    int id_1, id_2;
} mai;

int sign(int x)
{
    return x > 0 ? 1 : -1;
}

void solve()
{
    int n;
    scanf("%d", &n);

    vector<int> v;
    for (int i = 0; i < n; ++i)
    {
        int x;
        scanf("%d", &x);
        v.pb(x);
    }

    vector<ll> max_sweetness(maxn, 0);
    deque<ll> candies, candies_1;
    ll sum = 0, seg = 0;
    for (int i = 0; i < n; i++)
    {
        int cur = v[i], id = i;
        int j = i;
        while (j < n && sign(v[i]) == sign(v[j]))
        {
            if (v[j] > cur)
            {
                id = j;
            }
            cur = max(v[j], cur);
            ++j;
        }
        //printf("cur: %d\n", cur);
        sum += cur;
        candies.pb(cur);
        i = j - 1;
        seg++;
    }

    //printf("sum: %lld, seg: %lld\n", sum, seg);

    max_sweetness[seg] = sum;

    if (sum - candies[0] > sum - candies[seg - 1])
    {
        max_sweetness[seg - 1] = sum - candies[0];
        candies_1.assign(candies.begin() + 1, candies.end());
    }
    else
    {
        max_sweetness[seg - 1] = sum - candies[seg - 1];
        candies_1.assign(candies.begin(), candies.end() - 1);
    }

    // 最大長度 -> 最大長度-2 -> 最大長度-4 -> ....
    for (int i = seg - 2; i > 0; i -= 2)
    {
        ll takeaway_id = -1, cur_max = -inf;
        for (int j = 0; j <= i; ++j)
        {
            if (cur_max < max_sweetness[i + 2] - candies[j] - candies[j + 1])
            {
                cur_max = max_sweetness[i + 2] - candies[j] - candies[j + 1];
                takeaway_id = j;
            }
        }
        // 拔頭尾
        if (cur_max < max_sweetness[i + 2] - candies[0] - candies[i + 1])
        {
            cur_max = max_sweetness[i + 2] - candies[0] - candies[i + 1];
            takeaway_id = -2;
        }

        if (takeaway_id >= 0) // 不是頭尾
        {
            candies.erase(candies.begin() + takeaway_id, candies.begin() + takeaway_id + 2);
        }
        else
        {
            candies.ppb;
            candies.ppf;
        }

        max_sweetness[i] = cur_max;
    }

    // 最大長度-1 -> 最大長度-3 -> 最大長度-5 -> ....
    for (int i = seg - 3; i > 0; i -= 2)
    {
        ll takeaway_id = -1, cur_max = -inf;
        for (int j = 0; j <= i; ++j)
        {
            if (cur_max < max_sweetness[i + 2] - candies_1[j] - candies_1[j + 1])
            {
                cur_max = max_sweetness[i + 2] - candies_1[j] - candies_1[j + 1];
                takeaway_id = j;
            }
        }
        // 拔頭尾
        if (cur_max < max_sweetness[i + 2] - candies_1[0] - candies_1[i + 1])
        {
            cur_max = max_sweetness[i + 2] - candies_1[0] - candies_1[i + 1];
            takeaway_id = -2;
        }

        if (takeaway_id >= 0) // 不是頭尾
        {
            candies_1.erase(candies_1.begin() + takeaway_id, candies_1.begin() + takeaway_id + 2);
        }
        else
        {
            candies_1.ppb;
            candies_1.ppf;
        }

        max_sweetness[i] = cur_max;
    }

    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", max_sweetness[i]);
    }
    printf("\n");
}

int main()
{

    int t, flag;
    scanf("%d %d", &t, &flag);

    while (t--)
    {
        solve();
    }

    return 0;
}