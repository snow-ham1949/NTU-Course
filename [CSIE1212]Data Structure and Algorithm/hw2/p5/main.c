#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "price.h"

#define maxn 1024 * 1024
#define maxk 1000000 + 10
#define ull unsigned long long

typedef struct _Data {
    ull price;
    int stock;
} Data;

typedef struct _Heap {
    Data* arr;
    int sz, capacity;
} Heap;

int Parent(int i)
{
    return (i - 1) / 2;
}

int Left(int i)
{
    return 2 * i + 1;
}

int Right(int i)
{
    return 2 * i + 2;
}

Heap* newHeap()
{
    Heap* heap = calloc(1, sizeof(Heap));
    heap->arr = calloc(maxn, sizeof(Data));
    heap->sz = 0;
    return heap;
}

void HeapifyUp(Heap *heap, int id)
{
    if (id && heap->arr[Parent(id)].price > heap->arr[id].price)
    {
        Data tmp = heap->arr[Parent(id)];
        heap->arr[Parent(id)] = heap->arr[id];
        heap->arr[id] = tmp;
        HeapifyUp(heap, Parent(id));
    }
}

void HeapifyDown(Heap *heap, int p)
{
    int l = Left(p), r = Right(p);
    int minn = p;
    if (l < heap->sz && heap->arr[l].price < heap->arr[minn].price)
    {
        minn = l;
    }
    if (r < heap->sz && heap->arr[r].price < heap->arr[minn].price)
    {
        minn = r;
    }

    if (minn != p)
    {
        Data tmp = heap->arr[minn];
        heap->arr[minn] = heap->arr[p];
        heap->arr[p] = tmp;
        HeapifyDown(heap, minn);
    }
}

Data Top(Heap *heap)
{
    return heap->arr[0];
}

void Pop(Heap *heap)
{
    heap->arr[0] = heap->arr[heap->sz - 1];
    heap->sz--;
    HeapifyDown(heap, 0);
}

void Push(Heap *heap, Data key)
{
    heap->arr[heap->sz] = key;
    HeapifyUp(heap, heap->sz);
    heap->sz++;
}

void Merge(ull arr[], int l, int mid, int r)
{
    int n1 = mid - l, n2 = r - mid;
    ull L[n1], R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[i + l];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[i + mid];
    }
    int ptr_l = 0, ptr_r = 0, ptr = l;
    while (ptr_l < n1 && ptr_r < n2)
    {
        if (L[ptr_l] < R[ptr_r])
        {
            arr[ptr] = L[ptr_l];
            ptr_l++;
        }
        else
        {
            arr[ptr] = R[ptr_r];
            ptr_r++;
        }
        ptr++;
    }
    while (ptr_l < n1)
    {
        arr[ptr] = L[ptr_l];
        ptr++, ptr_l++;
    }
    while (ptr_r < n2)
    {
        arr[ptr] = R[ptr_r];
        ptr++, ptr_r++;
    }
}

void MergeSort(ull arr[], int l, int r)
{
    if (r - l <= 1)
    {
        return;
    }
    int mid = l + ((r - l) >> 1);
    MergeSort(arr, l, mid);
    MergeSort(arr, mid, r);
    Merge(arr, l, mid, r);
}

int BinarySearch(ull arr[], int l, int r, ull target)
{
    while (l < r)
    {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] < target)
        {
            l = mid + 1;
        }
        else
        {
            r = mid;
        }
    }
    return l;
}

ull kth(ull arr1[], ull arr2[], int m, int n, int k)
{
    if (k > (m + n) || k < 1)
    {
        return -1;
    }
    if (m > n)
    {
        return kth(arr2, arr1, n, m, k);
    }
    if (m == 0)
    {
        return arr2[k - 1];
    }
    if (k == 1)
    {
        return (arr1[0] < arr2[0]) ? arr1[0] : arr2[0];
    }
    int m2 = (m < k / 2) ? m : k / 2, n2 = (n < k / 2) ? n : k / 2;
    if (arr1[m2 - 1] > arr2[n2 - 1])
    {
        return kth(arr1, arr2 + n2, m, n - n2, k - n2);
    }
    else
    {
        return kth(arr1 + m2, arr2, m - m2, n, k - m2);
    }
}

ull ans[maxk], extra[maxk];

int main()
{
    int A, Q, N;
    scanf("%d %d %d", &A, &Q, &N);

    ull stock[A];
    for (int i = 0; i < A; i++)
    {
        scanf("%llu", &(stock[i]));
    }

    Heap *min_stock = newHeap();

    for (int i = 0; i < A; i++)
    {
        for (ull t = 1; t <= (ull)N; t++)
        {
            Data data;
            data.price = price(stock[i], t);
            data.stock = i;
            Push(min_stock, data);
        }
    }

    ull day[A];
    for (int i = 0; i < A; i++)
    {
        day[i] = 1 + N;
    }
    for (int cnt = 0; cnt < 1000000; cnt++)
    {
        Data top = Top(min_stock);
        ans[cnt] = top.price;
        Pop(min_stock);
        top.price = price(stock[top.stock], day[top.stock]);
        Push(min_stock, top);
        day[top.stock]++;
    }

    ull s, k;
    for (int i = 0; i < Q; i++)
    {   
        scanf("%llu%llu", &s, &k);
        if (s == 0) // no extra stock
        {
            printf("%llu\n", ans[k - 1]);
        }
        else
        {
            int left = -1, right = -1, jmp = (N < 1024) ? 1024 : N;
            for (int t = 1; t <= k + 2 * N; t += jmp)
            {
                int pos = BinarySearch(ans, 0, k, price(s, (ull)t));
                if (t + pos + jmp <= k)
                {
                    left = t;
                }
                else
                {
                    break;
                }
            }

            left = (left - jmp > 0) ? left - jmp : 1;
            right = (left + 7 * jmp <= k + 2 * N) ? left + 7 * jmp : k + 2 * N;
            int cnt = 0;
            for (ull t = left; t <= (ull)right; t++)
            {
                extra[cnt++] = price(s, t);
            }

            MergeSort(extra, 0, cnt);

            ull minn = kth(ans, extra, 1000000, cnt, k - left + 1);
            printf("%llu\n", minn);
        }
    }

    return 0;
}