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

// seems a good place to document Sylph, Core, and OS namespaces, no?

/**
 * \namespace Sylph
 * The Sylph namespace contains everything in LibSylph.
 */
/**
 * \namespace Sylph::Core
 * The Sylph::Core namespace contains the fundamental classes of LibSylph.
 * Examples are Application, Object, String, Vector, ....
 * <p>
 * <b>Dependancies:</b> Sylph::OS
 * <b>Cross-platform?</b> Most classes are cross-platform, but Array currently
 * depends on C++0x initializer_lists.
 * </p>
 */

/**
 * \namespace Sylph::OS
 * The Sylph::OS namespace contains all portability modules. Currently there is
 * support for Mac OS X and Linux. Minimal Windows support is present as well.
 * <p>
 * <b>Dependancies:</b> None
 * <b>Cross-platform?</b> Yes, by definition.
 * </p>
 */

/**
 * Used for LibSylph's garbage collection. It is passed as a parameter to new,
 * e.g.
 * <code>
 * Array<int>; = new (NoGC) Array<int>(5); // create a length-5 array without GC
 * </code>
 * This is most often used for creating LibSylph-objects not managed by the
 * garbage collector.
 */
enum GCPlacement {
    UseGC, /** < Use the garbage collector. This is the default */
    NoGC, /** < Do not use the garbage collector for this specific object */
    PointerFreeGC /** < When the object you create does not contain pointers,
                   * use this to speed up GC. However, this is usually not
                   * useful, as most LibSylph containers contain pointers. */
};

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC

/**
 * The root of all classes. This class contains the overloaded new and delete
 * operators. All classes in LibSylph extend from this class. If you want your
 * class to communicate with LibSylph, or just if you want to let LibSylph's
 * garbage collector manage dynamic allocation of your class, you should derive
 * from Object.
 */
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

