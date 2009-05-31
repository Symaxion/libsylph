#include "Array.h"
#include "String.h"

/*< rev Object-1
 *  rev Iterable-1
 *  rev Exception-1
 *  rev String-1
 *  rev Iterator-1
 *  rev Hashable-1
 *  rev Array-1
 *  rev ArrayIterator-1
 >*/

SYLPH_BEGIN_NAMESPACE

template class Array<byte>;
template class Array<sint>;
template class Array<suint>;
template class Array<slong>;
template class Array<sulong>;
template class Array<bool>;

template class Array<String>;

SYLPH_END_NAMESPACE
