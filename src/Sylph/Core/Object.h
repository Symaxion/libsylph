/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 * Created on 4 november 2008, 18:48
 */



#ifndef SYLPH_CORE_OBJECT_H_
#define	SYLPH_CORE_OBJECT_H_

#define SYLPH_BEGIN_NAMESPACE namespace Sylph {
#define SYLPH_END_NAMESPACE }

#include <cstddef>

/**
 * \namespace Sylph
 * The Sylph namespace contains everything in LibSylph.
 */


SYLPH_BEGIN_NAMESPACE

/**
 * null is a safe %null pointer. It can only be assigned to pointers, not to
 * ints. Therefore, no overload confusion can happen. E.g.:
 * <pre>
 * \#define NULL 0
 * int* i1 = NULL; // works
 * int  i2 = NULL; // works too, but maybe not what you want
 *
 * \#undef NULL
 * \#define NULL ((void*)0)
 * int* i3 = NULL; // does not work
 * int* i4 = (int*)NULL; // needs explicit cast in C++
 * int  i5 = NULL; // does not work -- like expected
 *
 * int* i5 = null; // works
 * int  i6 = null; // does not work -- like expected
 * </pre>
 */
struct null {
    null() {}
    template<class T>
    operator T*() const {
	return 0;
    }

    template<class C, class T>
    operator T C::*() const {
	return 0;
    }
private:
    null(const null&);
    null& operator=(const null&);
    void operator&() const;
};

static struct null null;

class SerializationBuffer;
class DeserializationBuffer;

/**
 * Placement new values for altering LibSylph's garbage collection's behavior.
 * The values in this enumeration are passed to placement-new, e.g.
 * <pre>
 * Array<int>; = new (NoGC) Array<int>(5); // create a length-5 array without GC
 * </pre>
 *
 * The most common use of the GC placement new as shown above is to disable GC
 * for a particular object, GC is enabled by default.
 */
enum GCPlacement {
    UseGC, /**< Use the garbage collector; this is the default. */
    NoGC, /**< Do not use the garbage collector for this specific object. */
    PointerFreeGC /**< When the object you create does not contain pointers,
                   * use this to speed up GC -- however, this is usually not
                   * useful, as most LibSylph containers contain pointers. */
};

/**
 * The root of all classes. This class contains the overloaded new and delete
 * operators that use the builtin garbage collection. (Almost) all classes in
 * LibSylph inherit from this class. If you want your class to communicate with
 * certain LibSylph features, or just if you want to let LibSylph's
 * garbage collector manage dynamic allocation of your class, you should derive
 * from Object.
 *
 * Note that arrays of Objects are <b>not</b> garbage collected. Instead, use
 * Sylph::Array if you want a garbage collected, safe %Array.
 */
class Object {
#ifndef SYLPH_DOXYGEN
public:
    Object();
    virtual ~Object();
    void* operator new( size_t size);
    void* operator new( size_t size, GCPlacement gcp);
    void* operator new( size_t size, void *p);
    void operator delete( void* obj);
    void operator delete( void*, GCPlacement);
    void operator delete( void*, void*);

    // Arrays from Object are *never* gc'ed, and I recommend using Sylph::Array
    // instead.
    void* operator new[](size_t size);
    void* operator new[](size_t size, void *p);
    void operator delete[](void* obj);
    void operator delete[](void*, void*);

private:
    static void cleanup(void* obj, void* clientData);
    static bool gc_inited;
#endif
};

#ifndef SYLPH_NO_CXX0X
/**
 * Creates a new (non-LibSylph) object using the LibSylph garbage
 * collection. Example (using Qt):
 * <pre>
 * QPushButton * but = newgc<QPushButton>("Hello");
 * </pre>
 * The syntax is very similar to that of the normal new operator.
 *
 * @tplreqs T Constructible with @em Args
 * @tplreqs Args none
 */
template<class T, class... Args> T * newgc(const Args&... args);

/**
 * Deletes a (non-LibSylph) object that was previously allocated with LibSylph
 * @c newgc(). Altough explicit deletion is not required when using garbage
 * collection, the function is provided anyways for your convenience.
 *
 * Deleting an object allocated with @c newgc with <code>operator delete</code>
 * or deleting an object not allocated with @c newgc with @c deletegc is
 * undefined behavior.
 *
 * @param t pointer to a class previously allocated with @c newgc
 * @tplreqs T none
 */
template<class T> void deletegc(const T * t);
// Undocumented, do not use directly! 
template<class T> void cleanupgc(void *obj, void *displ);
#endif
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_OBJECT_H_ */

