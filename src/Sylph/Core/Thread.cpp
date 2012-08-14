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
 */

#include "Thread.h"

SYLPH_BEGIN_NAMESPACE

HashMap<Thread,String> Thread::implString;
HashMap<String,Thread> Thread::stringImpl;
HashMap<Thread,bool> Thread::implJoinable;
idx_t Thread::threadCt = 1;

void Thread::addStringImpl(Thread impl, String s) {
    implString[impl] = s;
    stringImpl[s] = impl;
    implJoinable[impl] = true;
}
void Thread::removeString(String s) {
    Thread toRemove = stringImpl[s];
    stringImpl.remove(s);
    implString.remove(toRemove);
    implJoinable.remove(toRemove);
}
void Thread::removeImpl(Thread i) {
    String toRemove = implString[i];
    stringImpl.remove(toRemove);
    implString.remove(i);
    implJoinable.remove(i);
}

Thread::Thread(const Thread& other) : threadImpl(other.threadImpl) {

}

Thread::~Thread() {

}

void Thread::join() {
    pthread_join(threadImpl,null);
}
void Thread::detach() {
    pthread_detach(threadImpl);
    Thread::implJoinable[*this] = false;
}
bool Thread::joinable() const {
    return Thread::implJoinable[*this];
    return true;
}

void Thread::exit(int i) {
    Thread::removeImpl(pthread_self());
    pthread_exit(static_cast<void*>(&i));
}
Thread Thread::current() {
    return Thread(pthread_self());
}

String Thread::name() const {
    return implString[threadImpl];
}
void Thread::setName(String name) {
    addStringImpl(threadImpl,name);
}

Thread Thread::forName(String name) {
    return stringImpl[name];
}

void Thread::sleep(long millis, int nanos) {
    time_t seconds = millis / 1000;
    long nns = (millis-seconds) * 1000000 + nanos;
    timespec ts{seconds,nns};
    nanosleep(&ts,null);
}
void Thread::yield() {
    sched_yield();
}

Thread::Thread(pthread_t _impl) : threadImpl(_impl){
}

bool Thread::operator==(const Thread& other) const {
    return pthread_equal(threadImpl,other.threadImpl);
}
SYLPH_END_NAMESPACE

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
