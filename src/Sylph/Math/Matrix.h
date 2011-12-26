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

#ifndef SYLPH_MATH_MATRIX_H_
#define SYLPH_MATH_MATRIX_H_

#include "internal_base.h"

SYLPH_BEGIN_MATHNS
    template<class T, size_t H, size_t W>
    class MatrixBase : public Object {
    };

    template<class T, size_t D>
    class SquareMatrixBase : public MatrixBase<T,D,D> {
    };

    template<class T, size_t H, size_t W = H>
    class Matrix : public MatrixBase<T, H, W> {
    };

    template<class T, size_t D>
    class Matrix<T,D,D> : public SquareMatrixBase<T,2> {
    };

    template<class T>
    class Matrix<T,1,1> : public SquareMatrixBase<T,1> {
    };

    template<class T>
    class Matrix<T,2,2> : public SquareMatrixBase<T,2> {
    };

    template<class T>
    class Matrix<T,3,3> : public SquareMatrixBase<T,3> {
    };

    typedef Matrix<float,2> Matrix2f;
    typedef Matrix<float,3> Matrix3f;
    typedef Matrix<float,4> Matrix4f;
    typedef Matrix<double,2> Matrix2d;
    typedef Matrix<double,3> Matrix3d;
    typedef Matrix<double,4> Matrix4d;

    typedef Matrix2f mat2f;
    typedef Matrix3f mat3f;
    typedef Matrix4f mat4f;
    typedef Matrix2d mat2d;
    typedef Matrix3d mat3d;
    typedef Matrix4d mat4d;
SYLPH_END_MATHNS

#endif /* SYLPH_MATH_MATRIX_H_ */
