/* discuss with 林天行 */

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <set>

#define pb(a) push_back(a)
#define ppb pop_back()
#define ppf pop_front()
#define pii pair<int, int>
#define plii pair<ll, pii> // val, id_1, id_2
#define iter set<int>::iterator
#define riter set<int>::reverse_iterator
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

    vector<ll> max_sweetness(maxn, 0);
    deque<ll> candies, candies_1;
    priority_queue<small> pq, pq_1;
    set<int> index, index_1; // the index of elements which haven't been delelted
    index.clear(), index_1.clear();
    ll sum = 0, seg = 0;
    int prev = -1;
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
        //printf("id: %d\n", id);
        sum += cur;
        candies.pb(cur);
        index.insert(id);
        index_1.insert(id);
        i = j - 1;
        seg++;
        if (seg > 1)
        {
            plii tmp;
            tmp.f = candies[seg - 1] + candies[seg - 2], tmp.s.f = prev, tmp.s.s = id;
            pq.push(tmp);
            pq_1.push(tmp);
        }
        prev = id;
    }
    plii tmp;
    tmp.f = candies[0] + candies[seg - 1], tmp.s.f = 0, tmp.s.s = prev;
    pq.push(tmp);
    pq_1.push(tmp);

    //printf("sum: %lld, seg: %lld\n", sum, seg);

    printf("OK\n");

    max_sweetness[seg] = sum;

    if (sum - candies[0] > sum - candies[seg - 1])
    {
        max_sweetness[seg - 1] = sum - candies[0];
        candies_1.assign(candies.begin() + 1, candies.end());
        index_1.erase(0);
    }
    else
    {
        max_sweetness[seg - 1] = sum - candies[seg - 1];
        candies_1.assign(candies.begin(), candies.end() - 1);
        index_1.erase(prev);
    }

    printf("OK\n");

    // 最大長度 -> 最大長度-2 -> 最大長度-4 -> ....
    for (int i = seg - 2; i > 0; i -= 2)
    {
        max_sweetness[i] = max_sweetness[i + 2] - pq.top().f;

        iter it1, it2;
        it1 = index.find(pq.top().s.f), it2 = index.find(pq.top().s.s);

        iter tmp1 = index.begin();
        riter tmp2 = index.rbegin();
        int second, rev_second;
        tmp1++;
        second = *tmp1;
        tmp2++;
        rev_second = *tmp2;
        if ((*it1 == *(index.begin()) and *it2 == *(index.rbegin())) or
            (*it1 == *(index.begin()) and *it2 == second) or
            (*it1 == rev_second and *it2 == *(index.rbegin())))
        {
            index.erase(it1);
            index.erase(it2);
            plii tmp;
            tmp.s.f = *(index.begin()), tmp.s.s = *(index.rbegin());
            tmp.f = v[tmp.s.f] + v[tmp.s.s];
            pq.push(tmp);
        }
        else
        {
            it1--, it2++;
            plii tmp;
            tmp.s.f = *(it1), tmp.s.s = *(it2);
            tmp.f = v[tmp.s.f] + v[tmp.s.s];
            pq.push(tmp);
            it1++, it2--;
            index.erase(it1);
            index.erase(it2);
        }

        while (index.count(pq.top().s.f) == 0 || index.count(pq.top().s.s) == 0)
        {
            pq.pop();
        }
    }

    // 最大長度-1 -> 最大長度-3 -> 最大長度-5 -> ....
    for (int i = seg - 3; i > 0; i -= 2)
    {
        while (index_1.count(pq_1.top().s.f) == 0 || index.count(pq_1.top().s.s) == 0)
        {
            pq_1.pop();
        }
        max_sweetness[i] = max_sweetness[i + 2] - pq_1.top().f;

        iter it1, it2;
        it1 = index_1.find(pq_1.top().s.f), it2 = index_1.find(pq_1.top().s.s);

        iter tmp1 = index_1.begin();
        riter tmp2 = index_1.rbegin();
        int second, rev_second;
        tmp1++;
        second = *tmp1;
        tmp2++;
        rev_second = *tmp2;

        if ((*it1 == *(index_1.begin()) and *it2 == *(index_1.rbegin())) or
            (*it1 == *(index_1.begin()) and *it2 == second) or
            (*it1 == rev_second and *it2 == *(index_1.rbegin())))
        {
            index_1.erase(it1);
            index_1.erase(it2);
            plii tmp;
            tmp.s.f = *(index_1.begin()), tmp.s.s = *(index_1.rbegin());
            tmp.f = v[tmp.s.f] + v[tmp.s.s];
            pq_1.push(tmp);
        }
        else
        {
            it1--, it2++;
            plii tmp;
            tmp.s.f = *(it1), tmp.s.s = *(it2);
            tmp.f = v[tmp.s.f] + v[tmp.s.s];
            pq_1.push(tmp);
            it1++, it2--;
            index_1.erase(it1);
            index_1.erase(it2);
        }
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