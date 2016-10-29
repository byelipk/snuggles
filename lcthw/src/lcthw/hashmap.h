#ifndef lcthw_Hashmap_h
#define lcthw_Hashmap_h

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*Hashmap_compare)(void *a, void *b);
typedef uint32_t (*Hashmap_hash)(void *key);

typedef struct Hashmap {
  // A dynamic array that will be set to a fixed size of 100 buckets.
  // Each bucket will contain a DArray that will hold HashmapNodes.
  DArray *buckets;

  // This is a comparison function the hashmap uses to find elements
  // by their key. 
  Hashmap_compare compare;

  // This is the hashing function, and it is responsible for taking your key,
  // processing its contents, and producing a single uint32_t index number.
  Hashmap_hash hash;
} Hashmap;

typedef struct HashmapNode {
  void *key;     // key for the {key: value} pair
  void *data;    // The value
  uint32_t hash; // The hash makes finding the node quicker
} HashmapNode;

typedef int (*Hashmap_traverse_cb)(HashmapNode *node);

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash);
void Hashmap_destroy(Hashmap *map);

int Hashmap_set(Hashmap * map, void *key, void *data);
void *Hashmap_get(Hashmap * map, void *key);

int Hashmap_traverse(Hashmap * map, Hashmap_traverse_cb traverse_cb);

void *Hashmap_delete(Hashmap *map, void *key);

#endif
