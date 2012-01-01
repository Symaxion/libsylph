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
 *  Created on: 5 nov. 2011
 */

#ifndef SYLPH_MATH_TRIGFUNCTIONS_H_
#define SYLPH_MATH_TRIGFUNCTIONS_H_

#include "internal_base.h"
#include "Angle.h"

SYLPH_BEGIN_MATHNS
inline anglef acos(float a);
inline angled acos(double a);

inline anglef asin(float a);
inline angled asin(double a);

inline anglef atan(float a);
inline angled atan(double a);

inline anglef atan2(float a, float b) {
    return ::atan2f(a,b);
}

inline angled atan2(double a, double b) {
    return ::atan2(a,b);
}

inline float cos(anglef a);
inline double cos(angled a);

inline float cot(anglef a);
inline double cot(angled a);

inline float csc(anglef a);
inline double csc(angled a);

inline float sec(anglef a);
inline double sec(angled a);

inline float sin(anglef a);
inline double sin(angled a);

inline float tan(anglef a);
inline double tan(angled a);

float fastsin(anglef);
double fastsin(angled);

inline float fastcos(anglef a) {
    return fastsin(anglef(a + PI/2));
}

inline double fastcos(angled a) {
    return fastsin(angled(a + PI/2));
}

inline float fastcot(anglef a) {
    return fastcos(a) / fastsin(a);
}

inline double fastcot(angled a) {
    return fastcos(a) / fastsin(a);
}

inline float fastcsc(anglef a) {
    return 1 / fastsin(a);
}

inline double fastcsc(angled a) {
    return 1 / fastsin(a);
}

inline float fastsec(anglef a) {
    return 1 / fastcos(a);
}

inline double fastsec(angled a) {
    return 1 / fastcos(a);
}

inline float fasttan(anglef a) {
    return fastsin(a) / fastcos(a);
}

inline double fasttan(angled a) {
    return fastsin(a) / fastcos(a);
}
SYLPH_END_MATHNS


#endif /* SYLPH_MATH_TRIGFUNCTIONS_H_ */
