#include <stdio.h>

void recurse(int count)
{
  printf("%d\n", count);
  
  if (count == 4000) return
  recurse( count + 1 );
}

int main(int argc, const char *argv[])
{
  recurse(1);
  return 0;
}
