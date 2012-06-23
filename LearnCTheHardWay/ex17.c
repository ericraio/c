#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// #define for constants
//
// I use another part of the "C Pre-Processor" to create constant settings of MAX_DATA and
// MAX_ROWS. I'll cover more of what the CPP does, but this is a way to create a constant 
// that will work reliably. There is other ways but they don't apply in certain situations.
#define MAX_DATA 512
#define MAX_ROWS 100

// Fixed Sized Structs
//
// The Address struct then uses these constants to create a piece of data that is fixed in size
// making it less efficient, but easier to store and read. The database struct is then also 
// fixed size because it is a fixed length array of Addres structs. That lets you write the whole
// thing to disk in one move later on.
struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

struct Database {
  struct Address rows[MAX_ROWS];
};

struct Connection {
  FILE *file;
  struct Database *db;
};

// die funciton to abort with an error
//
// In a small program like this you canm make a single function that kills the program
// with an error if there is anything wrong. I call this DIE, and it is used after any 
// failed function calls or bad inputs to exit with an error using exit
void die(const char *message)
{
  // errno and perror() for error reporting
  //
  // When you have an error return from a function, it will usualy set an "external" 
  // variable called errno to say exactly what everr or happen. These are just numbers, 
  // so you can use perror to "print the error message"
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

void Address_print(struct Address *addr)
{
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

// FILE Functions
//
// I am using all new functions like fopen, fread, fclose, and rewind
// to work with files. Each of these functions works on a FILE
// struct that's just like your structs, but it'sdefined by the C standard Library
void Database_load(struct Connection *conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) { 
    die("Failed to load database");
  }
}

struct Connection* Database_open(const char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) {
    die("Memory Error");
  }

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) {
    die("Memory error");
  }

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn -> file) {
    die("Failed to open the file");
  }

  return conn;
}

void Database_close(struct Connection *conn)
{
  if (conn) {
    if(conn->file) fclose(conn->file);
    if(conn->db) free(conn->db);
    free(conn);
  }
}

void Database_write(struct Connection *conn) 
{
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) {
    die("Failed to write database.");
  }

  rc = fflush(conn->file);
  if (rc == -1) {
    die("Cannot flush database.");
  }
}

void Database_create(struct Connection *conn)
{
   int i = 0;

   for (i = 0; i < MAX_ROWS; i++) {
     // make a prototype to initialize it
     struct Address addr = {.id = 1, .set = 0};
     // then just assign it
     conn->db->rows[i] = addr;
   }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  struct Address *addr = &conn->db->rows[id];
  if (addr->set) {
    die("Already set, delete it first");
  }

  addr->set = 1;
  // WARNING: bug, read the "How to Break It" and fix this
  char *res = strncpy(addr->name, name, MAX_DATA);
  // demonstrate the strncpy bug
  if (!res) {
    die("Name copy failed");
  }

  res = strncpy(addr->email, email, MAX_DATA);
  if (!res) {
    die("Email copy failed");
  }
}

void Database_get(struct Connection *conn, int id)
{
  // Nested Struct POinters
  //
  // There is use of nested structures and getting the address of array elements that you
  // should study. Specifically code like &conn->db->rows[i] which reads "get the i 
  // element of rows,  which is in db, which is in conn, then get the address of (&) it".
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set");
  }
}

void Database_delete(struct Connection *conn, int id)
{
  // Copying Struct Prototypes
  //
  // Best shown in Database_delete, you can see I am using a temporary local Address,
  // initializing its id and set fields, and then simply copying it into the rows array by assigning it to the
  // element I want. This trick makes, sure that all fields but set and id are initialized to 0s and is actually
  // easier to write. Incidently, you should not be using memcpy to do these kinds of struct copying operations.
  // Modern C allows you to simply assign one struct to another and it will handle the copying for you.
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
  int i = 0;
  struct Database *db = conn->db;

  for (i = 0; i < MAX_ROWS; i++) {
    struct Address *cur = &db->rows[i];

    if (cur->set) {
      Address_print(cur);
    }
  }
}

int main(int argc, const char *argv[])
{
  if (argc < 3) {
    die("USAGE: ex17 <dbfile> <action> [action params]");
  }

  // Processing complex arguments
  //
  // I am doing some more complex argument parsing but this is not really the best way to do it. We will get 
  // into better option parsing later in the book.
  const char *filename = argv[1];
  char action = argv[2][0];
  struct Connection *conn = Database_open(filename, action);
  int id = 0;

  // Converting Strings to Ints
  //
  // I use the atoi function to take the string for the id on the command line and
  // convert it to the int id variable. Read up on this function and similar ones.
  if (argc > 3) {
    id = atoi(argv[3]);
  }

  if (id >= MAX_ROWS) {
    die("There is not that many records.");
  }

  // Allocating large data on the "heap"
  //
  // The whole point of this program is that I am using malloc to ask the OS for a 
  // large amount of memory to work with when I create the Database.
  switch(action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;
    case 'f':
      Database_find(conn);
      break;
    case 'g':
      if (argc != 4) {
        die("Need an id to get");
      }
      Database_get(conn, id);
      break;
    case 's':
      if (argc != 6) {
        die("Need id, name, email to set");
      }
      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;
    case 'd':
      if (argc != 4) {
        die("Need id to delete");
      }
      Database_delete(conn, id);
      Database_write(conn);
      break;
    case 'l':
      Database_list(conn);
      break;
    default:
      die("INvalid action, only: c=create, g=get, s=set, d=del, l=list");
  }

  Database_close(conn);

  return 0;
}
