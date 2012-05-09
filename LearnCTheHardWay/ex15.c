#include <stdio.h>

int main(int argc, const char *argv[])
{
  // create two arrays, ages storing some int data, and names storing
  // an array of string
  int ages[] = {23, 43, 12, 89, 2};
  char *names[] = {
    "Alan", "Frank",
    "Mary", "John", "Lisa"
  };
  // safely get the size of ages
  // some variables for our for-loops
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // first way using indexing
  // You know this is just looping through the two arrays and printing
  // how old each person is. This is using i to index into the array
  for (i = 0; i < count; i++) {
    printf("%s has %d years alive.\n",
        names[i], ages[i]);
  }

  printf("---\n");

  // setup the pointers to the start of the arrays
  // Create a pointer that points at ages. Notice the use of int * to
  // create a "pointer to integer" type of pointer. That's similar to char *,
  // which is a "which is a pointer to char", and a string is an array of chars. Seeing the similarity yet?
  int *cur_age = ages;
  // Create a pointer tha tpoints at names. A char * is already a "pointer to char", so that's juse a string. You however need 2 levels, since names is
  // 2 dimensional, that means you need char ** for a "pointer to (a pointer to char)" type. Study that too explain it to your self.
  char **cur_name = names;

  // second way using pointers
  // Loop through the ages and names but instead use the pointers plus an offset of i. Writing * (cur_name+1) is the same as writing nam[i], and you read it as 
  // "the the value of (pointer cur_name plus i)
  for (i = 0; i < count; i++) {
    printf("%s is %d years old.\n",
        *(cur_name+i), *(cur_age+i));
  }

  printf("---\n");

  // third way, pointers are just arrays
  // This shows the "magic" of how C treats pointers and arrays as the same thing.
  // You just use the array syntax for accessing the array, but use
  // the pointer's name. C figures it all out for you.
  for (i = 0; i < count; i++) {
    printf("%s is %d years old.\n",
        cur_name[i], cur_age[i]);
  }

  printf("---\n");

  // fourth way with pointers in a stupid complex way
  // Another admittedly insane loop that does the same thing as the other two,
  // but instead uses various pointer arithmetic methods
  // 
  // for-loop by setting cur_name and cur_age to the beginning of the names and ages arrays
  for (cur_name = names, cur_age = ages;
      // the test poition of the for-loop then compares the distance of the pointer cur_age from the start of ages.
      // Why does that work?
      (cur_age - ages) < count;
      // The increment part of the for-loop then increments both cur)name and cur_age so that they point at the next element of the name and age arrays
      cur_name++, cur_age++) {

    // The pointers cur_name and cur_age are now pointing at one element of the arrays they work on, and we can print them out
    // using the *cur_name and * cur_age, whgich means "the value of whereever cur_name is pointing"
    printf("%s lived %d years so far.\n", 
          *cur_name, *cur_age);
  }
  return 0;
}
