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
 *  Created on: 14 aug. 2011
 */

#ifndef SYLPH_CORE_FUNCTION_H_
#define SYLPH_CORE_FUNCTION_H_

#include "Object.h"
#include "Array.h"
#include "Foreach.h"

#include <functional>
#include <type_traits>

SYLPH_BEGIN_NAMESPACE
// Function
using std::function;

// Bind
using std::bind;

namespace Placeholders {
    using namespace std::placeholders;
}

#if !defined(SYLPH_NO_KEYWORDS) && !defined(SYLPH_NO_PLACEHOLDER_NS)
namespace P {
    using namespace std::placeholders;
}
#endif

// Noop
template<class... T>
void noop(T...) {}

// Iden
template<class T>
T& iden(T& t) {
    return t;
}

// Cons
template<class T, class... P>
function<T(P...)> cons(T& t) {
    return [=](P...) -> T { return t; };
}

// Car
template<class T1, class T2, class... P>
T1& car(T1& t1, T2& t2, P&... p) {
    return t1;
}

// Cdr
template<class T1, class T2, class... P>
T2& cdr(T1& t1, T2& t2,  P&... p) {
    return t2;
}

// Constify
template<class T>
const T& constify(const T& t) {
    return t;
}

template<class T>
const T& constipate(const T& t) {
    return t;
}

// Map
template<class T, class R>
class MappedFunction {
    typedef typename std::remove_reference<T>::type Tp;
    typedef typename std::remove_reference<R>::type Rp;
public:
    MappedFunction(function<R(T)> _func) : func(_func) {}

    template<template<class> class C >
    auto operator()(C<Tp>& list) -> C<Rp> {
        C<Rp> toReturn;
        sforeach(T& t, list) {
            toReturn.add(func(t));
        }
        return toReturn;
    }

//     Array<Rp> operator()(Array<Tp> list) {
//         Array<Rp> toReturn(list.length);
//         for(idx_t i = 0; i < list.length;++i) {
//             toReturn[i] = func(list[i]);
//         }
//         return toReturn;
//     }
private:
    function<R(T)> func;
};

template<class T, class R>
MappedFunction<T,R> map(function<R(T)> func) {
    return MappedFunction<T,R>(func);
}

template<class T, class R>
MappedFunction<T,R> map(R(*func)(T)) {
    return MappedFunction<T,R>(std::function<R(T)>(func));
}

// Chain
template<class T, class U, class... V>
function<T(V...)> chain(function<T(U)> a, function<U(V...)> b) {
    return [=](V... v) -> T { return a(b(v...)); };
}

template<class T, class U, class... V>
function<T(V...)> chain(T(*a)(U), function<U(V...)> b) {
    return [=](V... v) -> T { return a(b(v...)); };
}

template<class T, class U, class... V>
function<T(V...)> chain(function<T(U)> a, U(*b)(V...)) {
    return [=](V... v) -> T { return a(b(v...)); };
}

template<class T, class U, class... V>
function<T(V...)> chain(T(*a)(U), U(*b)(V...)) {
    return [=](V... v) -> T { return a(b(v...)); };
}

// Invoke
template<class C, class R, class... P>
function<R(C&)> invoke(R (C::*f)(P...), P&&... p) {
    return bind(f,Placeholders::_1,p...);
}

template<class C, class R, class... P>
function<R(C&)> invoke(R (C::*f)(P...) const, P&&... p) {
    return bind(f,Placeholders::_1,p...);
}

// Forany
template<template<class> class C, class T, class U>
bool forany(const C<T>& c, function<bool(U)> f) {
    sforeach(const T& t, c) {
        if(f(t)) return true;
    }
    return false;
}

template<template<class> class C, class T>
class ForanyHelper {
public:
    ForanyHelper(const C<T>& _c) : c(_c) {}

    template<class U>
    bool operator==(const U& u) const {
       sforeach(const T& t, c) {
           if(t == u) return true;
       }
       return false;
    }

    template<class U>
    bool operator!=(const U& u) const {
       sforeach(const T& t, c) {
           if(t != u) return true;
       }
       return false;
    }

