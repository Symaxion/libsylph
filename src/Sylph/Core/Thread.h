/*
 * LibSylph Class Library
 * Copyright (C) 2010 Frank "SeySayux" Erens <seysayux@gmail.com>
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

#ifndef THREAD_H_
#define THREAD_H_

#include "Object.h"
#include "String.h"
#include "HashMap.h"

#include "../OS/OS.h"

#ifdef SYLPH_OS_WINDOWS
#else
#include <pthread.h>
#include <sched.h>
#include <time.h>
#endif

#define dispatch
#define dispatch_if

SYLPH_BEGIN_NAMESPACE

class Thread : public virtual Object {
    template<class Callable>
    friend void* callCallable(Callable c);
private:
#ifdef SYLPH_OS_WINDOWS
#else
    static HashMap<pthread_t*,String> implString;
    static HashMap<String,pthread_t*> stringImpl;

    static void addStringImpl(pthread_t* i, String s);
    static void removeString(String s);
    static void removeImpl(pthread_t* i);
#endif
public:
    template<class Callable>
    Thread(Callable c);
    template<class Callable, class... Args>
    Thread(Callable c, Args... a);
    virtual ~Thread();

    void join();
    void detach();
    bool joinable() const;

    static void exit();
    static Thread current();

    String name() const;
    void setName(String name);

    static void sleep(long millis = 0, int nanos = 0);
    static void yield();

    bool operator==(const Thread& other) const;

private:
#ifdef SYLPH_OS_WINDOWS
#else
    pthread_t* threadImpl;

    Thread(pthread* impl);
#endif
};

template<class Callable>
void* callCallable(Callable c);

SYLPH_END_NAMESPACE


#endif /* THREAD_H_ */
