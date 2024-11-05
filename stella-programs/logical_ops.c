#include "../src/runtime.h"
#include <locale.h>

stella_object *_stella_id_Bool__not;
stella_object *_stella_id_Bool__or;
stella_object *_stella_id_Bool__and;
stella_object *_stella_id_Bool__xor;
stella_object *_stella_id_main;
stella_object *_stella_id__stella_cls_1(stella_object *closure, stella_object *_stella_id_b) {;
  stella_object *_stella_id_a; // a
  stella_object *_stella_reg_1, *_stella_reg_2;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_1 (");
  printf("b = "); print_stella_object(_stella_id_b);
  printf(") with ");
  #endif
  _stella_id_a = STELLA_OBJECT_READ_FIELD(closure, 1);
  #ifdef STELLA_DEBUG
  printf("a = "); print_stella_object(_stella_id_a);
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_b);
  gc_push_root((void**)&_stella_id_a);
  _stella_reg_1 = _stella_id_a;
  if (_stella_reg_1 == &the_TRUE) {
    _stella_reg_2 = &the_TRUE;
  } else {
    _stella_reg_2 = _stella_id_b;
  }
  _stella_reg_1 = _stella_reg_2;
  gc_pop_root((void**)&_stella_id_a);
  gc_pop_root((void**)&_stella_id_b);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_2(stella_object *closure, stella_object *_stella_id_b) {;
  stella_object *_stella_id_a; // a
  stella_object *_stella_reg_1, *_stella_reg_2;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_2 (");
  printf("b = "); print_stella_object(_stella_id_b);
  printf(") with ");
  #endif
  _stella_id_a = STELLA_OBJECT_READ_FIELD(closure, 1);
  #ifdef STELLA_DEBUG
  printf("a = "); print_stella_object(_stella_id_a);
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_b);
  gc_push_root((void**)&_stella_id_a);
  _stella_reg_1 = _stella_id_a;
  if (_stella_reg_1 == &the_TRUE) {
    _stella_reg_2 = _stella_id_b;
  } else {
    _stella_reg_2 = &the_FALSE;
  }
  _stella_reg_1 = _stella_reg_2;
  gc_pop_root((void**)&_stella_id_a);
  gc_pop_root((void**)&_stella_id_b);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_3(stella_object *closure, stella_object *_stella_id_b) {;
  stella_object *_stella_id_a; // a
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4, *_stella_reg_5, *_stella_reg_6, *_stella_reg_7, *_stella_reg_8;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
  gc_push_root((void**)&_stella_reg_5);
  gc_push_root((void**)&_stella_reg_6);
  gc_push_root((void**)&_stella_reg_7);
  gc_push_root((void**)&_stella_reg_8);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_3 (");
  printf("b = "); print_stella_object(_stella_id_b);
  printf(") with ");
  #endif
  _stella_id_a = STELLA_OBJECT_READ_FIELD(closure, 1);
  #ifdef STELLA_DEBUG
  printf("a = "); print_stella_object(_stella_id_a);
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_b);
  gc_push_root((void**)&_stella_id_a);
  _stella_reg_3 = _stella_id_Bool__or;
  _stella_reg_7 = _stella_id_Bool__and;
  _stella_reg_8 = _stella_id_a;
  _stella_reg_5 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_7, 0))(_stella_reg_7, _stella_reg_8);
  _stella_reg_7 = _stella_id_Bool__not;
  _stella_reg_8 = _stella_id_b;
  _stella_reg_6 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_7, 0))(_stella_reg_7, _stella_reg_8);
  _stella_reg_4 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_5, 0))(_stella_reg_5, _stella_reg_6);
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_3, 0))(_stella_reg_3, _stella_reg_4);
  _stella_reg_5 = _stella_id_Bool__and;
  _stella_reg_7 = _stella_id_Bool__not;
  _stella_reg_8 = _stella_id_a;
  _stella_reg_6 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_7, 0))(_stella_reg_7, _stella_reg_8);
  _stella_reg_3 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_5, 0))(_stella_reg_5, _stella_reg_6);
  _stella_reg_4 = _stella_id_b;
  _stella_reg_2 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_3, 0))(_stella_reg_3, _stella_reg_4);
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_1, 0))(_stella_reg_1, _stella_reg_2);
  gc_pop_root((void**)&_stella_id_a);
  gc_pop_root((void**)&_stella_id_b);
  gc_pop_root((void**)&_stella_reg_8);
  gc_pop_root((void**)&_stella_reg_7);
  gc_pop_root((void**)&_stella_reg_6);
  gc_pop_root((void**)&_stella_reg_5);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_fn__stella_id_Bool__not(stella_object *_cls, stella_object *_stella_id_b) {
  stella_object *_stella_reg_1, *_stella_reg_2;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  #ifdef STELLA_DEBUG
  printf("[debug] call function Bool::not(");
  printf("b = "); print_stella_object(_stella_id_b);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_b);
  _stella_reg_1 = _stella_id_b;
  if (_stella_reg_1 == &the_TRUE) {
    _stella_reg_2 = &the_FALSE;
  } else {
    _stella_reg_2 = &the_TRUE;
  }
  _stella_reg_1 = _stella_reg_2;
  gc_pop_root((void**)&_stella_id_b);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_Bool__not = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_Bool__not } } ;
