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
 *  Created on: 14 aug. 2011
 */

#ifndef SYLPH_CORE_FUNCTION_H_
#define SYLPH_CORE_FUNCTION_H_

#include "Object.h"
#include <functional>

SYLPH_BEGIN_NAMESPACE
// Function
using std::function;

// Noop
template<class... T>
void noop(T...) {}

// Map
template<class T, class R>class MappedFunction {
public:
    MappedFunction(function<R(T)> _func) : func(_func) {}

    template<class C<class>>
    auto operator()(C<T>& list) -> C<R> {
        C<R> toReturn;
        sforeach(T& t, list) {
            toReturn.add(func(t));
        }
        return toReturn;
    }
private:
    function<R(T)> func;
}

template<class T, class R>
MappedFunction<T,R> map(function<R(T)> func) {
    return MappedFunction<T,R>(func);
}

// Chain
template<class T, class U, class... V>
function<T(V...)> chain(function<T(U)> a, function<U(V...)> b) {
    return [=](V... v) -> T { return a(b(v)); }
}

// Call
template<class C, class R, class... P>
function<R(C&)> call(R(C::*)(P...) f, P... p) {
    return [=](C& c) -> R { return (c.*f)(p); }
}
SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_FUNCTION_H_ */
