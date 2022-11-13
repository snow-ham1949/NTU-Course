#include <iostream>

using namespace std;

typedef long long ll;

const int maxn = 200000 + 6;
const ll inf = 1000000000000000000 + 9;

ll demo[maxn], dp[maxn];
ll n, x, y, z;

int main()
{

    scanf("%lld%lld%lld%lld", &n, &x, &y, &z);
    for (ll i = 0; i < n; i++)
    {
        scanf("%lld", &(demo[i]));
    }

    dp[1] = x * demo[0] + z * demo[1];
    ll max_rating = dp[1];
    for (int i = 2; i < n; i++)
    {
        dp[i] = max(dp[i - 1] - z * demo[i - 1] + y * demo[i - 1] + z * demo[i], x * demo[i - 1] + z * demo[i]);
        max_rating = max(dp[i], max_rating);
    }

    printf("%lld", max_rating);

    return 0;
}

/* Sample Input 1

6 1 1 1
-12 7 -127 -1 -2 -7

*/

/* Sample Output 1

-3 

*/

/* Sample Input 2

8 59 4 87
0 8 -7 0 5 0 -2 9

*/

/* Sample Output 2

1239 

*/

/* Sample Input 3

3 5358 5926 3141
1 10000 100000000

*/

/* Sample Output 3

314159265358

*/
