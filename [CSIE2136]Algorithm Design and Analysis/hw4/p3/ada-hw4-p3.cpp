#include "ada-hw4-p3.h"
#include <bits/stdc++.h>

using namespace std;

#define rep(i, j, k) for (int i = j; i < k; i++)
#define pb(a) push_back(a)

// discuss with p10922001 黃佳琪

// feel free to use global variables
vector<int> contest;

vector<int> ID;
map<int, int> ConcealTogether;
vector<bool> Concealed;

const int maxn = 4000 + 10;
// set<int> Concealed;

vector<int> init(int N)
{
    // ID.resize(N);
    Concealed.resize(maxn, false);
    rep(i, 0, N)
    {
        // ID[i] = i;
        ID.pb(i);
    }

    if (N == 1)
    {
        return contest;
    }

    // contest id: [0, 1, 2, 3, 4]
    // score: [1, 5, 8, 3, 6]
    int ptr_l = 0, ptr_r = 1;
    while (ptr_r < N)
    {
        int a = ID[ptr_l], b = ID[ptr_r];
        if (!compare(a, b))
        {
            contest.pb(a), contest.pb(b);
            // Concealed.insert(a);
            // Concealed.insert(b);
            Concealed[a] = Concealed[b] = true;
            ConcealTogether[a] = b, ConcealTogether[b] = a;
            ptr_r++;
            while (ptr_l >= 0 and Concealed[ID[ptr_l]])
            {
                ptr_l--;
            }
            if (ptr_l < 0)
            {
                ptr_r++;
                ptr_l = ptr_r - 1;
            }
        }
        else
        {
            ptr_l = ptr_r;
            ptr_r++;
        }
    }
    return contest;
}

vector<int> insert(int p, int id)
{
    ID.insert(ID.begin() + p, id);
    int sz = ID.size();
    // check left
    int ptr_l = p - 1;
    while (ptr_l >= 0 and Concealed[ID[ptr_l]])
    {
        ptr_l--;
    }
    // fprintf(stderr, "l: %d\n", ptr_l);
    if (ptr_l >= 0 and !compare(ID[ptr_l], id))
    {
        // Concealed.insert(ID[ptr_l]);
        // Concealed.insert(id);
        Concealed[ID[ptr_l]] = Concealed[id] = true;
        ConcealTogether[id] = ID[ptr_l], ConcealTogether[ID[ptr_l]] = id;
        contest.pb(ID[ptr_l]), contest.pb(id);
    }
    else
    {
        // check right
        int ptr_r = p + 1;
        while (ptr_r < sz and Concealed[ID[ptr_r]])
        {
            ptr_r++;
        }
        // fprintf(stderr, "r: %d\n", ptr_r);
        if (ptr_r < sz and !compare(id, ID[ptr_r]))
        {
            // Concealed.insert(ID[ptr_r]);
            // Concealed.insert(id);
            Concealed[ID[ptr_r]] = Concealed[id] = true;
            ConcealTogether[id] = ID[ptr_r], ConcealTogether[ID[ptr_r]] = id;
            contest.pb(ID[ptr_r]), contest.pb(id);
        }
    }

    return contest;
}

vector<int> remove(int p)
{
    int id = ID[p];
    if (!Concealed[id])
    {
        ID.erase(ID.begin() + p);
        // fprintf(stderr, "Case 1\n");
        return contest;
    }

    int PairID = ConcealTogether[id];
    Concealed[PairID] = false;
    contest.erase(remove(contest.begin(), contest.end(), PairID), contest.end());
    contest.erase(remove(contest.begin(), contest.end(), id), contest.end());

    int ptr = distance(ID.begin(), find(ID.begin(), ID.end(), PairID));
    // fprintf(stderr, "ptr: %d\n", ptr);
    int ptr_l = ptr - 1;
    while (ptr_l >= 0 and Concealed[ID[ptr_l]])
    {
        ptr_l--;
    }
    if (ptr_l >= 0 and !compare(ID[ptr_l], PairID))
    {
        // Concealed.insert(ID[ptr_l]);
        // Concealed.insert(PairID);
        Concealed[ID[ptr_l]] = Concealed[PairID] = true;
        ConcealTogether[PairID] = ID[ptr_l], ConcealTogether[ID[ptr_l]] = PairID;
        contest.pb(ID[ptr_l]), contest.pb(PairID);
    }
    else
    {
        // check right
        int ptr_r = ptr + 1, sz = ID.size();
        while (ptr_r < sz and Concealed[ID[ptr_r]])
        {
            ptr_r++;
        }
        if (ptr_r < sz and !compare(PairID, ID[ptr_r]))
        {
            // Concealed.insert(ID[ptr_r]);
            // Concealed.insert(PairID);
            Concealed[ID[ptr_r]] = Concealed[PairID] = true;
            ConcealTogether[PairID] = ID[ptr_r], ConcealTogether[ID[ptr_r]] = PairID;
            contest.pb(ID[ptr_r]), contest.pb(PairID);
        }
    }
    ID.erase(ID.begin() + p);
    return contest;
}
