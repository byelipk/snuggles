#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "dbg.h"

#define MAX_LINE 1024

/* How are we going to scan a file? 
 *
 * Our method of scanning a file will leverage `fgets`
 * to read the file line-by-line. No more than MAX_LINE
 * bytes will be read at a time. 
 *
 * For each line in the file determine if the line contains
 * the search terms. */
int scan_file_by_line(const char *filename, int search_len, char *search_for[])
{
  char *line  = calloc(MAX_LINE, 1);
  FILE *file  = fopen(filename, "r");
  char *found = NULL;

  check_mem(line);
  check(file, "Failed to open file: %s", filename);

  /* The file scanning code goes here... */
  while(fgets(line, MAX_LINE, file) != NULL && found == NULL) {
    for(int i = 0; i < search_len && found == NULL; i++) {
      found = strcasestr(line, search_for[i]);
      if(found) {
        printf("%s\n", filename);
      }
    }
  }

  free(line);
  fclose(file);

  return 0;

error:
  if (line) free(line);
  if (file) fclose(file);

  return -1;
}

int scan_file_by_seek(const char *filename, int search_len, char *search_for[])
{
  // Boilerplate
  FILE *file   = fopen(filename, "r"); 
  char *buffer = NULL;
  char *found  = NULL;
  long int size = 0;

  check(file, "Failed to open file: %s", filename);

  // Determine file size
  fseek(file, 0, SEEK_END);  // seek to end of file
  size = ftell(file);        // get current file pointer
  fseek(file, 0, SEEK_SET);  // seek back to start of file

  // Allocate bytes into our buffer
  buffer = calloc(size, 1);
  check_mem(buffer);

  // Read data from file into buffer
  fread(buffer, size, 1, file);

  for(int i = 0; i < search_len && found == NULL; i++) {
    found = strcasestr(buffer, search_for[i]);
    if(found) {
      printf("%s\n", filename); 
    }
  }

  // Cleanup
  free(buffer);
  fclose(file);
  return 0;
error:
  if (buffer) free(buffer);
  if (file)   fclose(file);
  return -1;
}

int scan_file_by_stat(const char *filename, int search_len, char *search_for[])
{
  FILE *file   = fopen(filename, "r");
  char *buffer = NULL;
  char *found  = NULL;
  long int size = 0;

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
    found = strcasestr(buffer, search_for[i]);
    if (found) {
      printf("%s\n", filename);
    }
  }

  free(buffer);
  fclose(file);
  return 0;
error:
  if (buffer) free(buffer);
  if (file)   fclose(file);
  return -1;
}

int main(int argc, char *argv[])
{
  check(argc > 1, "USAGE: logfind word word word");

  /* scan_file_by_line("logfind.c", argc, argv); */
  /* scan_file_by_seek("logfind.c", argc, argv); */
  scan_file_by_stat("logfind.c", argc, argv);

  return 0;
error:
  return 1;
}
