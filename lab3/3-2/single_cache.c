#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "single_cache.h"

single_cache_t* init_single_cache_from_file(char *config_path) {
  int b, E, s, ret;
  FILE *config_fp;

  config_fp = fopen(config_path, "rt");
  if (config_fp == NULL) {
    printf("Failed to open configuration file %s\n", config_path);
    return NULL;
  }

  ret = fscanf(config_fp, "%d %d %d", &b, &E, &s);
  if (ret != 3) {
    printf("Invalid configuration format\n");
    return NULL;
  }
  fclose(config_fp);

  if (b <= 0 || E <= 0 || s <= 0 || b > 16 || s > 16) {
    printf("Invalid configuration parameter: b=%d, E=%d, s=%d\n", b, E, s);
    return NULL;
  }

  return init_single_cache_with_param(b, E, s);
}

single_cache_t* init_single_cache_with_param(int b, int E, int s) {
  single_cache_t *cache = malloc(sizeof(single_cache_t));
  // TODO: Implement this function (you can simply copy your file from 3-1).
  return cache;
}

int access_with_single_cache(single_cache_t* cache, addr_t addr) {
  // TODO: Implement this function (you can simply copy your file from 3-1).
  return -1;
}
