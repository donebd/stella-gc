project(GC)

set( gc_sources gc.h runtime.h gc.c runtime.c )
add_library( sgc STATIC ${gc_sources} )