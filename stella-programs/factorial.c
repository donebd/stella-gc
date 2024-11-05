#include "../src/runtime.h"
#include <locale.h>

stella_object *_stella_id_Nat2Nat__const;
stella_object *_stella_id_Nat__add;
stella_object *_stella_id_Nat__mul;
stella_object *_stella_id_factorial;
stella_object *_stella_id_main;
stella_object *_stella_id__stella_cls_1(stella_object *closure, stella_object *_stella_id_x) {;
  stella_object *_stella_id_f; // f
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_1 (");
  printf("x = "); print_stella_object(_stella_id_x);
  printf(") with ");
  #endif
  _stella_id_f = STELLA_OBJECT_READ_FIELD(closure, 1);
  #ifdef STELLA_DEBUG
  printf("f = "); print_stella_object(_stella_id_f);
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_x);
  gc_push_root((void**)&_stella_id_f);
  _stella_reg_1 = _stella_id_f;
  gc_pop_root((void**)&_stella_id_f);
  gc_pop_root((void**)&_stella_id_x);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_4(stella_object *closure, stella_object *_stella_id_r) {;
  stella_object *_stella_reg_1, *_stella_reg_2;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_4 (");
  printf("r = "); print_stella_object(_stella_id_r);
  printf(") with ");
  #endif
  #ifdef STELLA_DEBUG
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_r);
  _stella_reg_1 = _stella_id_r;
  _stella_reg_2 = alloc_stella_object(TAG_SUCC, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_2, 0, _stella_reg_1);
  _stella_reg_1 = _stella_reg_2;
  gc_pop_root((void**)&_stella_id_r);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_3(stella_object *closure, stella_object *_stella_id_i) {;
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_3 (");
  printf("i = "); print_stella_object(_stella_id_i);
  printf(") with ");
  #endif
  #ifdef STELLA_DEBUG
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_i);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_4);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_i);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_2(stella_object *closure, stella_object *_stella_id_m) {;
  stella_object *_stella_id_n; // n
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_2 (");
  printf("m = "); print_stella_object(_stella_id_m);
  printf(") with ");
  #endif
  _stella_id_n = STELLA_OBJECT_READ_FIELD(closure, 1);
  #ifdef STELLA_DEBUG
  printf("n = "); print_stella_object(_stella_id_n);
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_m);
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_1 = _stella_id_n;
  _stella_reg_2 = _stella_id_m;
  _stella_reg_4 = alloc_stella_object(TAG_FN, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 0, _stella_id__stella_cls_3);
  _stella_reg_3 = _stella_reg_4;
  _stella_reg_1 = stella_object_nat_rec(_stella_reg_1, _stella_reg_2, _stella_reg_3);
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_id_m);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_5(stella_object *closure, stella_object *_stella_id_m) {;
  stella_object *_stella_id_n; // n
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4, *_stella_reg_5, *_stella_reg_6, *_stella_reg_7;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
  gc_push_root((void**)&_stella_reg_5);
  gc_push_root((void**)&_stella_reg_6);
  gc_push_root((void**)&_stella_reg_7);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_5 (");
  printf("m = "); print_stella_object(_stella_id_m);
  printf(") with ");
  #endif
  _stella_id_n = STELLA_OBJECT_READ_FIELD(closure, 1);
  #ifdef STELLA_DEBUG
  printf("n = "); print_stella_object(_stella_id_n);
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_m);
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_1 = _stella_id_n;
  _stella_reg_2 = nat_to_stella_object(0);
  _stella_reg_4 = _stella_id_Nat2Nat__const;
  _stella_reg_6 = _stella_id_Nat__add;
  _stella_reg_7 = _stella_id_m;
  _stella_reg_5 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_6, 0))(_stella_reg_6, _stella_reg_7);
  _stella_reg_3 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_4, 0))(_stella_reg_4, _stella_reg_5);
  _stella_reg_1 = stella_object_nat_rec(_stella_reg_1, _stella_reg_2, _stella_reg_3);
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_id_m);
  gc_pop_root((void**)&_stella_reg_7);
  gc_pop_root((void**)&_stella_reg_6);
  gc_pop_root((void**)&_stella_reg_5);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_7(stella_object *closure, stella_object *_stella_id_r) {;
  stella_object *_stella_id_i; // i
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_7 (");
  printf("r = "); print_stella_object(_stella_id_r);
  printf(") with ");
  #endif
  _stella_id_i = STELLA_OBJECT_READ_FIELD(closure, 1);
  #ifdef STELLA_DEBUG
  printf("i = "); print_stella_object(_stella_id_i);
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_r);
  gc_push_root((void**)&_stella_id_i);
  _stella_reg_3 = _stella_id_Nat__mul;
  _stella_reg_4 = _stella_id_r;
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_3, 0))(_stella_reg_3, _stella_reg_4);
  _stella_reg_3 = _stella_id_i;
  _stella_reg_4 = alloc_stella_object(TAG_SUCC, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 0, _stella_reg_3);
  _stella_reg_2 = _stella_reg_4;
  _stella_reg_1 = (*(stella_object *(*)(stella_object *, stella_object *))STELLA_OBJECT_READ_FIELD(_stella_reg_1, 0))(_stella_reg_1, _stella_reg_2);
  gc_pop_root((void**)&_stella_id_i);
  gc_pop_root((void**)&_stella_id_r);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_stella_id__stella_cls_6(stella_object *closure, stella_object *_stella_id_i) {;
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] enter closure _stella_id__stella_cls_6 (");
  printf("i = "); print_stella_object(_stella_id_i);
  printf(") with ");
  #endif
  #ifdef STELLA_DEBUG
  printf("\n");
  #endif
  gc_push_root((void**)&_stella_id_i);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_7);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_id_i);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_i);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object *_fn__stella_id_Nat2Nat__const(stella_object *_cls, stella_object *_stella_id_f) {
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] call function Nat2Nat::const(");
  printf("f = "); print_stella_object(_stella_id_f);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_f);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_id_f);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_f);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_Nat2Nat__const = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_Nat2Nat__const } } ;
