/* 
 * File:   Key.h
 * Author: frank
 *
 * Created on 27 maart 2009, 16:32
 */

#ifndef KEY_H_
#define	KEY_H_

#define S_SERIALIZABLE(__s) \
     static ::Sylph::Core::Serialization::Key __sylph_serkey=__s
#define S_SERIALIZATION_KEY(_class) _class::__sylph_serkey
#define S_DECL_SERIALIZABLE(_class) \
       ::Sylph::Core::Serialization::Key _class::__sylph_serkey;

#include "../Object.h"

SYLPH_START_NAMESPACE(Core)
class String;
namespace Serialization {
    
    class Key : public Object {
    public:
        Key(const String name) : _name(name) {}
        Key(const Key & orig) : _name(orig._name) {}
        virtual ~Key() {}
        Key & operator=(const String name) { _name = name; return *this; }
        inline const String name() const { return _name; }
    private:
        String _name;
    };
}
SYLPH_END_NAMESPACE(Core)

#endif	/* KEY_H_ */

