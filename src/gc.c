#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "runtime.h"
#include "gc.h"

// ============================ Memory Configuration Constants =============================

#define DEFAULT_MAX_ALLOC_SIZE (800 * 1024)
#define DEFAULT_SPACE_SIZE_MULTIPLIER  5
#define GEN_COUNT 2
#define MAX_GC_ROOTS 4096
#define MAX_CHANGED_NODES 8192
// #define GC_DEBUG // uncomment for debug

// ========================= Global Statistics Variables ============================

int MAX_ALLOC_SIZE = 0; // define in runtime

// Total allocated number of bytes
int total_allocated_bytes = 0;
int total_requested_bytes = 0;

// Total allocated number of objects
int total_allocated_objects = 0;

int max_allocated_bytes = 0;
int max_allocated_objects = 0;
int total_reads = 0;
int total_writes = 0;

int gc_roots_max_size = 0;
int gc_roots_top = 0;
void **gc_roots[MAX_GC_ROOTS];
int changed_nodes_top = 0;
void *changed_nodes[MAX_CHANGED_NODES];

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

// Обертка над stella object
struct gc_unit
{
  void *moved_to;
  stella_object stella_object;
};

// Структура инкапсулирующая данные о конкретном space
struct Space
{
  GenType gen; // принадлежность к поколению
  int size; // размер выделенной памяти на space
  void *next; // первый свободный байт
  void *heap; // указатель на начало хипа
};

// Структура инкапсулирующая данные о конкретном поколении
struct Generation
{
  GenType number; // номер поколения
  int collected; // кол-во соборок мусора
  struct Space *from; // указатель на fromSpace
  struct Space *to; // указатель на toSpace
  void *cursor; // переменная для реализации копирующей сборки мусора
};

// ========================= Function Declarations ============================

// memory
void init_space(struct Space *space, GenType gen, int size); // инициализация space
void init_generation(struct Generation *generation, GenType gen_type, struct Space *from_space, struct Space *to_space); // инициализация поколения
int read_env_as_int(const char *env_var_name, int default_value); // чтение нужной переменной изи env
void init_memory();
void *safe_malloc(size_t size);
void handle_memory_error();
struct gc_unit *alloc_in_space(struct Space *space, size_t size_in_bytes);
void *try_alloc(struct Generation *g, size_t size_in_bytes);

// log & statistic
void gc_log(const char *text); // лог gc с выводом состояния памяти
void update_allocation_stats(size_t size_in_bytes);
void print_space(const struct Space *space); // вывод состояния памяти

// common
void gc_collect(); // инициация сборки мусора
bool in_heap(const void *ptr, const void *heap, size_t heap_size); // предикат определения нахождения указателя на куче
size_t get_stella_object_size(const stella_object *obj);

// gc_unit
size_t unit_size(const struct gc_unit *obj); // вес объекта gc
struct gc_unit *get_gc_unit(void *st_ptr); // получения указателя на объект gc по указателю объекта stella
stella_object *get_stella_object(struct gc_unit *gc_ptr); // reverse get_gc_unit

// space
bool is_valid(const struct Space *space, const void *ptr); // предикат указателя в спейсе
bool has_space(const struct Space *space, size_t requested_size);

// generation
void collect(struct Generation *g); // сборка в поколении
// Функции относящиеся к сборке мусора
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
  if (result == NULL)
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
  printf("| %-30s | %d bytes (%d objects)   |\n", "Total memory requested:", total_requested_bytes, total_allocated_objects);
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
  printf("Cursor: %-15p | Next: %-15p | Limit: %-15p\n", g->cursor, g->to->next, g->to->heap + g->to->size);
  printf("--------------------------------------------------------------------\n");
}

void print_gc_state()
{
  print_state(&g0);
  print_state(&g1);
  print_gc_roots();
}

