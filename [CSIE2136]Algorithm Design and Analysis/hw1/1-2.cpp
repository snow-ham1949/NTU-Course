/* discuss with: 花雲鴻 */

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef struct Element
{
    ll z, p;
} Ele;

const int maxn = 2000000 + 6;

Ele arr[maxn], tmp[maxn];
ll n, a, b, c, ans;

bool cmp(const Ele &a, const Ele &b)
{
    return a.z < b.z;
}

void merge(int l, int r) // [l, r)
{
    if (l == r or l + 1 == r)
    {
        return;
    }

    int mid = l + (r - l) / 2;
    ll mid_z = arr[mid].z;
    merge(l, mid);
    merge(mid, r);

    // count
    int ptr_right, ptr1 = l, mid_z_cnt = 0;
    for (ptr_right = mid; ptr_right < r; ptr_right++)
    {
        while (ptr1 < mid and (a * arr[ptr_right].p - c > b * arr[ptr1].p))
        {
            if (arr[ptr1].z == mid_z)
            {
                mid_z_cnt++;
            }
            ptr1++;
        }
        ans += (ptr1 - l);
        if (arr[ptr_right].z == mid_z)
        {
            ans -= mid_z_cnt;
        }
    }

    // merge
    ptr1 = l, ptr_right = mid;
    int id = l;
    while (ptr1 < mid and ptr_right < r)
    {
        if (arr[ptr1].p < arr[ptr_right].p)
        {
            tmp[id++] = arr[ptr1++];
        }
        else
        {
            tmp[id++] = arr[ptr_right++];
        }
    }

    while (ptr1 < mid)
    {
        tmp[id++] = arr[ptr1++];
    }
    while (ptr_right < r)
    {
        tmp[id++] = arr[ptr_right++];
    }

    for (int i = l; i < r; i++)
    {
        arr[i] = tmp[i];
    }

    //printf("l: %d, r: %d, ans: %lld\n", l, r, ans);
}

int main()
{
    scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld%lld", &(arr[i].p), &(arr[i].z));
    }

    sort(arr, arr + n, cmp);
    ans = 0;
    merge(0, n);

    printf("%lld", ans);

    return 0;
}

/* Sample Input 1

4 1 0 0
0 0
0 0
0 0
0 0

*/

/* Sample Output 1

0 

*/

/* Sample Input 2

4 1 1 2
1 47
3 22
7 81
5 65

*/

/* Sample Output 2

3 

*/

/* Sample Input 3

4 2021 0 1111111
123 4
567 8
901 2
345 6

*/

/* Sample Output 3

3 

*/
