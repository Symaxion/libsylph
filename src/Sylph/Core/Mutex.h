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
 *  Created on: 9 dec. 2010
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include "Object.h"
#ifdef SYLPH_OS_WINDOWS
#else
#include <pthread.h>
#endif

SYLPH_BEGIN_NAMESPACE

class Mutex : public virtual Object {
public:
    Mutex();
    virtual ~Mutex();

    void lock();
    bool tryLock();
    void unlock();

    void wait();
    void notify();
    void notifyAll();
protected:
#ifdef SYLPH_OS_WINDOWS
#else
    pthread_mutex_t* impl;
    pthread_cond_t* cond;
#endif
};

class RecursiveMutex : public virtual Object {
public:
    RecursiveMutex();
    virtual ~RecursiveMutex();

    void lock();
    bool tryLock();
    void unlock();
protected:
#ifdef SYLPH_OS_WINDOWS
#else
    pthread_mutex_t* impl;
    pthread_mutexattr_t* attr;
    pthread_cond_t* cond;

    void wait();
    void notify();
    void notifyAll();
#endif
};

SYLPH_END_NAMESPACE

#endif /* MUTEX_H_ */
