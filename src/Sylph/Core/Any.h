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
 * Created on 22 maart 2009, 16:40
 */

#ifndef SYLPH_CORE_ANY_H_
#define	SYLPH_CORE_ANY_H_

#include "Object.h"
#include "Exception.h"
#include "Primitives.h"

#include <typeinfo>

SYLPH_BEGIN_NAMESPACE

/**
 * Wrapper class for any kind of class. Any allows you to wrap any kind of class
 * in it, in other words, it acts as an universal supertype. It is similar to
 * what <code>void*</code> was used in C, but safer to use (wrong casts return
 * a null pointer instead of a corrupted pointer). Any is useful for using in
 * collections, it will allow any kind of object to be stored in a single
 * collection. Other languages or toolkits use a superclass for this purpose,
 * (e.g. Object), but this does not take primitive or alien (i.e. from another
 * API) types into account. Any can be used safely for such purposes and is
 * recommended over <code>void*</code> or Object. <p>
 * An example of a predefined collection using Any is Dictionary, which acts
 * as a HashMap of String,Any.
 */
class Any : public virtual Object {
    template<class T> friend T* any_cast(Any & any);
public:

    /**
     * Creates a new, empty Any object. The internal pointer will be initialized
     * to <code>null</code>.
     */
    Any() : content(null) {}
    template<class T>
    /**
     * Creates a new Any object from an existing object. The object will be
     * copied, therefore it is advised you only use easy-to-copy data, such
     * as primitives, reference counted data, or pointers.<p>
     * Note: Any will <b>not</b> take ownership over pointers.
     * @param value The value the new instance of Any will point to.
     */
    Any(const T & value) : content(new AnyContainer<T>(value)) {}

    /**
     * Copies this Any object from another Any object. The internal pointer will
     * be copied to this new Any object.
     */
    Any(const Any & other) : content(other.content ?
          other.content->clone() : 0) {}
    /**
     * Default destructor.
     */
    ~Any() { delete content; }

    /**
     * Check if this Any is pointing to something.
     * @return <i>true</i> if the internal pointer is a <code>null</code>
     * pointer, <i>false</i> otherwise.
     */
    bool empty() { return !content; }

    /**
     * Gets the typeinfo of the data pointed to. The result returned is
     * compatible with the return value of the <code>typeid</code> operator,
     * which means that you can check if the Any can be casted to a type using
     * its <code>typeid</code>. E.g:
     * <pre>
     * if(myany.type() == typeid(int)) {
     *     // safe to cast to int here
     * } else {
     *     // give some error message about the wrong type
     * }
     * </pre>
     * If the internal data pointer is a <code>null</code> pointer, it will
     * return the <code>typeid</code> of <code>void</code>.
     */
    const std::type_info & type() const {
        return content ? content->type() : typeid(void);
    }

    /**
     * Assigns an other Any instance to this one. The assignment simply consists
     * of copying the internal data pointer to this Any.
     * @param rhs An other Any instance to copy the data pointer from.
     * @return The current Any, modified to be equal to the other Any.
     */
    Any & operator=(const Any & rhs) {
        this->content = rhs.content;
        return *this;
    }

    /**
     * Assigns a new value to this Any. Again, the value can be of any type, and
     * is not restricted by the type that had been before in the Any. The
     * internal data pointer gets completely replaced by a new one, pointing to
     * the new data.
     * @param value A new value for the Any to point to.
     * @return The current any, with the updated data pointer.
     */
    template<class T>
    Any & operator=(T & value) {
        delete this->content;
        this->content = new AnyContainer<T>(value);
        return *this;
    }
private:

    class AnyContainerBase {
    public:

        virtual ~AnyContainerBase() {
        }
        virtual const std::type_info & type() const = 0;
        virtual AnyContainerBase * clone() const = 0;
    };

    template<class T>
    class AnyContainer : public AnyContainerBase {
    public:

        AnyContainer(const T & value) : held(value) {
        }

        virtual const std::type_info & type() const {
            return typeid (T);
        }

        virtual AnyContainerBase * clone() const {
            return new AnyContainer<T>(held);
        }

        T held;

    private:
        AnyContainer<T> & operator=(const AnyContainer<T> &);

    };

    AnyContainerBase * content;
};

/**
 * Cast an Any to the type it is holding. This cast is completely safe, and
 * either returns a correct pointer, or completely fails.
 * @param any An Any to convert to an instance of the type it is representing
 * @return A pointer to the internal data of the Any if the conversion was
 * successful, <code>null</code> otherwise.
 */
template<class T> T * any_cast(Any & any) {
    check_nullptr(any.content);
    if(any.type() != typeid(T)) return null;
    else return &(*(static_cast<Any::AnyContainer<T> *>(any.content))->held);
}
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_ANY_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
