// includes the standard io library
#include <stdio.h>

// start of a normal c program
int main(int argc, char *argv[])
{
  // sets up the areas variable with an integer array
  // arrays in C use curly braces
  int areas[] = {10, 12, 13, 14, 20};

  // sets up a character variable name with Zed
  char name[] = "Zed";
  // character array with Zed Shaws full name each character is an element of the array
  char full_name[] = {
    'Z', 'e', 'd',
    ' ', 'A', '.', ' ',
    'S', 'h', 'a', 'w', '\0'
  };

  // prints the size of an integer
  printf("The size of an int: %ld\n", sizeof(int));

  // prints the size of the array
  printf("The size of areas (int[]): %ld\n", 
      sizeof(areas));

  // prints the total element size of the array
  printf("The number of ints in areas; %ld\n",
      sizeof(areas) / sizeof(int));

  // prints the first element and the second element
  // arrays in C are 0 based
  printf("The first area is %d, then 2nd %d.\n",
      areas[0], areas[1]);

  // prints the size of a character
  printf("The size of a char: %ld\n", sizeof(char));
  // prints the size of the name for Zed
  printf("the size of name (char[]): %ld\n",
      sizeof(name));
  // prints the number of characters total for the name
  printf("The number of chars: %ld\n",
      sizeof(name) / sizeof(char));
  // prints the number of characters for the full name
  printf("The number of chars: %ld\n",
      sizeof(full_name) / sizeof(char));
  // prints both the name and the full name
  printf("name=\"%s\" and full_name=\"%s\"\n",
      name, full_name);

  // exits the program
  return 0;
}
