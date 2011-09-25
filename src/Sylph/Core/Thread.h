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

#include <functional>

#ifdef SYLPH_OS_WINDOWS
#else
#include <pthread.h>
#include <sched.h>
#include <time.h>
#endif

SYLPH_BEGIN_NAMESPACE

class Thread : public virtual Object {
    template<class Callable>
    friend void* callCallable(void*);
private:
#ifdef SYLPH_OS_WINDOWS
#else
    static HashMap<Thread,String> implString;
    static HashMap<String,Thread> stringImpl;
    static HashMap<Thread,bool> implJoinable;

    static void addStringImpl(Thread i, String s);
    static void removeString(String s);
    static void removeImpl(Thread i);

    static idx_t threadCt;
#endif
public:
    template<class Callable>
    explicit Thread(Callable c) {
#ifdef SYLPH_OS_WINDOWS
#else
        pthread_create(&threadImpl,null,Sylph::callCallable<Callable>,(void*)(c));
        Thread::addStringImpl(threadImpl,String(threadCt++));
#endif
    }
    template<class Callable, class... Args>
    explicit Thread(Callable c, Args&... a) {
#ifdef SYLPH_OS_WINDOWS
#else
        auto f = std::bind<void*>(c, a...);
        pthread_create(&threadImpl,null,f,null);
        Thread::addStringImpl(threadImpl,String(threadCt++));
        Thread::implJoinable[*this] = true;
#endif
    }

    Thread(const Thread& other);
    virtual ~Thread();

    void join();
    void detach();
    bool joinable() const;

    static void exit(int i = 0);
    static Thread current();

    String name() const;
    void setName(String name);
    static Thread forName(String name);

    static void sleep(long millis = 0, int nanos = 0);
    static void yield();

    bool operator==(const Thread& other) const;

private:
#ifdef SYLPH_OS_WINDOWS
#else
    pthread_t threadImpl;

    Thread(pthread_t impl);
#endif
};

HashMap<Thread,String> Thread::implString;
HashMap<String,Thread> Thread::stringImpl;
HashMap<Thread,bool> Thread::implJoinable;
idx_t Thread::threadCt = 1;

template<class Callable>
void* callCallable(void* c) {
#ifdef SYLPH_OS_WINDOWS
#else
    Callable c2 = (Callable)(c);
    c2();
    Thread::removeImpl(Thread::current());
    pthread_exit(null);
#endif
}

SYLPH_END_NAMESPACE


#endif /* THREAD_H_ */
