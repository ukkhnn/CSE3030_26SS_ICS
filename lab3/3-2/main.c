#include <stdio.h>
#include <stdlib.h>
#include "multi_cache.h"

int main(int argc, char* argv[]) {
  FILE *config_fp, *trace_fp;
  int ret, hit, b, E, s;
  addr_t addr;
  multi_cache_t *cache;

  if (argc != 3) {
    printf("Usage: %s <config file> <trace file>\n", argv[0]);
    exit(1);
  }

  cache = init_multi_cache_from_file(argv[1]);
  if (cache == NULL) {
    printf("Failed to initialize cache\n");
    exit(1);
  }

  trace_fp = fopen(argv[2], "rt");
  if (trace_fp == NULL) {
    printf("Failed to open memory trace file %s\n", argv[2]);
    exit(1);
  }

  // Read iteratively until an invalid line or EOF.
  while (fscanf(trace_fp, "%llx", &addr) == 1) {
    hit = access_with_multi_cache(cache, addr);
    if (hit == -1)
      puts("MISS");
    else
      printf("HIT at level %d\n", hit);
  }

  fclose(trace_fp);

  // For simplicity, let's omit the deallocation of memory blocks in 'cache'.

  return 0;
}