stella_object *_stella_id_Nat2Nat__const = (stella_object *)&_cls__stella_id_Nat2Nat__const;
stella_object *_fn__stella_id_Nat__add(stella_object *_cls, stella_object *_stella_id_n) {
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] call function Nat::add(");
  printf("n = "); print_stella_object(_stella_id_n);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_id_n);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_Nat__add = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_Nat__add } } ;
stella_object *_stella_id_Nat__add = (stella_object *)&_cls__stella_id_Nat__add;
stella_object *_fn__stella_id_Nat__mul(stella_object *_cls, stella_object *_stella_id_n) {
  stella_object *_stella_reg_1;
  gc_push_root((void**)&_stella_reg_1);
  #ifdef STELLA_DEBUG
  printf("[debug] call function Nat::mul(");
  printf("n = "); print_stella_object(_stella_id_n);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_1 = alloc_stella_object(TAG_FN, 2);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 0, _stella_id__stella_cls_5);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_1, 1, _stella_id_n);
  _stella_reg_1 = _stella_reg_1;
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_Nat__mul = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_Nat__mul } } ;
stella_object *_stella_id_Nat__mul = (stella_object *)&_cls__stella_id_Nat__mul;
stella_object *_fn__stella_id_factorial(stella_object *_cls, stella_object *_stella_id_n) {
  stella_object *_stella_reg_1, *_stella_reg_2, *_stella_reg_3, *_stella_reg_4;
  gc_push_root((void**)&_stella_reg_1);
  gc_push_root((void**)&_stella_reg_2);
  gc_push_root((void**)&_stella_reg_3);
  gc_push_root((void**)&_stella_reg_4);
  #ifdef STELLA_DEBUG
  printf("[debug] call function factorial(");
  printf("n = "); print_stella_object(_stella_id_n);
  printf(")\n");
  #endif
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_1 = _stella_id_n;
  _stella_reg_3 = nat_to_stella_object(0);
  _stella_reg_4 = alloc_stella_object(TAG_SUCC, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 0, _stella_reg_3);
  _stella_reg_2 = _stella_reg_4;
  _stella_reg_4 = alloc_stella_object(TAG_FN, 1);
  STELLA_OBJECT_INIT_FIELD(_stella_reg_4, 0, _stella_id__stella_cls_6);
  _stella_reg_3 = _stella_reg_4;
  _stella_reg_1 = stella_object_nat_rec(_stella_reg_1, _stella_reg_2, _stella_reg_3);
  gc_pop_root((void**)&_stella_id_n);
  gc_pop_root((void**)&_stella_reg_4);
  gc_pop_root((void**)&_stella_reg_3);
  gc_pop_root((void**)&_stella_reg_2);
  gc_pop_root((void**)&_stella_reg_1);
  return _stella_reg_1;
}
stella_object_1 _cls__stella_id_factorial = { .object_header = TAG_FN, .object_fields = { &_fn__stella_id_factorial } } ;
stella_object *_stella_id_factorial = (stella_object *)&_cls__stella_id_factorial;
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
  _stella_reg_1 = _stella_id_factorial;
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