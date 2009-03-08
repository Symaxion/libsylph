/*
 * String.h
 *
 *  Created on: 26-nov-2008
 *      Author: frank
 */

#ifndef STRING_H_
#define STRING_H_

#include "Object.h"

#include <string>

namespace Sylph {
namespace Core {
	class String : public Object, public std::string {
	public:
		inline String();
		String(const String & orig);
		String(const std::string & stlstring);
		String(const std::allocator<char> & alloc);
		String(const String & str, size_type pos,
		   size_type n = npos);
		String(const String & str, size_type pos,
		   size_type n, const std::allocator<char> & a);
	    String(const char * s, const std::allocator<char> & a = std::allocator<char>());
	    String(size_type n, char c, const std::allocator<char> & a = std::allocator<char>());
	    template<class InputIterator>
	        String(InputIterator beg, InputIterator end,
			     const std::allocator<char> & a = std::allocator<char>());
		virtual ~String();
	private:
		//
	};
}
}

#endif /* STRING_H_ */
