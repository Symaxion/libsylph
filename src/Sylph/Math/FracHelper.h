/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 */

#ifndef SYLPH_MATH_FRACHELPER_H_
#define SYLPH_MATH_FRACHELPER_H_

#include "internal_base.h"

SYLPH_BEGIN_MATHNS
#define S_OVER / FracHelper() /
#if !defined(SYLPH_NO_KEYWORDS) && !defined(SYLPH_NO_OVER)
#define over S_OVER
#endif

    class FracHelper {
    };

    class FracHelper2 {
    public:
        FracHelper2(sint _i) : i(_i) {}
        sint i;
    };

    FracHelper2 operator/(sint i, FracHelper) {
        return FracHelper2(i);
    }

    frac operator/(FracHelper2 h, suint i) {
        return frac(h.i,i);
    }

SYLPH_END_MATHNS

#endif /* SYLPH_MATH_FRACHELPER_H_ */
