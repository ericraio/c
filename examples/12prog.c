#include <stdio.h>

char strA[80] = "A string to be used for demonstration purposes";
char strB[80];

int main(int argc, const char *argv[])
{
  char *pA; // A pointer to type character
  char *pB; // Another pointer to type character

  puts(strA);     // Show string A
  pA = strA;      // Point pA at string A
  puts(pA);       // show what pA at string A
  pB = strB;      // point pB at string B
  putchar('\n');  // move down one line on the screen
  while(*pA != '\0')
  {
    *pB++ = *pA++;
  }
  *pB = '\0';
  puts(strB);
  return 0;
}

