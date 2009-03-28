/* 
 * File:   Deserializer.h
 * Author: frank
 *
 * Created on 27 maart 2009, 16:27
 */

#ifndef DESERIALIZER_H_
#define	DESERIALIZER_H_

#include "../Object.h"

SYLPH_START_NAMESPACE(Core)
template<class T> class Array;
template<class K,class V, class H> class Dictionary;
class String;
namespace Serialization {
    SYLPH_PUBLIC
    class _serkey;

    class Deserializer : public Object {
    public:
        Deserializer() {}
        virtual ~Deserializer();

        virtual Deserializer& operator>>(const unsigned int i) = 0;
        virtual Deserializer& operator>>(const int i) = 0;
        virtual Deserializer& operator>>(const unsigned long l) = 0;
        virtual Deserializer& operator>>(const long l) = 0;
        virtual Deserializer& operator>>(const float f) = 0;
        virtual Deserializer& operator>>(const double d) = 0;
        virtual Deserializer& operator>>(const bool b) = 0;
        template<class T>
        virtual Deserializer& operator>>(const Array<T> & ar) = 0;
        virtual Deserializer& operator>>(const String s) = 0;
        template<class K, class H, class V>
        virtual Deserializer& operator>>(const Dictionary<K,H,V> & dict) = 0;
        virtual Deserializer& operator>>(const _serkey & key) = 0;
    };
}
SYLPH_END_NAMESPACE(Core)

#endif	/* DESERIALIZER_H_ */

