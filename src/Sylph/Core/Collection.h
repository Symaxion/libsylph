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
 *  Created on: 3 jan. 2011
 */

#ifndef COLLECTION_H_
#define COLLECTION_H_

#include "Object.h"

SYLPH_BEGIN_NAMESPACE

class Collection : public virtual Object {

};

class OrderedCollection : public virtual Collection {

};

class RandomAccessCollection : public virtual OrderedCollection {

};

class ExpandableCollection : public virtual Collection {

};

class UniqueCollection : public virtual Collection {

};

SYLPH_END_NAMESPACE

#endif /* COLLECTION_H_ */
