#include <lcthw/seq_string.h>
#include <lcthw/bstrlib.h>
#include <stdio.h>

// ALGORITHM  BruteForceStringMatch(T[0..n - 1], P[0..m - 1])
//
// Desc:   Implements brute-force string matching.
// Input:  An array T[0..n - 1] of n characters representing a text AND
//         and array P[0..m - 1] representing a search pattern.
// Output: The index of the first character in the text that starts a
//         matching substring or -1 if the search is unsuccessful.
//
// def BruteForceStringMatch(T, P) do
//    for i <- 0 to n - m do
//      j <- 0
//      while j < m and P[j] = T[i + j] do
//        j <- j + 1
//      end
//      if j = m return i
//    end
//    return -1
// end

int String_sequential_search(char *string, char *pattern)
{
  bstring T = bfromcstr(string);
  bstring P = bfromcstr(pattern);

  int T_len = blength(T);
  int P_len = blength(P);

  for (int i = 0; i < (T_len - P_len); i++) {
    int j = 0;
    while (j < P_len && bchar(P, j) == bchar(T, i + j)) {
      j += 1;
    }
    
    if (j == P_len) {
      // found it
      bdestroy(T);
      bdestroy(P);

      return i;
    }
  }

  // no dice
  bdestroy(T);
  bdestroy(P);

  return -1;
}
