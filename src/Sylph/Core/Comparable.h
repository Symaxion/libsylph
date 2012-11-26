/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 * Created on 24 december 2008, 10:40
 */

#ifndef SYLPH_CORE_COMPARABLE_H_
#define	SYLPH_CORE_COMPARABLE_H_

#include "Object.h"

/**
 * @file Comparable.h
 * Include this file if you want your objects to be comparable with operator<
 * ,….
 * It defines operator!=,operator>,operator<=, and operator >= in terms of
 * operator== and operator<. Therefore, you'll only have to overload these in
 * order to make your objects comparable.
 */

SYLPH_BEGIN_NAMESPACE

#define S_CMP_NE_2_UNI(Left, Right) \
inline bool operator!=(Left lhs, Right rhs) {\
    return !(lhs == rhs); \
}

#define S_CMP_NE_2(Left, Right) \
S_CMP_NE_2_UNI(Left,Right) \
S_CMP_NE_2_UNI(Right, Left)

#define S_CMP_NE(Class) \
S_CMP_NE_2_UNI(Class, Class)

#define S_CMP_SEQ_2_UNI(Left, Right) \
S_CMP_NE_2_UNI(Left,Right) \
inline bool operator>=(Left lhs,Right rhs) {\
    return !(lhs < rhs); \
} \
inline bool operator>(Left lhs, Right rhs) {\
    return !(lhs < rhs) && !(lhs == rhs); \
} \
inline bool operator<=(Left lhs, Right rhs) {\
    return (lhs < rhs) || (lhs == rhs); \
}

#define S_CMP_SEQ_2(Left, Right) \
S_CMP_SEQ_2_UNI(Left,Right) \
S_CMP_SEQ_2_UNI(Right, Left)

#define S_CMP_SEQ(Class) \
S_CMP_SEQ_2_UNI(Class, Class)

        
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_COMPARABLE_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
