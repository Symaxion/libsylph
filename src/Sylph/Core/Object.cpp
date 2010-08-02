#include "Object.h"

#include <gc/gc.h>

#include <new>

#ifndef SYLPH_LIKELY
    #if __GNUC__ - 0 >= 3
        #define SYLPH_LIKELY(x) __builtin_expect(!!(x),1)
        #define SYLPH_UNLIKELY(x) __builtin_expect(!!(x),0)
    #else
        #define SYLPH_LIKELY(x) (x)
        #define SYLPH_UNLIKELY(x) (x)
    #endif
#endif

SYLPH_BEGIN_NAMESPACE

bool Object::gc_inited = false;

void* Object::operator new( size_t size) {
    if(SYLPH_UNLIKELY(!Object::gc_inited)) {
        GC_INIT();
        Object::gc_inited = true;
    }
    void * toReturn = GC_MALLOC(size);
    if (!toReturn) throw std::bad_alloc();
    else return toReturn;
}

void* Object::operator new( size_t size, GCPlacement gcp) {
    if(SYLPH_UNLIKELY(!Object::gc_inited)) {
        GC_INIT();
        Object::gc_inited = true;
    }
    void * toReturn;
    if (gcp == UseGC) toReturn = GC_MALLOC(size);
    else if (gcp == PointerFreeGC) toReturn = GC_MALLOC_ATOMIC(size);
    else toReturn = GC_MALLOC_UNCOLLECTABLE(size);
    if (!toReturn) throw std::bad_alloc();
    else return toReturn;
}

void* Object::operator new( size_t size, void *p) {
    return p;
}

void Object::operator delete( void* obj) {
    GC_FREE(obj);
}

void Object::operator delete( void*, void*) { }

void Object::operator delete( void* p, GCPlacement gcp) {
    GC_FREE(p);
}

void* Object::operator new[](size_t size) {
    return Object::operator new(size, NoGC);
}

void* Object::operator new[](size_t size, void *p) {
    return p;
}

void Object::operator delete[](void* obj) {
    Object::operator delete(obj);
}

void Object::operator delete[](void*, void*) { }

Object::~Object() {
    GC_register_finalizer_ignore_self(GC_base(this), 0, 0, 0, 0);
}

void Object::cleanup(void* obj, void* displ) {
    ((Object*) ((char*) obj + (ptrdiff_t) displ))->~Object();
}

Object::Object() {
    GC_finalization_proc oldProc;
    void* oldData;
    void* base = GC_base((void *) this);
    if (0 != base) {
        // Don't call the debug version, since this is a real base address.
        GC_register_finalizer_ignore_self(
                base, (GC_finalization_proc) cleanup, (void*) ((char*) this -(char*) base),
                &oldProc, &oldData);
        if (0 != oldProc) {
            GC_register_finalizer_ignore_self(base, oldProc, oldData, 0, 0);
        }
    }
}

#ifndef SYLPH_NO_CXX0X
template<class T, class... Args> T * newgc(const Args&... args) {
    T * tr = GC_MALLOC(sizeof (T));
    if (!tr) throw std::bad_alloc();
    tr = new(tr) T(args...);
    GC_finalization_proc oldProc;
    void* oldData;
    void* base = GC_base((void *) tr);
    if (0 != base) {
        // Don't call the debug version, since this is a real base address.
        GC_register_finalizer_ignore_self(
                base, (GC_finalization_proc) cleanupgc, (void*) ((char*) tr - (char*) base),
                &oldProc, &oldData);
        if (0 != oldProc) {
            GC_register_finalizer_ignore_self(base, oldProc, oldData, 0, 0);
        }
    }
    return tr;
}

template<class T>
void cleanupgc(void* obj, void* displ) {
    ((T*) ((char*) obj + (ptrdiff_t) displ))->~T();
}

template<class T>
void deletegc(const T * obj) {
    GC_FREE(obj);
}
#endif

SYLPH_END_NAMESPACE
