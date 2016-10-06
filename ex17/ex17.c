#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

/* Define a strucutre named Address that is composed of
 * an identifier (id), a flag that indicates if the struct
 * has data (set) and two character arrays which take a 
 * maximum of 512 bytes (name & email).*/
struct Address {
  int id;
  int set;
  char name[MAX_DATA];
  char email[MAX_DATA];
};

/* Define a structure named Database that has a single element
 * (rows) which is an array of Address structures. */
struct Database {
  struct Address rows[MAX_ROWS];
};

/* Define a structure named Connection that is composed of two elements. 
 * The first is a pointer to a FILE (file) and the second is a
 * pointer to a Database structure (db). */
struct Connection {
  FILE *file;
  struct Database *db;
};


/* Declare a function called `die` which prints out an error message. */
void die(const char *message)
{
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

void Database_load(struct Connection *conn) 
{
  /* Read from the file stream at `conn->file` and store them in
   * `conn->db`. 
   *
   * The number of bytes to read is determined by the
   * size of the Database struct. 
   *
   * We're also reading 1 Database struct's worth of bytes.
   *
   * If the read is successfull, `fread` will return 1. If the 
   * return value is less than 1, it means `fread` failed to read
   * the total amount of data we asked it to. */
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1)
    die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) {
    die("Memory error");
  }

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) {
    die("Memory error");
  }

  if (mode == 'c') {
    /* The mode `w` means open the file for writing. If the file
     * exists it is truncated to 0 length. Otherwise, the file is
     * created. */
    conn->file = fopen(filename, "w");
  } else {
    /* The mode `r+` means open the file for reading and writing. */
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file) {
    die("Failed to open the file");
  }

  return conn;
}

void Database_close(struct Connection *conn)
{
  if (conn) {
    /* We need to close all files and free everything that was malloc'd */
    if (conn->file) {
      fclose(conn->file);
    }

    if (conn->db) {
      free(conn->db);
    }

    free(conn);
  }
}

void Database_write(struct Connection *conn)
{
  /* The function `rewind` sets the file position indicator to 
   * the beginning of the file.
   * 
   * Why would we want to do this? 
   *
   * If the file position indicator was at midway through the file,
   * when we write from the file to our database we'd only be writing
   * half the file. Instead what we want to to write the whole file
   * to the database. To ensure we do that we need to set the file
   * position indicator to the beginning of the file using `rewind`. */
  rewind(conn->file);

  /* We've seen `fwrite` already. This code is reading an amount of
   * bytes equal to the size of 1 Database structure from the file stream
   * and writing them to the memory we malloc'd for the database. */
  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1)
    die("Failed to write database");

  /* If there are any bytes stuck in a buffer not yet written to the file, 
   * calling `fflush` will write them so we don't lose them. */ 
  rc = fflush(conn->file);
  if (rc == -1)
    die("Cannot flush database");
}


void Database_create(struct Connection *conn)
{
  int i = 0;

  for (i = 0; i < MAX_ROWS; i++) {
    // make a prototype to initialize it
    struct Address addr = {.id = i, .set = 0};
    // then just assign it
    conn->db->rows[i] = addr;
  }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  /* This one is a little weird. 
   *
   * What we're doing grabbing the memory address of 
   * the Address structure with id=`id`. */
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) 
    die("Already set, delete it first");
  
  addr->set = 1;

  // WARNING: bug, read the "How To Break It" and fix this
  char *res = strncpy(addr->name, name, MAX_DATA);

  // demonstrate the strncpy bug
  if (!res)
    die("Name copy failed");


  strncpy(addr->email, email, MAX_DATA);
  if (!res)
    die("Emailcopy failed");
}


void Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set");
  }
}

void Database_delete(struct Connection *conn, int id)
{
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

void Database_find(struct Connection *conn, char *query)
{
  int i = 0;

  for (i = 0; i < MAX_ROWS; i++) {
    struct Address *cur = &conn->db->rows[i];

    if (cur->set) {
      char *email = cur->email;
      if (strcmp(email, query) == 0) {
        Address_print(cur);
      }
    }
  }
}

int main(int argc, char *argv[])
{
  printf("The size of Address is %ld\n",    sizeof(struct Address));
  /* printf("The size of Database is %ld\n",   sizeof(struct Database)); */
  /* printf("The size of Connection is %ld\n", sizeof(struct Connection)); */

  if (argc < 3) die("USEAGE: ex17 <dbfile> <action> [action params]");
  

  char *filename = argv[1];
  char action    = argv[2][0];

  struct Connection *conn = Database_open(filename, action);

  int id = 0;
  if (argc > 3)       id = atoi(argv[3]); 
  if (id >= MAX_ROWS) die("There's not that many records.");


  switch (action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 'g':
      if (argc != 4) die("Need an id to get");

      Database_get(conn, id);
      break;

    case 's':
      if (argc != 6) die("Ned id, name, email to set");

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'd':
      if (argc != 4) die("Need an id to get");

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;

    case 'f':
      if (argc != 4) die("Need an email to search");

      Database_find(conn, argv[3]);
      break;

    default:
      die("Invalid action: c=create, g=get, s=set, d=delete, l=list");
  }


  Database_close(conn);


  return 0;
}
