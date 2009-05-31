/* 
 * File:   InputStream.h
 * Author: frank
 *
 * Created on 27 april 2009, 17:39
 */

#ifndef INPUTSTREAM_H_
#define	INPUTSTREAM_H_


#include "../Core/Object.h"

SYLPH_BEGIN_NAMESPACE
SYLPH_PUBLIC

class InputStream : public virtual Object {
public:
    InputStream();
    InputStream(const InputStream& orig);
    virtual ~InputStream();
private:


};

SYLPH_END_NAMESPACE

#endif	/* INPUTSTREAM_H_ */

