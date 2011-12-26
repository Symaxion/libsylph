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

#ifndef SYLPH_MATH_PLANE_H_
#define SYLPH_MATH_PLANE_H_

#include "internal_base.h"
#include "Vector.h"

SYLPH_BEGIN_MATHNS
    template<class Number>
    class Plane3 {
    public:
        Plane3(Vector3<Number> normal, 
                Vector3<Number> position = Vector3<Number>::zero);
        Plane3(Vector3<Number> a, Vector3<Number> b, Vector3<Number> c);
        
        static Plane<Number> fromDirection(Vector3<Number> pos,
                Vector3<Number> a, Vector3<Number> b) {
            // TODO
        }
    private:
        Number x, y, z, t;
    };

    typedef Plane3<float> Plane3f;
    typedef Plane3<double> Plane3d;
SYLPH_END_MATHNS

#endif /* SYLPH_MATE_PLANE_H_ */
