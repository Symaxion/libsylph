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

#include <typeinfo>

SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
class Any : public Object {
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

template<class T> T & any_cast(Any & any) {
    check_nullptr(any.contents);
    if(!any->type() == typeid(T)) sthrow(InvalidTypeError,
            "Tried to assign an Any to an invalid type!");
    return static_cast<Any::AnyContainer<T> *>(any.content)->held
}
SYLPH_END_NAMESPACE(Core)

#endif	/* ANY_H_ */

