#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// #define DEBUG

#define maxn 256 + 6
#define max(a,b) ((a) > (b) ? (a) : (b))

void reverse_str(char *str, int len);
bool zero(int *a, int max_len);
void divided_by_two(int *a, int max_len);
bool compare(int a[maxn], int b[maxn], int max_len);
void substract(int *a, int *b, int max_len);
void multiply_by_2(int *a, int max_len);
void multiply_by_2power(int *a, int power, int max_len);
void print(int *a, int max_len);

int main() {

    char A[maxn], B[maxn];
    scanf("%s %s", A, B);

    int A_len = strlen(A), B_len = strlen(B);
    reverse_str(A, A_len);
    reverse_str(B, B_len);

    int max_len = max(A_len, B_len);

    int a[max_len], b[max_len];
    for (int i = 0; i < max_len; i++)
    {
        if (i >= A_len)
        {
            a[i] = 0;
        }
        else
        {
            a[i] = A[i] - '0';
        }
    }

    for (int i = 0; i < max_len; i++)
    {
        if (i >= B_len)
        {
            b[i] = 0;
        }
        else
        {
            b[i] = B[i] - '0';
        }
    }

#ifdef   DEBUG
    print(a, max_len);
    printf("\n");
    print(b, max_len);
#endif  // DEBUG

    // GCD
    int *n = a, *m = b;
    if (compare(n, m, max_len))
    {
        int *tmp = n;
        n = m;
        m = tmp;
    }

    int power = 0;
    while (!zero(n, max_len) && !zero(m, max_len))
    {
        if (n[0] % 2 == 0 && m[0] % 2 == 0)
        {
            power++;
            divided_by_two(n, max_len);
            divided_by_two(m, max_len);
        }
        else if (n[0] % 2 == 0)
        {
            divided_by_two(n, max_len);
        }
        else if (m[0] % 2 == 0)
        {
            divided_by_two(m, max_len);
        }
#ifdef   DEBUG
        print(n, max_len);
        print(m, max_len);
#endif  // DEBUG
        if (compare(n, m, max_len))
        {
            int *tmp = n;
            n = m;
            m = tmp;
        }

        substract(m, n, max_len);
#ifdef  DEBUG
        print(n, max_len);
        print(m, max_len);
        printf("\n");
#endif  //DEBUG
    }

    multiply_by_2power(n, power, max_len);

    print(n, max_len);

    return 0;
}

void reverse_str(char *str, int len)
{
    for (int i = 0; i < len / 2; i++)
    {
        char c = str[i];
        str[i] = str[len - i - 1];
        str[len - i  -1] = c;
    }
}

bool zero(int *a, int max_len)
{
    for (int i = max_len - 1; i >= 0; i--)
    {
        if (a[i] != 0)
        {
            return false;
        }
    }

    return true;
}

void divided_by_two(int *a, int max_len)
{
    int borrow = 0;

    for (int i = max_len - 1; i >= 0; i--)
    {
        int num = borrow * 10 + a[i];
        if (num == 1)
        {
            a[i] = 0;
            borrow = 1;
        }
        else
        {
            a[i] = num / 2;
            borrow = num % 2;
        }
    }
}

bool compare(int a[maxn], int b[maxn], int max_len)
{
    // if a > b return true
    bool flag = 1;
    for (int i = max_len - 1; i >= 0; i--)
    {
        if (b[i] > a[i])
        {
            flag = 0;
            break;
        }
        else if (b[i] == a[i])
        {
            continue;
        }
        else
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

void substract(int *a, int *b, int max_len)
{
    int borrow = 0;
    for (int i = 0; i < max_len; i++)
    {
        a[i] = a[i] - b[i] - borrow;
        if (a[i] >= 0)
        {
            borrow = 0;
        }
        else
        {
            a[i] += 10;
            borrow = 1;
        }
    }
}

void multiply_by_2(int *a, int max_len)
{
    int carry = 0;
    for (int i = 0; i < max_len; i++)
    {
        a[i] = 2 * a[i] + carry;
        if (a[i] >= 10)
        {
            a[i] %= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
}

void multiply_by_2power(int *a, int power, int max_len)
{
    for (int i = 0; i < power; i++)
    {
        multiply_by_2(a, max_len);
    }
}

void print(int *a, int max_len)
{
    bool flag = 1;
    for (int i = max_len - 1; i >= 0; i--)
    {
        if (a[i] != 0 && flag)
        {
            flag = 0;
        }
        if (!flag)
        {
            printf("%d", a[i]);
        }
    }
    printf("\n");
}