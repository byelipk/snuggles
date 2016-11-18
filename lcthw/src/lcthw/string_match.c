#include <stdio.h>
#include <lcthw/string_match.h>
#include <lcthw/hashmap.h>

// ALGORITHM  ShiftTable(P[0..m - 1])
//
// Desc:   Fills the shift table used by Horspool's and Boyer-Moore algorithms.
// Input:  Pattern P[0..m - 1] and an alphabet of possible characters.
// Output: Table[0..size - 2] indexed by the alphabet's characters and
//         filled with shift sizes computed by formula.
//
//
// def ShiftTable(P) do
//   for j <- 0 to m - 2 do
//     Table[P[j]] <- m - 1 - j  # initialize all elements of table with m
//   end
//   return Table
// end

char *ShiftTable(bstring pattern)
{
  int rc = btolower(pattern);
  check(rc == BSTR_OK, "Failed to downcase pattern.");

  int len = blength(pattern);
  check(len > 0, "Invalid pattern.");

  Hashmap *table = Hashmap_create(NULL, NULL);
  check(table != NULL, "Failed to create hash table.");

  for (int i = 0; i < len; i++) {
    // char key = bchar(pattern, i);
    // void *cur = Hashmap_get(table, &key);

    // printf("Hash key -> %c -> %p\n", key, cur);

    // bstring key   = bmidstr(pattern, i, 1);
    // bstring value = Hashmap_get(table, &key);
    //
    // if (value == NULL) {
    //   printf("Insert %s into hash\n", bdata(key));
    //   Hashmap_set(table, &key, &value);
    // } else {
    //   printf("Increment %s by 1\n", bdata(key));
    // }

    // bdestroy(key); // cleanup
    // bdestroy(value); // cleanup
  }

  Hashmap_destroy(table);

  return bdata(pattern);

error:
  return NULL;
}
