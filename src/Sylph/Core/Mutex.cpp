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
 */

#include "Mutex.h"

SYLPH_BEGIN_NAMESPACE

Mutex::Mutex() {
    pthread_mutex_init(impl,null);
    pthread_cond_init(cond,null);
}
Mutex::~Mutex() {
    pthread_mutex_destroy(impl);
    pthread_cond_destroy(cond);
}

RecursiveMutex::RecursiveMutex() {
    pthread_mutexattr_init(attr);
    pthread_mutexattr_settype(attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(impl,null);
    pthread_cond_init(cond,null);
}
RecursiveMutex::~RecursiveMutex() {
    pthread_mutex_destroy(impl);
    pthread_mutexattr_destroy(attr);
    pthread_cond_destroy(cond);
}

#define MUTEX_IMPL(MUTEX) \
void MUTEX::lock() { \
    pthread_mutex_lock(impl); \
} \
bool MUTEX::tryLock() { \
    return pthread_mutex_unlock(impl) != 0; \
} \
void MUTEX::unlock() { \
    pthread_mutex_unlock(impl); \
} \
void MUTEX::wait() { \
    pthread_cond_wait(cond,impl); \
} \
void MUTEX::notify() { \
    pthread_cond_signal(cond); \
} \
void MUTEX::notifyAll() { \
    pthread_cond_broadcast(cond); \
}

MUTEX_IMPL(Mutex)
MUTEX_IMPL(RecursiveMutex)

#undef MUTEX_IMPL

SYLPH_END_NAMESPACE
