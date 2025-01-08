#include "../src/runtime.h"
#include <locale.h>

stella_object *_stella_id_main;
stella_object *_fn__stella_id_main(stella_object *_cls, stella_object *_stella_id_n) {
  stella_object *_stella_reg_1;
#ifdef STELLA_DEBUG
  printf("[debug] call function main(");
  printf("n = "); print_stella_object(_stella_id_n);
  printf(")\n");
#endif
  gc_push_root((void**)&_stella_id_n);
  _stella_reg_1 = _stella_id_n;
  gc_pop_root((void**)&_stella_id_n);
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