    template<class U>
    bool operator<(const U& u) const {
       sforeach(const T& t, c) {
           if(t < u) return true;
       }
       return false;
    }

    template<class U>
    bool operator>(const U& u) const {
       sforeach(const T& t, c) {
           if(t > u) return true;
       }
       return false;
    }

    template<class U>
    bool operator<=(const U& u) const {
       sforeach(const T& t, c) {
           if(t <= u) return true;
       }
       return false;
    }

    template<class U>
    bool operator>=(const U& u) const {
       sforeach(const T& t, c) {
           if(t >= u) return true;
       }
       return false;
    }

    explicit operator bool() const {
        sforeach(const T& t, c) {
            if(t) return true;
        }
        return false;
    }
private:
    const C<T>& c;
};

template<template<class> class C, class T>
ForanyHelper<C,T> forany(const C<T>& c) {
    return ForanyHelper<C,T>(c);
}

// Forall
template<template<class> class C, class T, class U>
bool forall(const C<T>& c, function<bool(U)> f) {
    sforeach(const T& t, c) {
        if(!f(t)) return false;
    }
    return true;
}

template<template<class> class C, class T>
class ForallHelper {
public:
    ForallHelper(const C<T>& _c) : c(_c) {}

    template<class U>
    bool operator==(const U& u) const {
        sforeach(const T& t, c) {
            if(!(t == u)) return false;
        }
        return true;
    }

    template<class U>
    bool operator!=(const U& u) const {
        sforeach(const T& t, c) {
            if(!(t != u)) return false;
        }
        return true;
    }

    template<class U>
    bool operator<=(const U& u) const {
        sforeach(const T& t, c) {
            if(!(t <= u)) return false;
        }
        return true;
    }

    template<class U>
    bool operator>=(const U& u) const {
        sforeach(const T& t, c) {
            if(!(t >= u)) return false;
        }
        return true;
    }

    template<class U>
    bool operator<(const U& u) const {
        sforeach(const T& t, c) {
            if(!(t < u)) return false;
        }
        return true;
    }

    template<class U>
    bool operator>(const U& u) const {
        sforeach(const T& t, c) {
            if(!(t > u)) return false;
        }
        return true;
    }

    explicit operator bool() const {
        sforeach(const T& t, c) {
            if(!t) return false;
        }
        return true;
    }
private:
    const C<T>& c;
};

template<template<class> class C, class T>
ForallHelper<C,T> forall(const C<T>& c) {
    return ForallHelper<C,T>(c);
}

// Countpred

template<template<class> class C, class T, class U>
std::size_t countpred(const C<T>& c, function<bool(U)> f) {
    std::size_t toReturn = 0;
    sforeach(const T& t, c) {
            if(f(t)) toReturn++;
    }
    return toReturn;
}

template<template<class> class C, class T>
class CountpredHelper {
public:
    CountpredHelper(const C<T>& _c) : c(_c) {}

    template<class U>
    std::size_t operator==(const U& u) {
        std::size_t toReturn = 0;
        sforeach(const T& t, c) {
            if(t == u) toReturn++;
        }
        return toReturn;
    }

    template<class U>
    std::size_t operator!=(const U& u) {
        std::size_t toReturn = 0;
        sforeach(const T& t, c) {
            if(t != u) toReturn++;
        }
        return toReturn;
    }

    template<class U>
    std::size_t operator<=(const U& u) {
        std::size_t toReturn = 0;
        sforeach(const T& t, c) {
            if(t <= u) toReturn++;
        }
        return toReturn;
    }

    template<class U>
    std::size_t operator>=(const U& u) {
        std::size_t toReturn = 0;
        sforeach(const T& t, c) {
            if(t >= u) toReturn++;
        }
        return toReturn;
    }

    template<class U>
    std::size_t operator<(const U& u) {
        std::size_t toReturn = 0;
        sforeach(const T& t, c) {
            if(t < u) toReturn++;
        }
        return toReturn;
    }

