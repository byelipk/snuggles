#include <lcthw/hashmap_algos.h>
#include <lcthw/bstrlib.h>

/*
 * A refresher on binary operators AND, OR, XOR:
 *
 * 0b00111100
 * 0b00001101
 *
 * AND = 0b00001100   (copy if bit exists in BOTH operands)
 * OR  = 0b00111101   (copy if bit exists in EITHER operand)
 * XOR = 0b00110001   (copy bit if exists in ONE operand but NOT the OTHER)
 **/

// settings taken from
// http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param
const uint32_t FNV_PRIME = 16777619;
const uint32_t FNV_OFFSET_BASIS = 2166136261;

uint32_t Hashmap_fnv1a_hash(void * data)
{
  bstring s = (bstring) data;
  uint32_t hash = FNV_OFFSET_BASIS;
  int i = 0;

  for (i = 0; i < blength(s); i++) {
    hash ^= bchare(s, i, 0);
    hash *= FNV_PRIME;
  }

  return hash;
}

const int MOD_ADLER = 65521;

uint32_t Hashmap_adler32_hash(void * data)
{
  bstring s = (bstring) data;
  uint32_t a = 1, b = 0;
  int i = 0;

  for (i = 0; i < blength(s); i++)
  {
    a = (a + bchare(s, i, 0)) % MOD_ADLER;
    b = (b + a) % MOD_ADLER;
  }

  return (b << 16) | a;
}

uint32_t Hashmap_djb_hash(void * data)
{
  bstring s = (bstring) data;
  uint32_t hash = 5381;
  int i = 0;

  for (i = 0; i < blength(s); i++) {
    hash = ((hash << 5) + hash) + bchare(s, i, 0);
  }

  return hash;
}

