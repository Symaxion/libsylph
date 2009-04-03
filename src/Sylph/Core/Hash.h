/* 
 * File:   Hash.h
 * Author: frank
 *
 * Created on 4 maart 2009, 12:45
 */

#ifndef HASH_H_
#define	HASH_H_

#include "Object.h"
#include "Exception.h"

#include <functional>

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
template<class T>
class Hash : public std::unary_function<int,T &> {
    inline int operator()(T & t);
};

template<>
class Hash<int> {
    inline int operator()(int & i);
};

template<>
class Hash<float> {
    inline int operator()(float & f);
};

template<>
class Hash<double> {
    inline int operator()(double & d);
};

template<>
class Hash<char *> {
    inline int operator()(char * & c);
};

template<typename T>
class Hash<T *> {
    inline int operator()(T * & t);
};




union float_union {
    float f;
    char c[sizeof(float)];
};

union double_union {
    double d;
    char c[sizeof(double)];
};

template<class T>
inline int Hash<T>::operator()(T & t) {
    return t.hashCode();
}

template<>
inline int Hash<int>::operator()(int & i) {
    return i; // easy
}

template<>
inline int Hash<float>::operator()(float & f) {
    float_union fu;
    fu.f = f;
    Hash h<char *>;
    return h(fu.c); // stop thinking. right now.
}

template<>
inline int Hash<double>::operator()(double & d) {
    double_union du;
    du.d = d;
    Hash h<char *>;
    return h(du.c); // better than above. I recommend using doubles instead of floats
}

template<>
inline int Hash<char *>::operator()(char * & c) {
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;
   std::size_t len = strlen(c);

   for(i = 0; i < len; c++, i++)
   {
      hash = (hash << 4) + (*c);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}

template<typename T>
inline int Hash<T *>::operator()(T * & t) {
    Hash <T> h;
    check_nullptr(t);
    return h(*t);
}




SYLPH_END_NAMESPACE

#endif	/* HASH_H_ */

