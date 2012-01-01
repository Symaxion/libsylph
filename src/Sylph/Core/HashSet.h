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
 *  Created on: 15 sep. 2011
 */

#ifndef SYLPH_CORE_HASHSET_H_
#define SYLPH_CORE_HASHSET_H_

#include "Object.h"
#include "Iterator.h"
#include "Primitives.h"
#include "Hash.h"

SYLPH_BEGIN_NAMESPACE
template<class T, class H = Sylph::Hash<T> >
class HashSet {
    typedef H HashFunction;
    typedef HashSet<T,H> Self;
};

// TODO implement HashSet
// TODO make testcase for HashSet

SYLPH_END_NAMESPACE


#endif /* SYLPH_CORE_HASHSET_H_ */
