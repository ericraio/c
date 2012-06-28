#include <stdio.h>

int main(int argc, const char *argv[])
{
  int x = 2;
  int *y = &x;
  int *b = &*y;
  int *c = &*&*y;
  int *d = &*&*&*y;
  int *e = &*d;

  printf("%d\n", *y);
  printf("%d\n", *b);
  printf("%d\n", *c);
  printf("%d\n", *d);
  printf("%d\n", *e);
  return 0;
}
