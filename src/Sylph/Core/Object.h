/*
 * File:   object.h
 * Author: SeySayux <seysayux@gmail.com>
 *
 * Created on 4 november 2008, 18:48
 */

#ifndef _OBJECT_H
#define	_OBJECT_H

#ifdef SYLPH_PUBLIC
#undef SYLPH_PUBLIC
#endif /* SYLPH_PUBLIC */
#define SYLPH_PUBLIC
#define interface class

#define SYLPH_START_NAMESPACE(_x) namespace Sylph { namespace _x {
#define SYLPH_END_NAMESPACE(_x) }}

#include <cstddef>

enum GCPlacement {
    UseGC,
    NoGC,
    PointerFreeGC
};

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
class Object {
public:
    Object();
    virtual ~Object();
    inline void* operator new( size_t size);
    inline void* operator new( size_t size, GCPlacement gcp);
    inline void* operator new( size_t size, void *p);
    /* Must be redefined here, since the other overloadings	*/
    /* hide the global definition.				*/
    inline void operator delete( void* obj);
    inline void operator delete( void*, GCPlacement);
    /* called if construction fails.	*/
    inline void operator delete( void*, void*);

    inline void* operator new[](size_t size);
    inline void* operator new[](size_t size, GCPlacement gcp);
    inline void* operator new[](size_t size, void *p);
    inline void operator delete[](void* obj);
    inline void operator delete[](void*, GCPlacement);
    inline void operator delete[](void*, void*);
private:

};

SYLPH_END_NAMESPACE(Core)

#endif	/* _OBJECT_H */

