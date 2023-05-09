#include <stdio.h>
typedef unsigned long long ull;

ull brute_force_F(int n)
{
    if (n == 0 || n == 1 || n == 2) {
        return n;
    }
    return brute_force_F(n - 3) + brute_force_F(n - 2);
}

ull iterative_F(int n)
{
    if (n == 0 || n == 1 || n == 2) {
        return n;
    }
    ull first = 0, second = 1, third = 2;
    ull temp;
    for (int i = 3; i <= n; i++) {
        temp = first + second;
        first = second;
        second = third;
        third = temp;
    }
    return third;
}

ull Padovan_sequence(int n)
{
    if (n == 0) return 1;
    if (n == 1 || n == 2) return 0;
    ull first = 1, second = 0, third = 0;
    ull temp;
    for (int i = 3; i <= n; i++) {
        temp = first + second;
        first = second;
        second = third;
        third = temp;
    }

    return third;
}

ull using_Padovan_F(int n)
{
    ull first = Padovan_sequence(n + 1);
    ull second = Padovan_sequence(n + 2);
    ull result = 2 * first + second;

    return result;
}

int main()
{
    for(int index = 0; index < 20; index++) {
        printf("Brute Force: %llu\n", brute_force_F(index));
        printf("Iterative: %llu\n", iterative_F(index));
        printf("Using Padovan Sequence: %llu\n", using_Padovan_F(index));
        puts("");
    }
}