#include "Object.h"

#include <gc.h>

#include <new>

SYLPH_BEGIN_NAMESPACE

inline void* Object::operator new( size_t size) {
    return GC_MALLOC(size);
}

inline void* Object::operator new( size_t size, GCPlacement gcp) {
    if (gcp == UseGC)
        return GC_MALLOC(size);
    else if (gcp == PointerFreeGC)
        return GC_MALLOC_ATOMIC(size);
    else
        return GC_MALLOC_UNCOLLECTABLE(size);
}

inline void* Object::operator new( size_t size, void *p) {
    return p;
}

inline void Object::operator delete( void* obj) {
    GC_FREE(obj);
}

inline void Object::operator delete( void*, void*) {
}

inline void Object::operator delete( void* p, GCPlacement gcp) {
    GC_FREE(p);
}

inline void* Object::operator new[](size_t size) {
    return Object::operator new(size, NoGC);
}

inline void* Object::operator new[](size_t size, void *p) {
    return p;
}

inline void Object::operator delete[](void* obj) {
    Object::operator delete(obj);
}

inline void Object::operator delete[](void*, void*) {
}

inline Object::~Object() {
    GC_register_finalizer_ignore_self(GC_base(this), 0, 0, 0, 0);
}

inline void Object::cleanup(void* obj, void* displ) {
    ((Object*) ((char*) obj + (ptrdiff_t) displ))->~Object();
}

inline Object::Object() {
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


SYLPH_END_NAMESPACE
