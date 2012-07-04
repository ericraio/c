#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, const char *argv[])
{

  double r1 = (float) rand() / (float) RAND_MAX;
  double r2 = (float) rand() / (float) RAND_MAX;
  int x = 1, y = 2;
  printf("---\n\n");
  printf("%i\n", x);
  printf("%i\n", y);

  printf("---\n\n");
  printf("%f\n", (float) RAND_MAX);
  printf("---\n\n");
  printf("%f\n", r1);
  printf("%f\n", r2);

  return 0;
}
