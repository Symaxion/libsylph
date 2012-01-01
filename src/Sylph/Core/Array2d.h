/*
 * LibSylph Class Library
 * Copyright (C) 2012 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 12 april 2010, 13:09
 */

#ifndef ARRAY2D_H_
#define	ARRAY2D_H_

#include "Object.h"
#include "Array.h"

SYLPH_BEGIN_NAMESPACE

/**
 * Array2d is a two-dimensional array. Unlike a traditional C-style or even
 * LibSylph-style (i.e. <code>Array<Array<T>></code>), it is backed only by a single
 * array and therefore gives faster access to the data. Example:
 * <pre>
 * // create a 3x4 array
 * Array2d<int>(3,4) myarr; // this will initialize everything to zero
 *
 * // access element at 1,2
 * myarr(1,2) = 5;
 *
 * // access element beyond scope
 * try {
 *     myarr(3,4) = 2;
 * catch(...) {
 *      thisapp->fail("Oops! couldnt do that!");
 * }
 * </pre>
 *
 * Unline a one-dimensional Array, this array is not reference-counted and
 * should be passed by reference to functions.
 * @tplreqs T CopyConstructible, DefaultConstructible, Assignable
 */
template<class T>
class Array2d : public Object {
public:
    /**
     * Creates a new two-dimensional array with given with and height. The
     * elements will be initialised to zero or the default constructor of the
     * object.
     * @param _width The width of the array.
     * @param _height The height of the array.
     */
    explicit Array2d(size_t width, size_t height) : _width(width), _height(height),
            contents(width*height) {

    }

    /**
     * Creates a copy from given existing array. All data will be copied into
     * the new array, which will be completely independant of the old one.
     * The height and width are indentical to those of the old array.
     * @param other Another array whose contents to copy.
     */
    Array2d(const Array2d& other) : _width(other._width), _height(other._height),
            contents(other.contents.copy()) {

    }

    /**
     * Returns the width of this two-dimensional array.
     * @return The width of this array.
     */
    size_t width() const {
        return _width;
    }

    /**
     * Returns the height of this two-dimensional array.
     * @return The height of this array.
     */
    size_t height() const {
        return _height;
    }

    /**
     * Returns the entry at <i>(<code>width</code>,<code>height</code>)</i>.
     * @param width The first index
     * @param height The second index
     * @return A reference to the element at this position.
     * @throw ArrayException if the indices are out of bounds.
     */
    T& operator()(idx_t width, idx_t height) throw(ArrayException) {
        try {
            return contents[height*_width + width];
        } straced;
    }

    /**
     * Returns the entry at <i>(<code>width</code>,<code>height</code>)</i>.
     * This is a const version of the access operator.
     * @param width The first index
     * @param height The second index
     * @return A reference to the element at this position.
     * @throw ArrayException if the indices are out of bounds.
     */
    const T& operator()(idx_t width, idx_t height) throw(ArrayException) const {
        try {
            return contents[height*_width + width];
        } straced;
    }
private:
    size_t _width;
    size_t _height;
    Array<T> contents;
};
SYLPH_END_NAMESPACE

#endif	/* ARRAY2D_H_ */

