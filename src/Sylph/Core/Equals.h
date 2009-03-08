/* 
 * File:   Equals.h
 * Author: frank
 *
 * Created on 6 maart 2009, 17:15
 */

#ifndef EQUALS_H_
#define	EQUALS_H_

#include "Object.h"
SYLPH_START_NAMESPACE(Core)
SYLPH_PUBLIC
template<class T>
inline bool Equals(T& t1, T& t2);

template<>
inline bool Equals(char * c1, char * c2);

template<class T>
inline bool Equals(T*& t1, T*& t2);
SYLPH_END_NAMESPACE(Core)

#endif	/* EQUALS_H_ */

