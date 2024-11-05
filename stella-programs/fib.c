#include "../src/runtime.h"
#include <locale.h>

stella_object *_stella_id_helper;
stella_object *_stella_id_fib;
stella_object *_stella_id_main;
stella_object *_stella_id__stella_cls_2(stella_object *closure, stella_object *_stella_id_r) {;
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
#ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_2 (");
  printf("r = "); print_stella_object(_stella_id_r);
  printf(") with ");
#endif
#ifdef STELLA_DEBUG
  printf("\n");
#endif
  gc_push_root((void**)&_stella_id_r);
  _stella_reg_1 = alloc_stella_object(TAG_TUPLE, 3);
  _stella_reg_3 = _stella_id_r;
  _stella_reg_3 = STELLA_OBJECT_READ_FIELD(_stella_reg_3, 0);
  _stella_reg_2 = _stella_reg_3;
  _stella_reg_3 = nat_to_stella_object(1);
  _stella_reg_3 = nat_to_stella_object(stella_object_to_nat(_stella_reg_2) - stella_object_to_nat(_stella_reg_3));
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_reg_3);
  _stella_reg_2 = _stella_id_r;
  _stella_reg_2 = STELLA_OBJECT_READ_FIELD(_stella_reg_2, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_reg_2);
  _stella_reg_3 = _stella_id_r;
  _stella_reg_3 = STELLA_OBJECT_READ_FIELD(_stella_reg_3, 1);
  _stella_reg_2 = _stella_reg_3;
  _stella_reg_4 = _stella_id_r;
  _stella_reg_4 = STELLA_OBJECT_READ_FIELD(_stella_reg_4, 2);
  _stella_reg_3 = _stella_reg_4;
  _stella_reg_3 = nat_to_stella_object(stella_object_to_nat(_stella_reg_2) + stella_object_to_nat(_stella_reg_3));
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 2, _stella_reg_3);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_r);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_1(stella_object *closure, stella_object *_stella_id_i) {;
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
#ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_1 (");
  printf("i = "); print_stella_object(_stella_id_i);
  printf(") with ");
#endif
#ifdef STELLA_DEBUG
  printf("\n");
#endif
  gc_push_root((void**)&_stella_id_i);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_2);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_i);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_fn__stella_id_helper(stella_object *_cls, stella_object *_stella_id_p) {
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
#ifdef STELLA_DEBUG
  printf("[debug] call function helper(");
  printf("p = "); print_stella_object(_stella_id_p);
  printf(")\n");
#endif
  gc_push_root((void**)&_stella_id_p);
  _stella_reg_2 = _stella_id_p;
  _stella_reg_2 = STELLA_OBJECT_READ_FIELD(_stella_reg_2, 0);
  _stella_reg_1 = _stella_reg_2;
  _stella_reg_2 = _stella_id_p;
  _stella_reg_4 = alloc_stella_object(TAG_FN, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 0, _stella_id__stella_cls_1);
  _stella_reg_3 = _stella_reg_4;
  _stella_reg_1 = stella_object_nat_rec(_stella_reg_1, _stella_reg_2, _stella_reg_3);
  gc_pop_root((void**)&_stella_id_p);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_helper = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_helper } } ;
stella_object *_stella_id_helper = (stella_object *)&_cls__stella_id_helper;
stella_object *_fn__stella_id_fib(stella_object *_cls, stella_object *_stella_id_n) {
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
#ifdef STELLA_DEBUG
  printf("[debug] call function fib(");
  printf("n = "); print_stella_object(_stella_id_n);
  printf(")\n");
#endif
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_2 = _stella_id_helper;
  _stella_reg_4 = alloc_stella_object(TAG_TUPLE, 3);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 0, _stella_id_n);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 1, nat_to_stella_object(0));
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 2, nat_to_stella_object(1));
  _stella_reg_3 = _stella_reg_4;
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_2, 0))(_stella_reg_2, _stella_reg_3);
  _stella_reg_1 = STELLA_OBJECT_READ_FIELD(_stella_reg_1, 1);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_fib = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_fib } } ;
stella_object *_stella_id_fib = (stella_object *)&_cls__stella_id_fib;
stella_object *_fn__stella_id_main(stella_object *_cls, stella_object *_stella_id_n) {
  stella_object *_stella_reg_1, *_stella_reg_2;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
#ifdef STELLA_DEBUG
  printf("[debug] call function main(");
  printf("n = "); print_stella_object(_stella_id_n);
  printf(")\n");
#endif
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_1 = _stella_id_fib;
  _stella_reg_2 = _stella_id_n;
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_1, 0))(_stella_reg_1, _stella_reg_2);
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_main = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_main } } ;
stella_object *_stella_id_main = (stella_object *)&_cls__stella_id_main;

int main(int argc, char **argv) {
  int n;
  setlocale(LC_NUMERIC, "");
  scanf("%d", &n);
#ifdef STELLA_DEBUG
  printf("[debug] input n = %d\n", n);
#endif
  print_stella_object(_fn__stella_id_main(_stella_id_main, nat_to_stella_object(n))); printf("\n");
  print_stella_stats();
  return 0;
}
