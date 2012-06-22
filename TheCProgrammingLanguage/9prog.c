#include <stdio.h>

int main(int argc, const char *argv[])
{
  int count = 10, x;
  int *int_pointer;
  printf("%d\n", sizeof(int *));
  printf("%d\n", sizeof(int_pointer));

  printf("%i\n", count);

  int_pointer = &count;

  x = *int_pointer;

  printf("%i\n", x);

  char *arr[] = {
    "hello", "world"
  };

  printf("%s\n", arr[0]);

  return 0;
}
