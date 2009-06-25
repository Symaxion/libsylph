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
#include "Primitives.h"
#include "Hashable.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
inline sint hash_internal(byte * b, std::size_t len) {
   suint hash = 0;
   suint x    = 0;
   suint i    = 0;

   for(i = 0; i < len; b++, i++)
   {
      hash = (hash << 4) + (*b);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}

template<class T>
inline sint Hash(T & t) {
    return hash_internal(*reinterpret_cast<byte*>(t), sizeof(T));
}

template<>
inline sint Hash<int>(int & i) {
    return i;
}

// 'Hashables' provide their own hasing method, usually it's based on this one
template<>
inline sint Hash<Hashable>(Hashable & h) {
    return h.hashCode();
}

SYLPH_END_NAMESPACE

#endif	/* HASH_H_ */

