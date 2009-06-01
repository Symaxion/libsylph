/* 
 * File:   vector.cpp
 * Author: frank
 * 
 * Created on 6 december 2008, 12:07
 */

#include "Vector.h"

SYLPH_BEGIN_NAMESPACE
template class Vector<byte>;
template class Vector<sint>;
template class Vector<suint>;
template class Vector<slong>;
template class Vector<sulong>;
template class Vector<bool>;

template class Vector<String>;
SYLPH_END_NAMESPACE
