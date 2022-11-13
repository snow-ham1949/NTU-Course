#include "mergesort.h"

void Merge_Str(Str arr[], int l, int mid, int r)
{
    int n1 = mid - l, n2 = r - mid;
    Str L[n1], R[n2];
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
        if ((L[ptr_l].pre < R[ptr_r].pre) || (L[ptr_l].pre == R[ptr_r].pre && (L[ptr_l].suf < R[ptr_r].suf)))
        {
            arr[ptr++] = L[ptr_l++];
        }
        else
        {
            arr[ptr++] = R[ptr_r++];
        }
    }

    while (ptr_l < n1)
    {
        arr[ptr++] = L[ptr_l++];
    }

    while (ptr_r < n2)
    {
        arr[ptr++] = R[ptr_r++];
    }
}

void Merge_int(int arr[], int l, int mid, int r)
{
    int n1 = mid - l, n2 = r - mid;
    int L[n1], R[n2];
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
            arr[ptr++] = L[ptr_l++];
        }
        else
        {
            arr[ptr++] = R[ptr_r++];
        }
    }

    while (ptr_l < n1)
    {
        arr[ptr++] = L[ptr_l++];
    }

    while (ptr_r < n2)
    {
        arr[ptr++] = R[ptr_r++];
    }
}

void MergeSort_Str(Str arr[], int l, int r)
{
    if (l == r || l + 1 == r)
    {
        return;
    }
    int mid = l + (r - l) / 2;
    MergeSort_Str(arr, l, mid);
    MergeSort_Str(arr, mid, r);
    Merge_Str(arr, l, mid, r);
}

void MergeSort_int(int arr[], int l, int r)
{
    if (l == r || l + 1 == r)
    {
        return;
    }
    int mid = l + (r - l) / 2;
    MergeSort_int(arr, l, mid);
    MergeSort_int(arr, mid, r);
    Merge_int(arr, l, mid, r);
}