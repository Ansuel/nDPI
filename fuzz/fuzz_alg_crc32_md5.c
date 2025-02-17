#include "ndpi_api.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  u_char hash[16];
  struct ndpi_popcount popcount;
  char *str;

  /* No memory allocations involved */

  /* Used for crc32, md5, hash(es) and popcount algs */

  ndpi_crc32(data, size);
  ndpi_md5(data, size, hash);

  ndpi_murmur_hash((const char *)data, size);
  ndpi_quick_hash(data, size);

  str = ndpi_malloc(size + 1);
  if(str) {
    memcpy(str, data, size);
    str[size] = '\0';

    ndpi_quick_hash64((const char *)str, strlen(str));
    ndpi_hash_string(str);
    ndpi_rev_hash_string(str);
    ndpi_hash_string_len(str, strlen(str));

    ndpi_free(str);
  }
  

  ndpi_popcount_init(&popcount);
  ndpi_popcount_count(&popcount, data, size);

  return 0;
}
