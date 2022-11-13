#include <stdio.h>
#include <stdbool.h>

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};

    int n = 5;
    int sum = 0, weight_sum = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        sum += arr[i];
        weight_sum += (arr[i] * i);
    }

    int num = 0, left = 0, right = weight_sum, prev_sum = 0;
    for (int i = 0; i < n; i++)
    {
        num = arr[i];
        sum -= num;
        printf("index %d, left: %d, right: %d, sum: %d\n", i, left, right, sum);
        right -= sum;
        prev_sum += num;
        left += prev_sum;
        
    }

    return 0;
}