stella_object *_stella_id_Bool__not = (stella_object *)&_cls__stella_id_Bool__not;
stella_object *_fn__stella_id_Bool__or(stella_object *_cls, stella_object *_stella_id_a) {
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] call function Bool::or(");
  printf("a = "); print_stella_object(_stella_id_a);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_a);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_id_a);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_a);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_Bool__or = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_Bool__or } } ;
stella_object *_stella_id_Bool__or = (stella_object *)&_cls__stella_id_Bool__or;
stella_object *_fn__stella_id_Bool__and(stella_object *_cls, stella_object *_stella_id_a) {
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] call function Bool::and(");
  printf("a = "); print_stella_object(_stella_id_a);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_a);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_id_a);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_a);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_Bool__and = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_Bool__and } } ;
stella_object *_stella_id_Bool__and = (stella_object *)&_cls__stella_id_Bool__and;
stella_object *_fn__stella_id_Bool__xor(stella_object *_cls, stella_object *_stella_id_a) {
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] call function Bool::xor(");
  printf("a = "); print_stella_object(_stella_id_a);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_a);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_3);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_id_a);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_a);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_Bool__xor = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_Bool__xor } } ;
stella_object *_stella_id_Bool__xor = (stella_object *)&_cls__stella_id_Bool__xor;
stella_object *_fn__stella_id_main(stella_object *_cls, stella_object *_stella_id_n) {
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4, *_stella_reg_5, *_stella_reg_6, *_stella_reg_7, *_stella_reg_8;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
  gc_push_root((void**)&_stella_reg_5);
  gc_push_root((void**)&_stella_reg_6);
  gc_push_root((void**)&_stella_reg_7);
  gc_push_root((void**)&_stella_reg_8);
  #ifdef STELLA_DEBUG
  printf("[debug] call function main(");
  printf("n = "); print_stella_object(_stella_id_n);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_3 = _stella_id_Bool__xor;
  _stella_reg_7 = _stella_id_Bool__and;
  _stella_reg_8 = _stella_id_n;
  _stella_reg_5 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_7, 0))(_stella_reg_7, _stella_reg_8);
  _stella_reg_7 = _stella_id_Bool__not;
  _stella_reg_8 = _stella_id_n;
  _stella_reg_6 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_7, 0))(_stella_reg_7, _stella_reg_8);
  _stella_reg_4 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_5, 0))(_stella_reg_5, _stella_reg_6);
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_3, 0))(_stella_reg_3, _stella_reg_4);
  _stella_reg_5 = _stella_id_Bool__or;
  _stella_reg_7 = _stella_id_Bool__not;
  _stella_reg_8 = _stella_id_n;
  _stella_reg_6 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_7, 0))(_stella_reg_7, _stella_reg_8);
  _stella_reg_3 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_5, 0))(_stella_reg_5, _stella_reg_6);
  _stella_reg_4 = _stella_id_n;
  _stella_reg_2 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_3, 0))(_stella_reg_3, _stella_reg_4);
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_1, 0))(_stella_reg_1, _stella_reg_2);
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_reg_8);
  gc_pop_root((void**)&_stella_reg_7);
  gc_pop_root((void**)&_stella_reg_6);
  gc_pop_root((void**)&_stella_reg_5);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
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