/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 * 
 * Created on 4 november 2008, 18:48
 */



#ifndef OBJECT_H_
#define	OBJECT_H_

#ifdef SYLPH_PUBLIC
#undef SYLPH_PUBLIC
#endif /* SYLPH_PUBLIC */
#define SYLPH_PUBLIC

#define SYLPH_BEGIN_NAMESPACE namespace Sylph {
#define SYLPH_END_NAMESPACE }

#include <cstddef>

/**
 * \namespace Sylph
 * The Sylph namespace contains everything in LibSylph.
 */


SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

/**
 * Used for LibSylph's garbage collection. It is passed as a parameter to new,
 * e.g.
 * <pre>
 * Array<int>; = new (NoGC) Array<int>(5); // create a length-5 array without GC
 * </pre>
 * This is most often used for creating LibSylph-objects not managed by the
 * garbage collector.
 */
enum GCPlacement {
    UseGC, /**< Use the garbage collector; this is the default */
    NoGC, /**< Do not use the garbage collector for this specific object */
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
 * from Object.<p>
 * Note that arrays of Objects are <b>not</b> garbage collected. Instead, use
 * Sylph::Array if you want a garbage collected, safe Array.
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
    // instead. Maybe we should document this somewhere?
    void* operator new[](size_t size);
    void* operator new[](size_t size, void *p);
    void operator delete[](void* obj);
    void operator delete[](void*, void*);

private:
    static void cleanup(void* obj, void* clientData);
    static bool gc_inited;
#endif
};

/**
 * Creates a new (non-LibSylph) object using the LibSylph garbage
 * collection. Example (using Qt):
 * <pre>
 * QPushButton * but = newgc<QPushButton>("Hello");
 * </pre>
 * The syntax is very similar to that of the normal new operator.
 * @tplreqs T Constructible with @em Args
 * @tplreqs Args none
 */
template<class T, class... Args> T * newgc(const Args&... args);

/**
 * Deletes a (non-LibSylph) object that was previously allocated with LibSylph
 * @c newgc(). Altough explicit deletion is not required when using garbage
 * collection, the function is provided anyways for your convenience.
 * @param t pointer to a class previously allocated with @c newgc
 * @tplreqs T none
 */
template<class T> void deletegc(const T * t);
// Undocumented, do not use directly! 
template<class T> void cleanupgc(void *obj, void *displ);
SYLPH_END_NAMESPACE

#endif	/* OBJECT_H_ */

