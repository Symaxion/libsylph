/* 
 * File:   Any.h
 * Author: frank
 *
 * Created on 22 maart 2009, 16:40
 */

#ifndef ANY_H_
#define	ANY_H_

#include "Object.h"
#include "Exception.h"
#include "Primitives.h"

#include <typeinfo>

SYLPH_BEGIN_NAMESPACE

template<class T>
class Array;
class String;
class Dictionary;
SYLPH_PUBLIC
class Any : public virtual Object {
    template<class T> friend T & any_cast(Any & any);
public:

    Any() : content(NULL) {}
    template<class T>
    Any(const T & value) : content(new AnyContainer<T>(value)) {}
    Any(const Any & other) : content(other.content ?
          other.content->clone() : 0) {}
    ~Any() { delete content; }

    bool empty() { return !content; }
    const std::type_info & type() const {
        return content ? content->type() : typeid(void);
    }

    inline Primitive primtype() {
        if(type() == typeid(int)) return T_Integer;
        else if(type == typeid(long)) return T_Long;
        else if(type == typeid(float)) return T_Float;
        else if(type == typeid(double)) return T_Double;
        else if(type == typeid(bool)) return T_Bool;
        else if(type == typeid(Array)) return T_Array;
        else if(type == typeid(String)) return T_String;
        else if(type == typeid(Dictionary)) return T_Dictionary;
        else return FAIL;
    }

    Any & operator=(const Any & rhs) {
        this->content = rhs.content;
    }
    template<class T>
    Any & operator=(T & value) {
        delete this->content;
        this->content = new AnyContainer<T>(value);
    };
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

        holder(const T & value) : held(value) {
        }

        virtual const std::type_info & type() const {
            return typeid (T);
        }

        virtual AnyContainerBase * clone() const {
            return new holder(held);
        }

        T held;

    private:
        AnyContainer & operator=(const AnyContainer &);

    };

    AnyContainerBase * content;
};

template<class T> T * any_cast(Any & any) {
    check_nullptr(any.contents);
    if(!any->type() == typeid(T)) sthrow(InvalidTypeError,
            "Tried to assign an Any to an invalid type!");
    return static_cast<Any::AnyContainer<T> *>(any.content)->held;
}
SYLPH_END_NAMESPACE

#endif	/* ANY_H_ */

