#include "functions.h"
#include "../../src/Sylph/Core/Primitives.h"

namespace Concepts {
    /**
     * hash
     */
    template<class T>
    struct Hash : public Function<sint,T> {};

    /**
     * cryptographic hash
     */
    template<class T>
    struct CryptographicHash : public Hash<T> {};

    /**
     * random function
     */
    template<class T>
    struct RandomFunction : public Function<T> {};

}

