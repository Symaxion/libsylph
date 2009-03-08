#include "Equals.h"

#include "Util.h"

#include <string.h>

SYLPH_START_NAMESPACE(Core)
template<class T>
inline bool Equals(T& t1, T& t2) {
    return t1 == t2;
}

template<>
inline bool Equals(char * c1, char * c2) {
    return strncmp(c1, c2, strlen(c1)) == 0;
}

template<class T>
inline bool Equals(T*& t1, T*& t2) {
    return *(t1) == *(t2);

}
SYLPH_END_NAMESPACE(Core)
