/* 
 * File:   Util.h
 * Author: frank
 *
 * Created on 9 december 2008, 15:34
 */

#ifndef UTIL_H_
#define	UTIL_H_

#include "Object.h" // macros
#include "Exception.h"
#include "Array.h"

SYLPH_START_NAMESPACE(Core)
        SYLPH_PUBLIC

        template<typename T>
        inline void carraycopy(T src[], std::size_t srcPos, T dest[],
                std::size_t destPos, std::size_t length) throw(Exception);
        template<typename T>
        inline void arraycopy(Array<T> & src, std::size_t srcPos, Array<T> & dest,
                std::size_t destPos, std::size_t length) throw(Exception);

        template<typename T>
        inline std::size_t carraysize(T array[]);

SYLPH_END_NAMESPACE(Core)

#endif	/* UTIL_H_ */