    template<class U>
    std::size_t operator>(const U& u) {
        std::size_t toReturn = 0;
        sforeach(const T& t, c) {
            if(t > u) toReturn++;
        }
        return toReturn;
    }

    explicit operator std::size_t() {
        std::size_t toReturn = 0;
        sforeach(const T& t, c) {
            if(t) toReturn++;
        }
        return toReturn;
    }
private:
    const C<T>& c;
};

template<template<class> class C, class T>
CountpredHelper<C,T> countpred(const C<T>& c) {
    return CountpredHelper<C,T>(c);
}

// TODO: wait until GCC supports this or we have tuple unpacking.
/*template<class P, class... A>
function<bool(const P&)> andfn(function<bool(const P&)> f1,
        function<bool(const P&)> f2, A... a) {
    return [=](const P& p) -> bool {
        return andfn_impl(p,f1,f2,a...);
    };
}

template<class P, class... A>
bool andfn_impl(const P& p, function<bool(const P&)> f1,
        function<bool(const P&)> f2, A... a) {
    return f1(p) && andfn_impl(p,f2,a...);
}

template<class P>
bool andfn_impl(const P& p, function<bool(const P&)> f1) {
    return f1(p);
}*/


template<class P>
function<bool(const P&)> andfn(function<bool(const P&)> f1,
        function<bool(const P&)> f2) {
    return [=](const P& p) -> bool {
        return f1(p) && f2(p);
    };
}

template<class P>
function<bool(const P&)> orfn(function<bool(const P&)> f1,
        function<bool(const P&)> f2) {
    return [=](const P& p) -> bool {
        return f1(p) || f2(p);
    };
}

template<class P>
function<bool(const P&)> notfn(function<bool(const P&)> f1) {
    return [=](const P& p) -> bool {
        return !f1(p);
    };
}

template<class P, class T, class U>
function<bool(const P&)> eqfn(function<T(const P&)> f1,
        function<U(const P&)> f2) {
    return [=](const P& p) -> bool {
        return f1(p) == f2(p);
    };
}

template<class P, class T, class U>
function<bool(const P&)> nefn(function<T(const P&)> f1,
        function<U(const P&)> f2) {
    return [=](const P& p) -> bool {
        return f1(p) != f2(p);
    };
}

template<class P, class T, class U>
function<bool(const P&)> relfn(function<bool(const T&, const U&)> rel,
        function<T(const P&)> f1, function<U(const P&)> f2) {
    return [=](const P& p) -> bool {
        return rel(f1(p),f2(p));
    };
}

// Operator wrappers
namespace Op {
    // Binary operators

    template<class T, class U=T>
    auto com(T t, U u) -> decltype(t,u) {
        return t , u;
    }

    template<class T, class U=T>
    auto asg(T t, U u) -> decltype(t=u) {
        return t = u;
    }

    template<class T, class U=T>
    auto equ(T t, U u) -> decltype(t==u) {
        return t == u;
    }

    template<class T, class U=T>
    auto neq(T t, U u) -> decltype(t!=u) {
        return t != u;
    }

    template<class T, class U=T>
    auto grt(T t, U u) -> decltype(t>u) {
        return t > u;
    }

    template<class T, class U=T>
    auto lst(T t, U u) -> decltype(t<u) {
        return t < u;
    }

    template<class T, class U=T>
    auto gte(T t, U u) -> decltype(t>=u) {
        return t >= u;
    }

    template<class T, class U=T>
    auto lte(T t, U u) -> decltype(t<=u) {
        return t <= u;
    }

    template<class T, class U=T>
    auto add(T t, U u) -> decltype(t+u) {
        return t + u;
    }

    template<class T, class U=T>
    auto sub(T t, U u) -> decltype(t-u) {
        return t - u;
    }

    template<class T, class U=T>
    auto mul(T t, U u) -> decltype(t*u) {
        return t * u;
    }

    template<class T, class U=T>
    auto div(T t, U u) -> decltype(t/u) {
        return t / u;
    }

