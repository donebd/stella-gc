#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "runtime.h"
#include "gc.h"

// ============================ Memory Configuration Constants =============================

#define MAX_ALLOC_SIZE (24 * 128)
#define GEN_COUNT 2
// #define GC_DEBUG

// ========================= Global Statistics Variables ============================

int total_allocated_bytes = 0;
int total_allocated_objects = 0;
int max_allocated_bytes = 0;
int max_allocated_objects = 0;
int total_reads = 0;
int total_writes = 0;

int gc_roots_max_size = 0;
int gc_roots_top = 0;
void **gc_roots[4096];
int changed_nodes_top = 0;
void *changed_nodes[8192];

bool initialized = false;

struct Space g0_space_from, g1_space_from, g1_space_to;
struct Generation g0, g1;
struct Generation *generations[GEN_COUNT] = {&g0, &g1};

// ============================ Data Structures Definitions ================================

typedef enum
{
  GENERATION_0,
  GENERATION_1
} GenType;

struct gc_unit
{
  void *moved_to;
  stella_object stella_object;
};

struct Space
{
  GenType gen;
  int size;
  void *next;
  void *heap;
};

struct Generation
{
  GenType number;
  int collected;
  struct Space *from;
  struct Space *to;
  void *cursor;
};

// ========================= Function Declarations ============================

// memory
void init_space(struct Space *space, GenType gen, int size);
void init_generation(struct Generation *generation, GenType gen_type, struct Space *from_space, struct Space *to_space);
void init_memory();
void *safe_malloc(size_t size);
void handle_memory_error();
struct gc_unit *alloc_in_space(struct Space *space, size_t size_in_bytes);
void *try_alloc(struct Generation *g, size_t size_in_bytes);

// log & statistic
void dc_log(const char *text);
void update_allocation_stats(size_t size_in_bytes);
void print_space(const struct Space *space);

// common
void gc_collect();
bool in_heap(const void *ptr, const void *heap, size_t heap_size);
size_t get_stella_object_size(const stella_object *obj);

// gc_unit
size_t unit_size(const struct gc_unit *obj);
struct gc_unit *get_gc_unit(void *st_ptr);
stella_object *get_stella_object(struct gc_unit *gc_ptr);

// space
bool is_valid(const struct Space *space, const void *ptr);
bool has_space(const struct Space *space, size_t requested_size);

// generation
void forward_object_fields(struct Generation *gen, stella_object *obj);
void collect(struct Generation *g);
void forward_roots(struct Generation *g);
void forward_previous_generations(struct Generation *g);
void forward_changed_nodes(struct Generation *g);
void search_objects(struct Generation *g);
void finalize_collection(struct Generation *g);
bool chase(struct Generation *g, struct gc_unit *p);
void *forward(struct Generation *g, void *p);

// ============================ Function Implementations ================================

void *gc_alloc(const size_t size_in_bytes)
{
  init_memory();
  void *result = try_alloc(&g0, size_in_bytes);
  if (!result)
  {
    gc_collect();
    result = try_alloc(&g0, size_in_bytes);
  }
  if (result)
  {
    update_allocation_stats(size_in_bytes);
  }
  else
  {
    handle_memory_error();
  }
  return result;
}

void gc_read_barrier(void *object, int field_index)
{
  total_reads += 1;
}

void gc_write_barrier(void *object, int field_index, void *contents)
{
  total_writes += 1;

  changed_nodes[changed_nodes_top] = object;
  changed_nodes_top++;
}

void gc_push_root(void **ptr)
{
  gc_roots[gc_roots_top++] = ptr;
  if (gc_roots_top > gc_roots_max_size)
  {
    gc_roots_max_size = gc_roots_top;
  }
}

void gc_pop_root(void **ptr)
{
  gc_roots_top--;
}

void print_gc_alloc_stats()
{
  printf("--------------------------------------------------------------------\n");
  printf("                           STATS                                   \n");
  printf("--------------------------------------------------------------------\n");
  printf("| %-30s | %d bytes (%d objects)   |\n", "Total memory allocation:", total_allocated_bytes, total_allocated_objects);
  printf("| %-30s | %d (G_0: %d, G_1: %d)    |\n", "Total garbage collecting:", g0.collected + g1.collected, g0.collected, g1.collected);
  printf("| %-30s | %d bytes (%d objects)   |\n", "Maximum residency:", max_allocated_bytes, max_allocated_objects);
  printf("| %-30s | %d reads and %d writes   |\n", "Total memory use:", total_reads, total_writes);
  printf("| %-30s | %d roots                 |\n", "Max GC roots stack size:", gc_roots_max_size);
  printf("--------------------------------------------------------------------\n");
}

