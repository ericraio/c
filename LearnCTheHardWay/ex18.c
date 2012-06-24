#include <stdio.h>   // The usual includes needed for all the functons we call.
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex 17 */
void die(const char *message) // This is the die function from the previous exercise which 
{                             // I will use to do error checking.
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb) (int a, int b); // This is where the typedef is used, and later I use
                                          // compare_cb like it is a type similar to int or char
/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting
 */                                                        // A bubble sort implementation, which is a very inefficient way to sort some integers
int *bubble_sort(int *numbers, int count, compare_cb cmp)  // Here is where I use typedef for compare_cb as the last parameter cmp.
{                                                          // This is now a function that will return a comparison between 2 integers of sorting.
  int temp = 0;
  int i = 0;
  int j = 0;                                      // The usual creation of variables on the stack, followed by a new array of integers on the heap
  int *target = malloc(count * sizeof(int));      // using malloc. Make sure you understand what count * sizeof(int) is doing.

  if (!target) {
    die("Memmory error.");
  }

  memcpy(target, numbers, count * sizeof(int));

  for (i = 0; i < count; i++) {                       // <------------ The outer loop of the bubble sort
    for (j = 0; j < count - 1; j++) {                 // <------------ The inner loop of the bubble sort
      if (cmp(target[j], target[j+1]) > 0) {                                  //  Now I call the cmp callback just like it is a normal function, but instead of
        temp = target[j+1];                                                   //  being the name of something we defined, it is just a pointer to it. this lets
        target[j+1] = target[j];                                              //  the caller pass in anything they want as long as it matches the "signature" of the compare_cb typedef
        target[j] = temp;                             // The actual swapping the a bubble sort needs to do
      }
    }
  }

  return target;  // Finally return the newly created and sorted result array target.
}

int sorted_order(int a, int b)                           // Three different versions of compare_cb function type, which needs to have the same definition
{                                                        // as the typedef we created. The C compiler will complain to you if you get this wrong and say 
  return a - b;                                          // the types don't match
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strange_order(int a, int b)
{
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

/**
 * Used to test that we are sorting things 
 * correctly by doing the sort and priting it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp)  // This is a tester for the bubble_sort function. You can see now how I am also using compare_cb to
{                                                           // then pass to bubble_sort demonstrating how these can be passed around like any other pointers.
  int i = 0;
  int *sorted = bubble_sort(numbers, count, cmp);

  if (!sorted) {
    die("Failed to sort as request.");
  }

  for (i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);
}

int main(int argc, char *argv[])  // A simple main function that sets up an array based on integers you pass on the command line, then calls the test_sorting function.
{
  if (argc < 2) {
    die("USAGE: ex18 4 3 1 5 6");
  }

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;

  int *numbers = malloc(count * sizeof(int));

  if (!numbers) {
    die("Memory Error.");
  }

  for (i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }

  test_sorting(numbers, count, sorted_order);  // Finally, you get to see how the compare_cb function pointer typedef is used. I simply call test_sorting but give it the name
  test_sorting(numbers, count, reverse_order); // of sorted_order, reverse_order, and strange_order as the function to use. THe C impiler then finds the address of those functions and makes
  test_sorting(numbers, count, strange_order); // it a pointer for test_sorting to use. If you look at test_sorting you will see it then passes each of these to bubble_sort but it actually has
                                               // no idea what they do, only that they match the compare_cb prototype and shold work.
  free(numbers);  // Last thing we do is free up the array of numbers we made.

  return 0;
}
