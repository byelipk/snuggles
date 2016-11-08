#ifndef lcthw_Hashmap_h
#define lcthw_Hashmap_h

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 100

typedef int (*Hashmap_compare)(void *a, void *b);
typedef uint32_t (*Hashmap_hash)(void *key);

// A Hashmap can contain any number of HashmapNodes.
// The nodes are stored in buckets, a type of DArray
// that holds HashmapNode key/value pairs.
typedef struct Hashmap {
  DArray *buckets;         // two-level map of nodes
  Hashmap_compare compare; // comparison function
  Hashmap_hash hash;       // hashing function
} Hashmap;

typedef struct HashmapNode {
  void *key;     // key for the {key: value} pair
  void *data;    // data is a pointer to some value
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