void print_state(const struct Generation *g)
{
  printf("--------------------------------------------------------------------\n");
  printf("G_%d state\n", g->number);
  printf("Collect count %d\n", g->collected);
  print_space(g->from);
  if (g->to->gen == g->from->gen)
  {
    printf("To space\n");
    print_space(g->to);
  }
  printf("--------------------------------------------------------------------\n");
}

void print_gc_state()
{
  print_state(&g0);
  print_state(&g1);
}

void print_gc_roots()
{
  printf("Roots:\n");
  printf("--------------------------------------------------------------------\n");
  for (int i = 0; i < gc_roots_top; i++)
  {
    printf("Address: %-15p | Value: %-15p\n", gc_roots[i], *gc_roots[i]);
  }
  printf("--------------------------------------------------------------------\n");
}

void handle_memory_error()
{
  printf("Out of memory error occurred!\n");
  exit(1);
}

void *safe_malloc(size_t size)
{
  void *ptr = malloc(size);
  if (!ptr)
  {
    handle_memory_error();
  }
  return ptr;
}

void init_space(struct Space *space, GenType gen, int size)
{
  space->gen = gen;
  space->size = size;
  space->heap = safe_malloc(size);
  space->next = space->heap;
}

void init_generation(struct Generation *generation, GenType gen_type, struct Space *from_space, struct Space *to_space)
{
  generation->number = gen_type;
  generation->collected = 0;
  generation->from = from_space;
  generation->to = to_space;
}

int read_g1_space_size()
{
  int size = 0;
  char *str = getenv("G1_SPACE_SIZE");
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] >= '0' && str[i] <= '9')
    {
      size = size * 10 + (str[i] - '0');
    }
    else
    {
      printf("Invalid input\n");
      exit(1);
    }
  }
  return size;
}

void init_memory()
{
  if (initialized)
  {
    return;
  }

  init_space(&g0_space_from, GENERATION_0, MAX_ALLOC_SIZE);
  int g1_space_size = read_g1_space_size();

  init_space(&g1_space_from, GENERATION_1, g1_space_size);
  init_space(&g1_space_to, GENERATION_1, g1_space_size);

  init_generation(&g0, GENERATION_0, &g0_space_from, &g1_space_from);
  init_generation(&g1, GENERATION_1, &g1_space_from, &g1_space_to);
  initialized = true;
}

void update_allocation_stats(const size_t size_in_bytes)
{
  total_allocated_bytes += size_in_bytes + sizeof(void *);
  total_allocated_objects += 1;
  max_allocated_bytes = total_allocated_bytes;
  max_allocated_objects = total_allocated_objects;
}

void gc_collect()
{
  collect(&g0);

  dc_log("Collected\n");
}

bool in_heap(const void *ptr, const void *heap, const size_t heap_size)
{
  return ptr >= heap && ptr < heap + heap_size;
}

size_t get_stella_object_size(const stella_object *obj)
{
  const int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(obj->object_header);
  return (1 + field_count) * sizeof(void *);
}

size_t unit_size(const struct gc_unit *obj)
{
  const int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(obj->stella_object.object_header);
  return (2 + field_count) * sizeof(void *);
}

struct gc_unit *get_gc_unit(void *st_ptr)
{
  return st_ptr - sizeof(void *);
}

stella_object *get_stella_object(struct gc_unit *gc_ptr)
{
  return &gc_ptr->stella_object;
}

bool is_valid(const struct Space *space, const void *ptr)
{
  return in_heap(ptr, space->heap, space->size);
}

bool has_space(const struct Space *space, const size_t requested_size)
{
  return space->next + requested_size <= space->heap + space->size;
}

struct gc_unit *alloc_in_space(struct Space *space, const size_t size_in_bytes)
{
  const size_t size = size_in_bytes + sizeof(void *);
  if (has_space(space, size))
  {
    struct gc_unit *result = space->next;
    result->moved_to = NULL;
    result->stella_object.object_header = 0;
    space->next += size;

    return result;
  }

  return NULL;
}

