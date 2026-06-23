#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "single_cache.h"

static unsigned long long g_clock = 0;

single_cache_t *init_single_cache_from_file(char *config_path)
{
  int b, E, s, ret;
  FILE *config_fp;

  config_fp = fopen(config_path, "rt");
  if (config_fp == NULL)
  {
    printf("Failed to open configuration file %s\n", config_path);
    return NULL;
  }

  ret = fscanf(config_fp, "%d %d %d", &b, &E, &s);
  if (ret != 3)
  {
    printf("Invalid configuration format\n");
    return NULL;
  }
  fclose(config_fp);

  if (b <= 0 || E <= 0 || s <= 0 || b > 16 || s > 16)
  {
    printf("Invalid configuration parameter: b=%d, E=%d, s=%d\n", b, E, s);
    return NULL;
  }

  return init_single_cache_with_param(b, E, s);
}

single_cache_t *init_single_cache_with_param(int b, int E, int s)
{
  single_cache_t *cache = malloc(sizeof(single_cache_t));
  // TODO: Implement this function.

  cache->b = b;
  cache->B = 1 << b;
  cache->E = E;
  cache->s = s;
  cache->S = 1 << s;

  cache->sets = malloc(sizeof(cache_set_t) * cache->S);
  for (int i = 0; i < cache->S; i++)
  {
    cache->sets[i] = malloc(sizeof(cache_line_t) * E);
    for (int j = 0; j < E; j++)
    {
      cache->sets[i][j].valid_flag = 0;
      cache->sets[i][j].tag = 0;
      cache->sets[i][j].age = 0;
    }
  }

  return cache;
}

int access_with_single_cache(single_cache_t *cache, addr_t addr)
{
  // TODO: Implement this function.

  int E = cache->E;

  addr_t set_index = (addr >> cache->b) & ((1ULL << cache->s) - 1);
  addr_t tag = addr >> (cache->b + cache->s);
  cache_set_t set = cache->sets[set_index];

  g_clock++;

  for (int i = 0; i < E; i++)
  {
    if (set[i].valid_flag && set[i].tag == tag)
    {
      set[i].age = g_clock;
      return 0;
    }
  }

  int victim = 0;
  for (int i = 0; i < E; i++)
  {
    if (!set[i].valid_flag)
    {
      victim = i;
      break;
    }
    if (set[i].age < set[victim].age)
    {
      victim = i;
    }
  }

  set[victim].valid_flag = 1;
  set[victim].tag = tag;
  set[victim].age = g_clock;

  return -1;
}
