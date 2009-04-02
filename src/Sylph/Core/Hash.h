/* 
 * File:   Hash.h
 * Author: frank
 *
 * Created on 4 maart 2009, 12:45
 */

#ifndef HASH_H_
#define	HASH_H_

#include "Object.h"


SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC
template<class T>
class Hash : public std::unary_function<int,T &> {
    inline int operator()(T & t);
};

template<>
class Hash<int> {
    inline int operator()(int & i);
};

template<>
class Hash<float> {
    inline int operator()(float & f);
};

template<>
class Hash<double> {
    inline int operator()(double & d);
};

template<>
class Hash<char *> {
    inline int operator()(char * & c);
};

template<typename T>
class Hash<T *> {
    inline int operator()(T * & t);
};


SYLPH_END_NAMESPACE

#endif	/* HASH_H_ */

