/* 
 * File:   Serialisator.h
 * Author: frank
 *
 * Created on 26 maart 2009, 16:59
 */

#ifndef SERIALIZER_H_
#define	SERIALIZER_H_

#include "../Object.h"

SYLPH_START_NAMESPACE(Core)
template<class T> class Array;
template<class K,class V, class H> class Dictionary;
class String;
namespace Serialization {
    SYLPH_PUBLIC
    class _serkey;

    class Serializer : public Object {
    public:
        Serializer() {}
        virtual ~Serializer();

        virtual Serializer& operator<<(const unsigned int i) = 0;
        virtual Serializer& operator<<(const int i) = 0;
        virtual Serializer& operator<<(const unsigned long l) = 0;
        virtual Serializer& operator<<(const long l) = 0;
        virtual Serializer& operator<<(const float f) = 0;
        virtual Serializer& operator<<(const double d) = 0;
        virtual Serializer& operator<<(const bool b) = 0;
        template<class T>
        virtual Serializer& operator<<(const Array<T> & ar) = 0;
        virtual Serializer& operator<<(const String s) = 0;
        template<class K, class H, class V>
        virtual Serializer& operator<<(const Dictionary<K,H,V> & dict) = 0;
        virtual Serializer& operator<<(const _serkey & key) = 0;
    };
}
SYLPH_END_NAMESPACE(Core)

#endif	/* SERIALIZER_H_ */

