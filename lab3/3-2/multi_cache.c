#include <stdio.h>
#include <stdlib.h>
#include "multi_cache.h"

multi_cache_t *init_multi_cache_from_file(char *config_path)
{
  // TODO: Implement this function.
  FILE *config_fp;
  int b, n;

  config_fp = fopen(config_path, "rt");

  if (config_fp == NULL)
  {
    printf("Failed to open configuration file %s\n", config_path);
    return NULL;
  }

  if (fscanf(config_fp, "%d %d", &b, &n) != 2)
  {
    printf("Invalid configuration format\n");
    fclose(config_fp);
    return NULL;
  }

  multi_cache_t *cache;
  cache = malloc(sizeof(multi_cache_t));

  cache->n = n;
  cache->caches = malloc(sizeof(single_cache_t *) * n);

  for (int i = 0; i < n; i++)
  {
    int E, s;
    if (fscanf(config_fp, "%d %d", &E, &s) != 2)
    {
      printf("Invalid configuration format\n");
      fclose(config_fp);
      return NULL;
    }
    cache->caches[i] = init_single_cache_with_param(b, E, s);
  }

  fclose(config_fp);
  return cache;
}

int access_with_multi_cache(multi_cache_t *cache, addr_t addr)
{
  // TODO: Implement this function.

  for (int i = 0; i < cache->n; i++)
  {
    if (access_with_single_cache(cache->caches[i], addr) == 0)
    {
      return i + 1;
    }
  }

  return -1;
}
