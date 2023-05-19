#include <stdio.h>

void factorial(int);


int main()
{
    int n;
    printf("n: ");
    scanf("%d",&n);
    factorial(n);
    return 0;
}

void factorial(int n)
{
    int fact = 1;
    int i; 
    for(i=1;i<=n;i++)
    {
        fact = i * fact;
    }
    printf("Factorial of %d: %d\n",n,fact);
}