#include "Hash.h"
#include "Exception.h"

SYLPH_START_NAMESPACE(Core)
        
union float_union {
    float f;
    char c[sizeof float];
};

union double_union {
    double d;
    char c[sizeof double];
};

inline int Hash::operator()(T & t) {
    return t.hashCode();
}

inline int Hash<int>::operator()(int & i) {
    return i; // easy
}

inline int Hash<float>::operator()(float & f) {
    float_union fu;
    fu.f = f;
    Hash h<char *>;
    return h(fu.c); // stop thinking. right now.
}

inline int Hash<double>::operator()(double & d) {
    double_union du;
    du.d = d;
    Hash h<char *>;
    return h(du.c); // better than above. I recommend using doubles instead of floats
}

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


SYLPH_END_NAMESPACE(Core)
