/* discuss with 花雲鴻 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>

using namespace std;

#define pb(a) push_back(a)

typedef struct Point
{
    int x, y;
} Point;

typedef long long ll;

const int maxn = 200000 + 10;

Point p[maxn];

bool cmp_x(Point a, Point b)
{
    return a.x < b.x;
}

bool cmp_y1(const Point &a, const Point &b)
{
    return a.y > b.y;
}

bool cmp_y2(const Point &a, const Point &b)
{
    return a.y < b.y;
}

ll ans;

void mergesort(int l, int r)
{
    if (l == r or l + 1 == r)
    {
        return;
    }
    int mid = l + (r - l) / 2;
    mergesort(l, mid);
    mergesort(mid, r);

    // count
    stack<Point> stk_left;
    vector<Point> stk_right;
    stk_left = stack<Point>();
    stk_right.clear();
    Point block;
    int ptr_right = mid;

    // upper case
    for (int i = l; i < mid; i++)
    {
        // choose the point which will block p[i] to connect points on the other side
        while (!stk_left.empty() and (stk_left.top().x < p[i].x))
        {
            stk_left.pop();
        }
        if (stk_left.empty())
        {
            block.x = maxn, block.y = maxn;
        }
        else
        {
            block = stk_left.top();
        }

        // extend the right boundary to find how many point it can connect
        while (ptr_right < r and p[ptr_right].y > p[i].y)
        {
            /*
            for (auto &v : stk_right)
            {
                printf("%d %d\n", v.x, v.y);
            }
            */
            while (!stk_right.empty() and ((stk_right.end() - 1)->x > p[ptr_right].x))
            {
                stk_right.pop_back();
            }
            stk_right.pb(p[ptr_right]);
            ptr_right++;
        }

        int high = lower_bound(stk_right.begin(), stk_right.end(), block, cmp_y1) - stk_right.begin();
        int low = lower_bound(stk_right.begin(), stk_right.end(), p[i], cmp_y1) - stk_right.begin();
        ans += (low - high);
        stk_left.push(p[i]);
        /*
        printf("l: %d, r: %d, x: %d, y: %d\n", l, r, p[i].x, p[i].y);
        //printf("block: %d %d\n", block.x, block.y);
        printf("high: %d, low: %d\n", high, low);
        for (auto &v : stk_right)
        {
            printf("%d %d\n", v.x, v.y);
        }
        */
    }

    // clear
    while (!stk_left.empty())
    {
        stk_left.pop();
    }
    stk_right.clear();

    // lower case
    ptr_right = r - 1;
    for (int i = mid - 1; i >= l; i--)
    {
        // choose the point which will block p[i] to connect points on the other side
        while (!stk_left.empty() and (stk_left.top().x < p[i].x))
        {
            stk_left.pop();
        }
        if (stk_left.empty())
        {
            block.x = maxn, block.y = -1;
        }
        else
        {
            block = stk_left.top();
        }

        // extend the right boundary to find how many point it can connect
        while (ptr_right >= mid and (p[ptr_right].y < p[i].y))
        {
            while (!stk_right.empty() and ((stk_right.end() - 1)->x > p[ptr_right].x))
            {
                stk_right.pop_back();
            }
            stk_right.pb(p[ptr_right]);
            ptr_right--;
        }
        /*
        int high = lower_bound(stk_right.begin(), stk_right.end(), p[i], cmp_y1) - stk_right.begin();
        int low = lower_bound(stk_right.begin(), stk_right.end(), block, cmp_y1) - stk_right.begin();
        */

        int high = lower_bound(stk_right.begin(), stk_right.end(), block, cmp_y2) - stk_right.begin();
        int low = lower_bound(stk_right.begin(), stk_right.end(), p[i], cmp_y2) - stk_right.begin();

        ans += (low - high);
        stk_left.push(p[i]);
        /*
        printf("l: %d, r: %d, x: %d, y: %d\n", l, r, p[i].x, p[i].y);
        for (auto &v : stk_right)
        {
            printf("%d %d\n", v.x, v.y);
        }
        */
    }

    // sort
    int ptr_left = l, id = l;
    ptr_right = mid;
    Point tmp[maxn];
    while (ptr_left < mid and ptr_right < r)
    {
        if (p[ptr_left].y > p[ptr_right].y)
        {
            tmp[id++] = p[ptr_left++];
        }
        else
        {
            tmp[id++] = p[ptr_right++];
        }
    }
    while (ptr_left < mid)
    {
        tmp[id++] = p[ptr_left++];
    }
    while (ptr_right < r)
    {
        tmp[id++] = p[ptr_right++];
    }
    for (int i = l; i < r; i++)
    {
        p[i] = tmp[i];
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &(p[i].x), &(p[i].y));
    }

    sort(p, p + n, cmp_x);
    ans = 0;
    mergesort(0, n);

    printf("%lld\n", ans);

    return 0;
}