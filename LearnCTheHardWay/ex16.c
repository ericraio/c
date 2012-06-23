// include some new header files here to gain access to some new functions
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// This is where I am creating a structure that has 4 elements to describe a person. The final result is a new
// compound type that lets me reference these elements all as one, or each piece by name. It is similar
// to a row of a database table or a class in an OOP language.
struct Person {
  char *name;

  int age;
  int height;
  int weight;
};

// I need a way to create these structures so I have made a function to do that.
// Here is the important things this function is doing.
struct Person *Person_create(char *name, int age, int height, int weight)
{
  // I use malloc for memory allocate to ask the OS to give me a piece of raw memory.
  // I pass to malloc the sizeof(struct Person) which calculates the total size of the struct in bytes,
  // given all the fields inside it
  struct Person *who = malloc(sizeof(struct Person));
  // I use assert to make sure that I have a valid piece of memory back
  // from malloc. There is a special constant called NULL that you use to
  // mean "unset or invalid pointer". This assert is basically checking that
  // malloc didn't return a NULL invalid pointer.
  assert(who != NULL);

  // I initialize each field of struct Person using the x->y syntax, to
  // say what part of the struct I want to set.
  who->name = strdup(name);
  // I use strdup function to duplicate the string for the name, just 
  // to make sure that this structure actually owns it. THe strdup actually is like malloc and it also copies the original string 
  // into the memory it creates.
  who->age = age;
  who->height= height;
  who->weight = weight;

  return who;
}

// If I have a create then I always need a destroy function,
// and this is what destroys Person structs, I again use assert to
// make sure i am not getting bad input. Then I use the function free to return the memory I got with malloc and strdup. If you don't do this
// you get a "memory leak".
void Person_destroy(struct Person *who)
{
  assert(who != NULL);

  free(who->name);
  free(who);
}

// I then need a way to print out people, which is all this function does. it uses the same x->y syntax to get the field
// from the struct to print it.
void Person_print(struct Person *who)
{
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
}

// In the main function I use all the previous functions and the struct person to do the following
int main(int argc, const char *argv[])
{
  // make two people structures
  // create two people joe and frank
  struct Person *joe = Person_create(
    "Joe Alex", 32, 64, 140);

  struct Person *frank = Person_create(
      "Frank Blank", 20, 72, 180);

  // print them out and where they are in memory
  // print them out but notice im using the %p format so you can see 
  // where the program has actually put your struct in memory
  printf("Joe is at memory location %p:\n", joe);
  Person_print(joe);

  printf("Frank is at memory location %p:\n", frank);
  Person_print(frank);

  // Age both of them by 20 years with changes to their body too.
  // make everyone age 20 years and print them again
  joe->age += 20;
  joe->height -= 2;
  joe->weight += 40;
  // Print each after aging them
  Person_print(joe);

  frank->age += 20;
  frank->weight += 40;
  Person_print(frank);

  // destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(frank);


  return 0;
}
