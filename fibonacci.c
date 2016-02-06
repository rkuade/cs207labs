#include <stdio.h>

int main(int argc, char** argv)
{
    printf("fib(8) = %d",fib(8));
    return 0;
}

int fib(int n)
{
  if (n==1)
    return 0;
  if (n==2)
    return 1;
  else
    return (fib(n-1)+fib(n-2));
}