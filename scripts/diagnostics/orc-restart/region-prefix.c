// Diagnostic single-threaded execution-region allocator, not a production ABI.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
typedef struct RegionNode { void *pointer; struct RegionNode *next; } RegionNode;
static RegionNode *region_nodes;
static long long region_count;
static unsigned long long region_epoch = 1;
static void *region_malloc(size_t size) {
  void *pointer = malloc(size ? size : 1);
  RegionNode *node = malloc(sizeof(*node));
  if (!pointer || !node) abort();
  *node = (RegionNode){pointer, region_nodes}; region_nodes = node; ++region_count;
  return pointer;
}
static void region_free(void *pointer) {
  if (!pointer) return;
  RegionNode **link = &region_nodes;
  while (*link && (*link)->pointer != pointer) link = &(*link)->next;
  if (!*link) { fputs("foreign or duplicate region free\n", stderr); abort(); }
  RegionNode *node = *link; *link = node->next;
  free(pointer); free(node); --region_count;
}
static void *region_calloc(size_t count, size_t size) {
  if (size && count > SIZE_MAX / size) abort();
  void *pointer = region_malloc(count * size); memset(pointer, 0, count * size); return pointer;
}
static void *region_realloc(void *pointer, size_t size) {
  if (!pointer) return region_malloc(size);
  if (!size) { region_free(pointer); return NULL; }
  RegionNode *node = region_nodes;
  while (node && node->pointer != pointer) node = node->next;
  if (!node) abort();
  void *replacement = realloc(pointer, size); if (!replacement) abort();
  node->pointer = replacement; return replacement;
}
long long probe_allocations(void) { return region_count; }
long long probe_destroy_region(void) {
  long long count = region_count;
  while (region_nodes) region_free(region_nodes->pointer);
  ++region_epoch;
  return count;
}
#define malloc region_malloc
#define calloc region_calloc
#define realloc region_realloc
#define free region_free
// The host controls dispatch; generated main must not drain before returning.
#define plew_loop_run probe_drain
