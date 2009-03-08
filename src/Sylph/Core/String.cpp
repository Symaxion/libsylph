/*
 * String.cpp
 *
 *  Created on: 26-nov-2008
 *      Author: SeySayux
 */

#include "String.h"

namespace Sylph {
namespace Core {
inline String::String() : std::string() {

}
String::String(const String & orig) : std::string(orig) {

}
String::String(const std::allocator<char> & alloc) : std::string(alloc) {

}
String::String(const String & str, size_type pos,
   size_type n) : std::string(str, pos, n) {

}
String::String(const String & str, size_type pos,
   size_type n, const std::allocator<char> & a) : std::string(str,pos,n,a) {

   }
String::String(const char * s, const std::allocator<char> & a) : std::string(s,a) {

}
String::String(size_type n, char c, const std::allocator<char> & a) : std::string(n,c,a) {

}
template<class InputIterator>
   String::String(InputIterator beg, InputIterator end,
	     const std::allocator<char> & a) : std::string(beg,end,a) {

}
String::~String() {

}
}
}