    template<class T, class U=T>
    auto mod(T t, U u) -> decltype(t%u) {
        return t % u;
    }

    template<class T, class U=T>
    auto ada(T t, U u) -> decltype(t+=u) {
        return t += u;
    }

    template<class T, class U=T>
    auto sua(T t, U u) -> decltype(t-=u) {
        return t -= u;
    }

    template<class T, class U=T>
    auto mua(T t, U u) -> decltype(t*=u) {
        return t *= u;
    }

    template<class T, class U=T>
    auto dia(T t, U u) -> decltype(t/=u) {
        return t /= u;
    }

    template<class T, class U=T>
    auto moa(T t, U u) -> decltype(t%=u) {
        return t %= u;
    }

    template<class T, class U=T>
    auto lan(T t, U u) -> decltype(t&&u) {
        return t && u;
    }

    template<class T, class U=T>
    auto lor(T t, U u) -> decltype(t||u) {
        return t || u;
    }

    template<class T, class U=T>
    auto ban(T t, U u) -> decltype(t&u) {
        return t & u;
    }

    template<class T, class U=T>
    auto bor(T t, U u) -> decltype(t|u) {
        return t | u;
    }

    template<class T, class U=T>
    auto bxr(T t, U u) -> decltype(t^u) {
        return t ^ u;
    }

    template<class T, class U=T>
    auto baa(T t, U u) -> decltype(t&=u) {
        return t &= u;
    }

    template<class T, class U=T>
    auto boa(T t, U u) -> decltype(t|=u) {
        return t |= u;
    }

    template<class T, class U=T>
    auto bxa(T t, U u) -> decltype(t^=u) {
        return t ^= u;
    }

    template<class T, class U=T>
    auto lsh(T t, U u) -> decltype(t<<u) {
        return t << u;
    }

    template<class T, class U=T>
    auto rsh(T t, U u) -> decltype(t>>u) {
        return t >> u;
    }

    template<class T, class U=T>
    auto lsa(T t, U u) -> decltype(t<<=u) {
        return t <<= u;
    }

    template<class T, class U=T>
    auto rsa(T t, U u) -> decltype(t>>=u) {
        return t >>= u;
    }

    template<class T, class U>
    auto idx(T t, U u) -> decltype(t[u]) {
        return t[u];
    }

    // Unary operators
    template<class T>
    auto inc(T t) -> decltype(++t) {
        return ++t;
    }

    template<class T>
    auto dec(T t) -> decltype(--t) {
        return --t;
    }

    template<class T>
    auto lnt(T t) -> decltype(!t) {
        return !t;
    }

    template<class T>
    auto bnt(T t) -> decltype(~t) {
        return ~t;
    }

    template<class T>
    auto der(T t) -> decltype(*t) {
        return *t;
    }

    template<class T>
    auto adr(T t) -> decltype(&t) {
        return &t;
    }

    template<class T>
    auto pos(T t) -> decltype(+t) {
        return +t;
    }

    template<class T>
    auto neg(T t) -> decltype(-t) {
        return -t;
    }

    template<class T>
    auto inp(T t) -> decltype(t++) {
        return t++;
    }

    template<class T>
    auto dep(T t) -> decltype(t--) {
        return t--;
    }

    // Special operators
    template<class T, class... U>
    auto call(T&& t, U&&... u) -> decltype(t(u...)) {
        return t(std::forward<U...>(u)...);
    }

    template<class T, class... U>
    T* crt(U&&... u) {
        return new T(std::forward<U...>(u)...);
    }

    template<class T>
    void dtr(T* t) {
        delete t;
    }

    // Casts

    template<class T, class U>
    T sca(U& u) {
        return static_cast<T>(u);
    }

    template<class T, class U>
    T dca(U& u) {
        return dynamic_cast<T>(u);
    }

    template<class T, class U>
    T cca(U& u) {
        return const_cast<T>(u);
    }

    template<class T, class U>
    T rca(U& u) {
        return reinterpret_cast<T>(u);
    }
}

// Call
using Op::call;
SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_FUNCTION_H_ */
