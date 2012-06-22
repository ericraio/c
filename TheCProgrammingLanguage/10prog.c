#include <stdio.h>

// Set Up Array of 5 integers
int my_array[] = {1, 23, 17, 4, -5, 100};

// Set up Pointer
int *ptr;

int main(int argc, const char *argv[])
{
  // set up i integer var
  int i;
  // point oul pointer to the first element of the array
  ptr = &my_array[0];

  printf("\n\n");


  // Loop through each element of the array
  for (i = 0; i < 6; i++) {
    // this display each index and value of the array
    printf("my_array[%d] = %d    ", i, my_array[i]);  // <--- A

    // this moves the pointer to move over X memory allocations
    printf("ptr + %d = %d       ", i, *(ptr + i));         // <--- B

    // increment the value
    printf("ptr + %d = %d\n", i, *(ptr++));         // <--- C
  }

  return 0;
}
