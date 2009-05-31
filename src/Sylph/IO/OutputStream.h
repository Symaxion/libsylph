/* 
 * File:   OutputStream.h
 * Author: frank
 *
 * Created on 27 april 2009, 17:41
 */

#ifndef OUTPUTSTREAM_H_
#define	OUTPUTSTREAM_H_


#include "../Core/Object.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class OutputStream : public virtual Object {
public:
    OutputStream();
    OutputStream(const OutputStream& orig);
    virtual ~OutputStream();
private:


};

SYLPH_END_NAMESPACE

#endif	/* OUTPUTSTREAM_H_ */

