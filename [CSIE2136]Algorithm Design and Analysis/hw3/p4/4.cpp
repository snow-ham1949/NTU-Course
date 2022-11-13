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
    Time : 2021:11:25  00:40:19
***/

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;

class Node
{
public:
    int sz;
    int pos;
    Node *parent;
    Node(int pos)
    {
        this->sz = 0, this->pos = pos, this->parent = this;
    }
};

Node *cats[maxn];
map<int, Node *> mp;
ll crowdness;

ll C(ll n)
{
    return n * (n - 1) / 2;
}

Node *Find(Node *a)
{
    if (a != a->parent)
    {
        a->parent = Find(a->parent);
    }
    return a->parent;
}

void PutFood(int point, int radius)
{
    if (!mp.count(point))
    {
        mp[point] = new Node(point);
    }
    auto it = mp.find(point);
    //fprintf(stderr, "-----start processing put food-----\n");
    crowdness -= C(it->S->sz);
    auto it_lower = mp.lower_bound(point - radius);
    ll cnt = 0;
    //fprintf(stderr, "put food step 1 ok\n");
    while (it_lower != mp.end() and it_lower->F <= point + radius)
    {
        //fprintf(stderr, "move cat from coordinate %d , fartest should be %d\n", it_lower->F, point + radius);
        if (it_lower->F == it->F)
        {
            it_lower++;
            continue;
        }
        it_lower->S->parent = mp[point];
        mp[point]->sz += it_lower->S->sz, crowdness -= C(it_lower->S->sz);
        it_lower = mp.erase(it_lower);
    }
    crowdness += C(mp[point]->sz);

    cout << crowdness << "\n";
}

void MoveCat(int id, int coordinate)
{
    Node *parent = Find(cats[id]);
    crowdness -= C(parent->sz);
    parent->sz--;
    crowdness += C(parent->sz);
    if (parent->sz == 0)
    {
        mp.erase(parent->pos);
        delete parent;
    }
    if (!mp.count(coordinate))
    {
        mp[coordinate] = new Node(coordinate);
    }
    cats[id] = mp[coordinate];
    crowdness -= C(mp[coordinate]->sz);
    mp[coordinate]->sz++;
    crowdness += C(mp[coordinate]->sz);
    cout << crowdness << "\n";
}

int main()
{
    AC;
    int n, q;
    cin >> n >> q;
    int coordinate;
    crowdness = 0;
    for (int id = 1; id <= n; id++)
    {
        cin >> coordinate;
        auto it = mp.find(coordinate);
        if (it != mp.end())
        {
            it->S->sz++;
            cats[id] = it->S;
        }
        else
        {
            Node *node = new Node(coordinate);
            mp[coordinate] = node;
            cats[id] = node;
            node->sz++;
        }
    }

    ll size;

    for (auto &it : mp)
    {
        //fprintf(stderr, "coordinate: %d, size: %d, pos: %d\n", i.F, i.S->sz, i.S->pos);
        crowdness += C(it.S->sz);
    }
    //fprintf(stderr, "crowdness: %lld\n", crowdness);

    int type, point, radius, id;
    while (q--)
    {
        cin >> type;
        if (type == 1) // put food
        {
            cin >> point >> radius;
            PutFood(point, radius);
        }
        else // move cats
        {
            cin >> id >> coordinate;
            MoveCat(id, coordinate);
        }
    }

    return 0;
}