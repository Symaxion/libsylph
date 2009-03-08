#include "Object.h"

#include <gc.h>

#include <new>

SYLPH_START_NAMESPACE(Core)
Object::Object() {
}

Object::~Object() {
}

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
    return Object::operator new(size);
}

inline void* Object::operator new[](size_t size, GCPlacement gcp) {
    return Object::operator new( size, gcp);
}

inline void* Object::operator new[](size_t size, void *p) {
    return p;
}

inline void Object::operator delete[](void* obj) {
    Object::operator delete( obj);
}


inline void Object::operator delete[](void*, void*) {
}

inline void Object::operator delete[](void* p, GCPlacement gcp) {
    Object::operator delete(p);
}

SYLPH_END_NAMESPACE(Core)
