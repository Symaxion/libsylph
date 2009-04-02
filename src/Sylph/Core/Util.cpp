#include "Util.h"

namespace Sylph {
    namespace Core {

        template<typename T>
        inline void carraycopy(T src[], std::size_t srcPos, T dest[],
                std::size_t destPos, std::size_t length) throw (Exception) {

            std::size_t srcSize = carraysize(src);
            std::size_t destSize = carraysize(dest);
            if (srcPos + length > srcSize) sthrow(ArrayException, "Source array too short");
            if (destPos + length > destSize) sthrow(ArrayException, "Dest array too short");

            for (int i = 0; i < length; i++) {
                dest[destPos + i] = src[srcPos + i];
            }
        }

        template<typename T>
        inline void arraycopy(Array<T> & src, std::size_t srcPos, Array<T> dest,
                std::size_t destPos, std::size_t length) throw (Exception) {

            std::size_t srcSize = src.length();
            std::size_t destSize = dest.length();
            if (srcPos + length > srcSize) sthrow(ArrayException, "Source array too short");
            if (destPos + length > destSize) sthrow(ArrayException, "Dest array too short");

            for (int i = 0; i < length; i++) {
                dest[destPos + i] = src[srcPos + i];
            }
        }

        template <typename T, std::size_t N>
        std::size_t carraysize(T(&)[N]) {
            return N;
        }

    }
}
