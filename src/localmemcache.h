#ifndef _LOCAL_MEMCACHE_INCLUDED_
#define _LOCAL_MEMCACHE_INCLUDED_

#include <stdlib.h>
#include "lmc_hashtable.h"
#include "lmc_shm.h"
#include "lmc_lock.h"
#include "lmc_error.h"

#define LOCAL_MEMCACHE_FAILED 0
#define LOCAL_MEMCACHE_SUCCESS 1

typedef struct {
  char *namespace;
  size_t size;
  lmc_shm_t *shm;
  size_t va_hash;
  lmc_lock_t *lock;
  lmc_lock_t *root_lock;
  void* base;
  lmc_error_t error;
} local_memcache_t;

local_memcache_t *local_memcache_create(const char *namespace, size_t size,
    lmc_error_t *e);
char *local_memcache_get(local_memcache_t *lmc, const char *key);
int local_memcache_set(local_memcache_t *lmc, const char *key, const char* value);
int local_memcache_delete(local_memcache_t *lmc, char *key);
int local_memcache_free(local_memcache_t *lmc);
int local_memcache_iterate(local_memcache_t *lmc, void *ctx, ITERATOR_P(iter));
int local_memcache_clear_namespace(const char *namespace, int repair, 
    lmc_error_t *e);

#endif
