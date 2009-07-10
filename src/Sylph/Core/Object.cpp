#include "Object.h"

#include <gc.h>

#include <new>

/*< rev Object-1 >*/

SYLPH_BEGIN_NAMESPACE

void* Object::operator new( size_t size) {
    void * toReturn  = GC_MALLOC(size);
    if(!toReturn) throw std::bad_alloc();
    else return toReturn;
}

void* Object::operator new( size_t size, GCPlacement gcp) {
    void * toReturn;
    if(gcp == UseGC) toReturn = GC_MALLOC(size);
    else if(gcp == PointerFreeGC) toReturn = GC_MALLOC_ATOMIC(size);
    else toReturn = GC_MALLOC_UNCOLLECTABLE(size);
    if(!toReturn) throw std::bad_alloc();
    else return toReturn;
}

void* Object::operator new( size_t size, void *p) {
    return p;
}

void Object::operator delete( void* obj) {
    GC_FREE(obj);
}

void Object::operator delete( void*, void*) {
}

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

void Object::operator delete[](void*, void*) {
}

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


SYLPH_END_NAMESPACE
