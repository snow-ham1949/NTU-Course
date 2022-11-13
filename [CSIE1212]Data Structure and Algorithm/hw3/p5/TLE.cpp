#include <bits/stdc++.h>

using namespace std;

int main()
{
    int k, l, flag;
    cin >> k >> l >> flag;
    vector<string> v;
    for (int i = 0; i < k; i++)
    {
        string s; cin >> s;
        v.push_back(s);
    }
    long long ans = 0;
    int ans_1 = -1, ans_2 = -1;
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            int diff = 0;
            for (int ch = 0; ch < l; ch++)
            {
                if (v[i][ch] != v[j][ch])
                {
                    diff++;
                }
            }
            if (diff <= 1)
            {
                ans++;
                ans_1 = i, ans_2 = j;
            }
        }
    }

    ans ? cout << "Yes\n" : cout << "No\n";
    if (flag)
    {
        cout << ans << "\n";
    }
    else
    {
        if (ans) cout << ans_2 << " " << ans_1 << "\n";
    }

    return 0;
}