#include <stdio.h>

extern int fact1(int n);
extern int fact2(int n);

int main() {
  int no, factorial;

  // get no
  printf("Enter a number to calculate it's factorial\n");
  scanf("%d", &no);

  // calculate factorial using Non-recursive
  factorial = fact1(no);
  printf("NR Factorial of the num(%d) = %d\n", no, factorial);

  // calculate factorial using Recursive
  factorial = fact2(no);
  printf("RC Factorial of the num(%d) = %d\n", no, factorial);

  return 0;
}