#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <glob.h>
#include "dbg.h"

const size_t MAX_LINE = 1024;

int found_it(int use_or, int found_count, int search_len)
{
  debug("use_or: %d, found_count: %d, search_len: %d", use_or, found_count, search_len);

  if (use_or && found_count > 0) {
    return 1;
  } else if (!use_or && found_count == search_len) {
    return 1;
  } else {
    return 0;
  }
}

int scan_file(const char *filename, int use_or, int search_len, char *search_for[])
{
  FILE *file   = fopen(filename, "r");
  char *buffer = NULL;
  char *found  = NULL;
  long int size = 0;
  int found_count = 0;

  check(file, "Failed to open file: %s", filename);

  // Find size of file
  struct stat st;
  stat(filename, &st);
  size = st.st_size;

  // Allocate memory for buffer
  buffer = calloc(size, 1);
  check_mem(buffer);

  // Read data from file into buffer
  fread(buffer, size, 1, file);

  for(int i = 0; i < search_len && found == NULL; i++) {
    if (strcasestr(buffer, search_for[i])) {
      /* debug("file: %s, line: %s, search: %s", filename, buffer, search_for[i]); */
      found_count++;
    }
  }

  if (found_it(use_or, found_count, search_len)) {
    printf("%s\n", filename);
  } else {
    found_count = 0;
  }

  free(buffer);
  fclose(file);
  return 0;
error:
  if (buffer) free(buffer);
  if (file)   fclose(file);
  return -1;
}

int list_files(glob_t *globber)
{
  char *buffer = NULL;
  FILE *file   = fopen(".logfind", "r");
  int G_FLAGS  = GLOB_TILDE;
  int rc       = -1;
  long int size = 0;

  check(globber != NULL, "Invalid glob_t given.");
  check(file, "Failed to open `.logfind`. Make that first.");

  // Read .logfind into memory
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  buffer = calloc(size, 1);

  check_mem(buffer);
  fread(buffer, size, 0, file);

  // NOTE:
  // There is a design flaw in glob() where we cannot append
  // to the struct right away. We're using this dummy test
  // file to begin the globbing process so that we can append
  // to the glob struct when we're dealing with the files we
  // actually care about.
  rc = glob("dummy", G_FLAGS, NULL, globber);
  check(rc == 0, "Failed to glob dummy test file `test.txt`");

  while (fgets(buffer, MAX_LINE, file) != NULL) {
    buffer[strlen(buffer) - 1] = '\0';    // A little trick to remove trailing `\n`

    rc = glob(buffer, G_FLAGS | GLOB_APPEND, NULL, globber);

    check(rc == 0 || rc == GLOB_NOMATCH, "Failed to glob.");
  }

  for (int i = 0; i < globber->gl_pathc; i++) {
    debug("Matched file: %s", globber->gl_pathv[i]);
  }

  rc = 0; // All good

error:   // fallthrough
  if (buffer) free(buffer);
  if (file)   fclose(file);
  return rc;
}

int parse_args(int *use_or, int *argc, char **argv[])
{
  (*argc)--;
  (*argv)++;

  if (strcmp((*argv)[0], "-o") == 0) {
    *use_or = 1;
    (*argc)--; // skip the -o
    (*argv)++;
    check(*argc > 1, "You need words after -o.");
  } else {
    // NOTE
    // This is a bug. Why?
    // This is a pointer to an int. We're not changing the value
    // of the int by assigning 0 to `use_or`.
    use_or = 0;
  }

  return 0;
error:
  return -1;
}

int main(int argc, char *argv[])
{
  int use_or = 0;
  glob_t files_found;

  check(argc > 1, "USAGE: logfind word word word");

  check(parse_args(&use_or, &argc, &argv) == 0, "USAGE: logfind word word word");

  check(list_files(&files_found) == 0, "Failed to list files.");

  for (int i = 0; i < files_found.gl_pathc; i++) {
    scan_file(files_found.gl_pathv[i], use_or, argc, argv);
  }

  globfree(&files_found);

  return 0;
error:
  return -1;
}

