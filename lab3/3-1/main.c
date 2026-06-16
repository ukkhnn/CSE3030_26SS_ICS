#include <stdio.h>
#include <stdlib.h>
#include "single_cache.h"

int main(int argc, char* argv[]) {
  FILE *config_fp, *trace_fp;
  int ret, b, E, s;
  addr_t addr;
  single_cache_t *cache;

  if (argc != 3) {
    printf("Usage: %s <config file> <trace file>\n", argv[0]);
    exit(1);
  }

  cache = init_single_cache_from_file(argv[1]);
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
    if (access_with_single_cache(cache, addr) == -1)
      puts("MISS");
    else
      puts("HIT");
  }

  fclose(trace_fp);

  // For simplicity, let's omit the deallocation of memory blocks in 'cache'.

  return 0;
}
