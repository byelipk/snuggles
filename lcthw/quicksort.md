### Quicksort

```
// ALGORITHM  Quicksort(A[l..r])
//
// Desc:  Sorts a subarray by quicksort where l is the 
//        low index and r is the high index.
// Input: A subarray A[l..r] of A[0..n - 1], defined by
//        its left and right indices, l and r.
// Output: Subarray A[l..r] sorted in nondecreasing order.

def Quicksort(A[l..r]) do
  if l < r
    s <- Partition(A[l..r]) // s is a split position
    Quicksort(A[l..s - 1])
    Quicksort(A[s + 1..r])
end


// ALGORITHM  Partition(A[l..r])
//
// Desc: Partitions a subarray by using its first element as a pivot,
//       where l is the element as index position 0 and r is the last 
//       element in the array.
// Input: A subarray A[l..r] of A[0..n - 1], defined by its left and right
//        indices l and r (l < r)
// Output: A partition of A[l..r], with the split position returned as this 
//         function's value.
//
// According to the pseudo code for Partition, three situations
// may arise after the scans stop:
//
// (1) If the scanning indices i and j have crossed (i < j)
//     then we decrement i and j and resume the scans.
//
// (2) If the scanning indices have crossed over (i > j), we
//     will have partitioned the array after exchanging the
//     pivot with A[j].
//
// (3) If the scanning indices stop while pointing to the same element (i = j),
//     the value they are pointing to must be equal to the pivot.

def Partition(A[l..r]) do
  p <- A[l]     // pivot (first element in A[l..r])
  i <- l        // index i (left to right scan)
  j <- r + 1    // index j (right to left scan)

  repeat
    repeat i <- i + 1 until A[i] >= p
    repeat j <- j - 1 until A[j] <= p
    swap(A[i], A[j])  
  until i >= j  

  swap(A[i], A[j])  // undo last swap when i >= j
  swap(A[l], A[j])  

  return j
end
```

State of Mind

  Quicksort(A[0..7])
  A = [5, 3, 1, 9, 8, 2, 4, 7]
  p = val 5
  i = idx 5
  j = idx 4
  S = idx 4

    State of Mind (S = idx 4)

      Quicksort(A[0..4 - 1])
      A = [5, 3, 1, 4]
      p = val 2
      i = idx 2
      j = idx 1
      S = idx 1

          State of Mind (S = idx 1)
            Quicksort(A[0..1 - 1])

            Quicksort(A[1 + 1..3])
            A = [3, 4]
            p = val 3
            i = idx 0
            j = idx 1
            S = idx 1


      Quicksort(A[4 + 1..7])
      A = [8, 9, 7]
      p = val 0
      i = idx 0
      j = idx 0
      S = ???
