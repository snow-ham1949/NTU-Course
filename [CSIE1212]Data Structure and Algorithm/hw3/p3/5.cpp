#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<stack<int> > v(k);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        for (int j = 0; j < k; j++)
        {
            if (v[j].empty())
            {
                v[j].push(x);
                break;
            }
            else if (!v[j].empty() and v[j].top() >= x)
            {
                v[j].push(x);
                break;
            }
        }
    }

    vector<int> ans;
    int cnt = 0;
    while (cnt < n)
    {
        vector<pair<int, int> > sorted_top;
        for (int i = 0; i < k; i++)
        {
            if (!v[i].empty()) sorted_top.push_back(make_pair(v[i].top(), i));
        }
        sort(sorted_top.begin(), sorted_top.end());
        ans.push_back(sorted_top[0].first);
        v[sorted_top[0].second].pop();
        cnt++;
    }

    for (int ele: ans)
    {
        cout << ele << " ";
    }

    return 0;
}