void print_space(const struct Space *space)
{
  printf("Objects:\n");

  for (void *start = space->heap; start < space->next; start += unit_size(start))
  {
    const struct gc_unit *gc_ptr = start;
    const int tag = STELLA_OBJECT_HEADER_TAG(gc_ptr->stella_object.object_header);
    const int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(gc_ptr->stella_object.object_header);

    printf("\tGC address: %-15p | moved: %-15p", gc_ptr, gc_ptr->moved_to);
    for (int i = 0; i < field_count; i++)
    {
      printf("%-15p", gc_ptr->stella_object.object_fields[i]);
      if (i < field_count - 1)
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void *try_alloc(struct Generation *g, size_t size_in_bytes)
{
  void *allocated = alloc_in_space(g->from, size_in_bytes);
  return allocated ? allocated + sizeof(void *) : NULL;
}

bool chase(struct Generation *g, struct gc_unit *p)
{
  struct gc_unit *q = alloc_in_space(g->to, get_stella_object_size(&p->stella_object));
  if (!q)
    return false;

  int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(p->stella_object.object_header);
  q->moved_to = NULL;
  q->stella_object.object_header = p->stella_object.object_header;

  for (int i = 0; i < field_count; i++)
  {
    q->stella_object.object_fields[i] = p->stella_object.object_fields[i];
  }
  p->moved_to = q;
  return true;
}

void *forward(struct Generation *g, void *p)
{
  if (!is_valid(g->from, p))
    return p;

  struct gc_unit *gc_object = get_gc_unit(p);
  if (is_valid(g->to, gc_object->moved_to))
    return get_stella_object(gc_object->moved_to);

  if (!chase(g, gc_object) && g->to->gen != g->from->gen)
  {
    collect(generations[g->to->gen]);
    if (!chase(g, gc_object))
      handle_memory_error();
  }
  return get_stella_object(gc_object->moved_to);
}

void collect(struct Generation *g)
{
  g->collected++;

  g->cursor = g->to->next;
  forward_roots(g);
  forward_previous_generations(g);
  forward_changed_nodes(g);
  search_objects(g);
  finalize_collection(g);

  dc_log("Collected: \n");
}

void forward_roots(struct Generation *g)
{
  for (int i = 0; i < gc_roots_top; i++)
  {
    void **root_ptr = gc_roots[i];
    *root_ptr = forward(g, *root_ptr);
  }

  dc_log("All roots forwarded: \n");
}

void forward_previous_generations(struct Generation *g)
{
  for (int i = 0; i < g->number; i++)
  {
    struct Generation *older_gen = generations[i];
    for (void *ptr = older_gen->from->heap; ptr < older_gen->from->next; ptr += unit_size(ptr))
    {
      struct gc_unit *obj = ptr;
      forward_object_fields(g, ptr);
    }
  }
  dc_log("Previous generations forwarded: \n");
}

void forward_changed_nodes(struct Generation *g)
{
  for (int i = 0; i < changed_nodes_top; i++)
  {
    stella_object *obj = changed_nodes[i];
    forward_object_fields(g, obj);
  }
  changed_nodes_top = 0;

  dc_log("Changed nodes forwarded: \n");
}

void search_objects(struct Generation *g)
{
  while (g->cursor < g->to->next)
  {
    struct gc_unit *obj = g->cursor;
    forward_object_fields(g, g->cursor);
    g->cursor += unit_size(obj);
  }

  dc_log("Searching \n");
}

void forward_object_fields(struct Generation *gen, stella_object *obj)
{
  int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(obj->object_header);
  for (int i = 0; i < field_count; i++)
  {
    obj->object_fields[i] = forward(gen, obj->object_fields[i]);
  }
}

void swap_spaces(struct Generation *gen)
{
  struct Space *temp = gen->from;
  gen->from = gen->to;
  gen->to = temp;
  gen->to->next = gen->to->heap;

  generations[gen->from->gen - 1]->to = gen->from;
  generations[gen->from->gen - 1]->cursor = gen->from->heap;
}

void reset_next_gen(struct Generation *gen)
{
  struct Generation *current_gen = generations[gen->from->gen];
  const struct Generation *next_gen = generations[gen->to->gen];
  current_gen->from->next = gen->from->heap;
  current_gen->to = next_gen->from;
}

void finalize_collection(struct Generation *g)
{
  if (g->from->gen == g->to->gen)
  {
    swap_spaces(g);
    return;
  }

  reset_next_gen(g);
}

void dc_log(const char *text)
{
#ifdef GC_DEBUG
  printf("--------------------------------------------------------------------\n");
  printf(text);
  print_gc_state();
#endif
}