void print_gc_roots()
{
  printf("Roots:\n");
  printf("--------------------------------------------------------------------\n");
  for (int i = 0; i < gc_roots_top; i++)
  {
    printf(
      "\tIndex: %-5d | Address: %-15p | From: %-5s | Value: %-15p\n", 
      i,
      gc_roots[i],
      is_valid(g0.from, *gc_roots[i]) ? "G_0" : is_valid(g1.from, *gc_roots[i]) ? "G_1" : "OTHER",
      *gc_roots[i]
    );
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

int read_env_as_int(const char *env_var_name, int default_value)
{
    char *env_value = getenv(env_var_name);
    int result = 0;

    if (env_value == NULL) 
    {
        return default_value;
    }

    for (int i = 0; env_value[i] != '\0'; i++) 
    {
        if (env_value[i] >= '0' && env_value[i] <= '9') 
        {
            result = result * 10 + (env_value[i] - '0');
        } 
        else 
        {
            printf("Invalid input in environment variable '%s': %s\n", env_var_name, env_value);
            exit(1);
        }
    }

    return result;
}

void init_memory()
{
  if (initialized)
  {
    return;
  }

  MAX_ALLOC_SIZE = read_env_as_int("MAX_ALLOC_SIZE", DEFAULT_MAX_ALLOC_SIZE);
  init_space(&g0_space_from, GENERATION_0, MAX_ALLOC_SIZE);
  int g1_space_size = read_env_as_int("G1_SPACE_SIZE", MAX_ALLOC_SIZE * DEFAULT_SPACE_SIZE_MULTIPLIER);
  printf("G0_SPACE_SIZE = %d\n", MAX_ALLOC_SIZE);
  printf("G1_SPACE_SIZE = %d\n", g1_space_size);

  init_space(&g1_space_from, GENERATION_1, g1_space_size);
  init_space(&g1_space_to, GENERATION_1, g1_space_size);

  init_generation(&g0, GENERATION_0, &g0_space_from, &g1_space_from);
  init_generation(&g1, GENERATION_1, &g1_space_from, &g1_space_to);
  initialized = true;
}

void update_allocation_stats(const size_t size_in_bytes)
{
  total_requested_bytes += size_in_bytes;
  total_allocated_bytes += size_in_bytes + sizeof(void *);
  total_allocated_objects += 1;
  max_allocated_bytes = total_allocated_bytes;
  max_allocated_objects = total_allocated_objects;
}

void gc_collect()
{
  collect(&g0);

  gc_log("Collected\n");
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

    printf("\tGC address: %-15p | ST obj address: %-15p | moved: %-15p | tag: %-2d", gc_ptr, &gc_ptr->stella_object, gc_ptr->moved_to, tag);
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

  // Runtime memory usage
  printf("Boundaries  | from: %-15p | to: %-15p | total: %d bytes\n",
         space->heap,
         space->heap + space->size,
         space->size);
  printf("Free memory | from: %-15p | to: %-15p | total: %ld bytes\n",
         space->next,
         space->heap + space->size,
         space->heap + space->size - space->next);
}

void *try_alloc(struct Generation *g, size_t size_in_bytes)
{
  void *allocated = alloc_in_space(g->from, size_in_bytes);
  return allocated ? allocated + sizeof(void *) : NULL;
}

bool chase(struct Generation *g, struct gc_unit *p)
{
  do {
    struct gc_unit *q = alloc_in_space(g->to, get_stella_object_size(&p->stella_object));
    if (q == NULL) {
      return false;
    }

    const int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(p->stella_object.object_header);
    void *r = NULL;

    q->moved_to = NULL;
    q->stella_object.object_header = p->stella_object.object_header;
    for (int i = 0; i < field_count; i++) {
      q->stella_object.object_fields[i] = p->stella_object.object_fields[i];

      if (is_valid(g->from, q->stella_object.object_fields[i])) {
        struct gc_unit *potentially_forwarded = get_gc_unit(q->stella_object.object_fields[i]);

        if (!is_valid(g->to, potentially_forwarded->moved_to)) {
          r = potentially_forwarded;
        }
      }
    }

    p->moved_to = q;
    p = r;
  } while (p != NULL);

  return true;
}

void *forward(struct Generation *g, void *p)
{
  if (!is_valid(g->from, p))
    return p;

  struct gc_unit *gc_unit = get_gc_unit(p);
  if (is_valid(g->to, gc_unit->moved_to))
    return get_stella_object(gc_unit->moved_to);

  if (!chase(g, gc_unit) && g->to->gen != g->from->gen)
  {
    collect(generations[g->to->gen]);
    if (!chase(g, gc_unit))
      handle_memory_error();
  }
  return get_stella_object(gc_unit->moved_to);
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

  gc_log("Collected: \n");
}

void forward_roots(struct Generation *g)
{
  for (int i = 0; i < gc_roots_top; i++)
  {
    void **root_ptr = gc_roots[i];
    *root_ptr = forward(g, *root_ptr);
  }

  gc_log("All roots forwarded: \n");
}

// run for all objects in prev generations and try find link to collected generation
void forward_previous_generations(struct Generation *g)
{
  for (int i = 0; i < g->number; i++) {
    const struct Generation* past_gen = generations[i];

    for (void *ptr = past_gen->from->heap; ptr < past_gen->from->next; ptr += unit_size(ptr)) {
      struct gc_unit *obj = ptr;
      const int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(obj->stella_object.object_header);
      for (int j = 0; j < field_count; j++) {
        obj->stella_object.object_fields[j] = forward(g, obj->stella_object.object_fields[j]);
      }
    }
  }
  gc_log("Previous generations forwarded: \n");
}

void forward_changed_nodes(struct Generation *g)
{
  for (int i = 0; i < changed_nodes_top; i++) {
    stella_object *obj = changed_nodes[i];
    const int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(obj->object_header);
    for (int j = 0; j < field_count; j++) {
      obj->object_fields[j] = forward(g, obj->object_fields[j]);
    }

    changed_nodes_top = 0;
  }

  gc_log("Changed nodes forwarded: \n");
}

void search_objects(struct Generation *g)
{
  while (g->cursor < g->to->next) {
    struct gc_unit *obj = g->cursor;
    const int field_count = STELLA_OBJECT_HEADER_FIELD_COUNT(obj->stella_object.object_header);
    for (int i = 0; i < field_count; i++) {
      obj->stella_object.object_fields[i] = forward(g, obj->stella_object.object_fields[i]);
    }

    g->cursor += unit_size(obj);
  }

  gc_log("Searching \n");
}

void swap_spaces(struct Generation *g)
{
  void *buff = g->from;
  g->from = g->to;
  g->to = buff;

  g->to->next = g->to->heap;

  struct Generation* past = generations[g->from->gen - 1];
  past->to = g->from;
  past->cursor = g->from->heap;
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

void gc_log(const char *text)
{
#ifdef GC_DEBUG
  printf("--------------------------------------------------------------------\n");
  printf(text);
  print_gc_state();
#endif
}
