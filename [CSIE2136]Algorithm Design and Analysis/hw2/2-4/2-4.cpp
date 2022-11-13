/* discuss with 林天行 */

#include <iostream>
#include <vector>
#include <queue>

#define pb(a) push_back(a)
#define ppb pop_back()
#define ppf pop_front()
#define mp make_pair
#define pii pair<int, int>
#define plii pair<ll, pii> // val, id_1, id_2
#define small plii, vector<plii>, greater<plii>
#define f first
#define s second
#define ll long long

const int maxn = 1000000 + 10;
const ll inf = 10000000000000000;

using namespace std;

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

    ll max_sweetness[maxn];
    priority_queue<small> pq_1, pq_2;
    pii minusone;
    minusone.f = minusone.s = -1;
    vector<pii> id_1(n + 10, minusone), id_2(n + 10, minusone);
    vector<int> index;
    ll sum = 0;
    int seg = 0, prev = -1, first_index = -1;
    for (int i = 0; i < n; ++i)
    {
        int cur = v[i], id = i;
        int j = i;
        while (j < n and sign(v[i]) == sign(v[j]))
        {
            if (v[j] > cur)
            {
                cur = v[j];
                id = j;
            }
            ++j;
        }

        sum += cur;
        index.pb(id);
        i = j - 1;
        seg++;

        if (seg > 1)
        {
            plii tmp;
            tmp.f = v[prev] + v[id], tmp.s.f = prev, tmp.s.s = id;
            pq_1.push(tmp), pq_2.push(tmp);
        }
        prev = id;
        if (first_index == -1)
        {
            first_index = id;
        }
    }

    for (int i = 0; i < seg - 1; i++)
    {
        id_1[index[i]].s = index[i + 1];
        id_2[index[i]].s = index[i + 1];
    }
    id_1[index[seg - 1]].s = index[0];
    id_2[index[seg - 1]].s = index[0];

    for (int i = seg - 1; i > 0; i--)
    {
        id_1[index[i]].f = index[i - 1];
        id_2[index[i]].f = index[i - 1];
    }
    id_1[index[0]].f = index[seg - 1];
    id_2[index[0]].f = index[seg - 1];

    plii tmp;
    tmp.f = v[index[0]] + v[index[seg - 1]], tmp.s.f = index[seg - 1], tmp.s.s = index[0];
    pq_1.push(tmp);
    pq_2.push(tmp);

    for (int i = seg + 1; i <= n; ++i)
    {
        max_sweetness[i] = 0;
    }

    max_sweetness[seg] = sum;

    for (int i = seg - 2; i > 0; i -= 2)
    {
        while (!pq_1.empty() and (id_1[pq_1.top().s.f].f == -1 || id_1[pq_1.top().s.f].s == -1 || id_1[pq_1.top().s.s].f == -1 || id_1[pq_1.top().s.s].s == -1))
        {
            pq_1.pop();
        }
        //fprintf(stderr, "val: %lld, id1: %d, id2: %d\n", pq_1.top().f, pq_1.top().s.f, pq_1.top().s.s);

        max_sweetness[i] = max_sweetness[i + 2] - pq_1.top().f;

        plii tmp = pq_1.top();
        id_1[id_1[tmp.s.s].s].f = id_1[tmp.s.f].f;
        id_1[id_1[tmp.s.f].f].s = id_1[tmp.s.s].s;
        int prev = id_1[tmp.s.f].f, next = id_1[tmp.s.s].s;
        plii tmpp;
        tmpp.f = v[prev] + v[next], tmpp.s.f = prev, tmpp.s.s = next;
        pq_1.push(tmpp);
        id_1[tmp.s.f].s = -1;
        id_1[tmp.s.f].f = -1;
        id_1[tmp.s.s].s = -1;
        id_1[tmp.s.s].f = -1;
    }

    if (sum - v[index[0]] > sum - v[index[seg - 1]])
    {
        max_sweetness[seg - 1] = sum - v[index[0]];
        id_2[id_2[index[0]].s].f = id_2[index[0]].f;
        id_2[id_2[index[0]].f].s = id_2[index[0]].s;
        plii tmp;
        tmp.s.f = id_2[index[0]].f, tmp.s.s = id_2[index[0]].s;
        tmp.f = v[tmp.s.f] + v[tmp.s.s];
        pq_2.push(tmp);
        id_2[index[0]].f = id_2[index[0]].s = -1;
    }
    else
    {
        max_sweetness[seg - 1] = sum - v[index[seg - 1]];
        id_2[id_2[index[seg - 1]].s].f = id_2[index[seg - 1]].f;
        id_2[id_2[index[seg - 1]].f].s = id_2[index[seg - 1]].s;
        plii tmp;
        tmp.s.f = id_2[index[seg - 1]].f, tmp.s.s = id_2[index[seg - 1]].s;
        tmp.f = v[tmp.s.f] + v[tmp.s.s];
        pq_2.push(tmp);
        id_2[index[seg - 1]].f = id_2[index[seg - 1]].s = -1;
    }

    for (int i = seg - 3; i > 0; i -= 2)
    {
        /*
        printf("i: %d\n", i);
        for (int i = 0; i < n; i++)
        {
            printf("index: %d, prev: %d, next: %d\n", i, id_2[i].f, id_2[i].s);
        }
        */
        while (!pq_2.empty() and (id_2[pq_2.top().s.f].f == -1 || id_2[pq_2.top().s.f].s == -1 || id_2[pq_2.top().s.s].f == -1 || id_2[pq_2.top().s.s].s == -1))
        {
            //printf("val: %lld, id1: %d, id2: %d\n", pq_2.top().f, pq_2.top().s.f, pq_2.top().s.s);
            pq_2.pop();
        }
        //printf("OK\n");
        //printf("val: %lld, id1: %d, id2: %d\n", pq_2.top().f, pq_2.top().s.f, pq_2.top().s.s);

        max_sweetness[i] = max_sweetness[i + 2] - pq_2.top().f;

        plii tmp = pq_2.top();
        id_2[id_2[tmp.s.s].s].f = id_2[tmp.s.f].f;
        id_2[id_2[tmp.s.f].f].s = id_2[tmp.s.s].s;
        int prev = id_2[tmp.s.f].f, next = id_2[tmp.s.s].s;
        plii tmpp;
        tmpp.f = v[prev] + v[next], tmpp.s.f = prev, tmpp.s.s = next;
        //printf("val: %lld, id1: %d, id2: %d\n", tmpp.f, tmpp.s.f, tmpp.s.s);
        pq_2.push(tmpp);
        id_2[tmp.s.f].s = -1;
        id_2[tmp.s.f].f = -1;
        id_2[tmp.s.s].s = -1;
        id_2[tmp.s.s].f = -1;
        /*
        for (int i = 0; i < n; i++)
        {
            printf("index: %d, prev: %d, next: %d\n", i, id_2[i].f, id_2[i].s);
        }
        printf("i: %d, finish\n", i);
        */
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