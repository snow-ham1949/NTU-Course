/* discuss with: 黃佳琪、沈家睿、李旻翰 */

#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

#define ll long long

class Task
{
public:
    int s, e, x, p;
    Task() {}
    Task(int s, int e, int x, int p)
    {
        this->s = s, this->e = e, this->x = x, this->p = p;
    }
};

int cmp_p(Task &a, Task &b)
{
    return a.p > b.p;
}

int cmp_s(Task &a, Task &b)
{
    return a.s < b.s;
}

struct cmp_e
{
    bool operator()(Task &a, Task &b)
    {
        return a.e > b.e;
    }
};

vector<Task> task;

ll solve(int id)
{
    vector<Task> tmp_task;
    int num = id + 1;
    tmp_task.assign(task.begin(), task.begin() + num);
    sort(tmp_task.begin(), tmp_task.end(), cmp_s);

    //fprintf(stderr, "OK\n");
    priority_queue<Task, vector<Task>, cmp_e> pq;

    Task cur;
    int start, end, i = 0, time = tmp_task[0].s;
    ll unit = 0;
    while (i < num or !pq.empty())
    {
        if (i < num)
        {
            start = tmp_task[i].s;
        }

        //fprintf(stderr, "%d Choose best\n", i);
        while (pq.empty() or (i < num and time <= tmp_task[i].e and tmp_task[i].s == start and time >= start))
        {
            pq.push(tmp_task[i]);
            i++;
        }

        //fprintf(stderr, "%d start processing\n", i);
        Task best = pq.top();
        end = i < num ? min(tmp_task[i].s - 1, best.e) : best.e;
        time = best.s > time ? best.s : time;
        pq.pop();

        if (end - time + 1 >= best.x)
        {
            unit += (ll)best.x;
            time += best.x;
        }
        else
        {
            unit += (ll)(end - time + 1);
            best.x -= (end - time + 1);
            time += (end - time + 1);
            pq.push(best);
        }

        while (!pq.empty() and pq.top().e < time)
        {
            pq.pop();
        }
        //fprintf(stderr, "%d OK\n", i);
    }
    return unit;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int s, e, x, p;
        scanf("%d %d %d %d", &(s), &(e), &(x), &(p));
        task.push_back(Task(s, e, x, p));
    }
    sort(task.begin(), task.end(), cmp_p);

    if (task[0].p == task[n - 1].p)
    {
        //fprintf(stderr, "OK\n");
        printf("%lld\n", solve(n - 1));
    }
    else
    {
        ll res = (ll)task[0].x * (ll)task[0].p, prev = task[0].x;
        int id = 1;
        while (id < n)
        {
            ll u = solve(id);
            res += (ll)(u - prev) * (ll)task[id].p;
            prev = u;
            id++;
        }
        printf("%lld\n", res);
    }

    return 0;
}
