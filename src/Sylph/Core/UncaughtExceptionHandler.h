/* 
 * File:   UncaughtExceptionHandler.h
 * Author: frank
 *
 * Created on 12 februari 2009, 19:21
 */

#ifndef _UNCAUGHTEXCEPTIONHANDLER_H
#define	_UNCAUGHTEXCEPTIONHANDLER_H

#include "Object.h"
#include "Exception.h"
#include "Application.h"

SYLPH_BEGIN_NAMESPACE

SYLPH_PUBLIC

class UncaughtExceptionHandler : public Object {
public:
    UncaughtExceptionHandler() {}
    virtual ~UncaughtExceptionHandler() {}
    virtual void handle(const Exception & ex) const = 0;
public:
#ifdef SYLPH_DEBUG
    static UncaughtExceptionHandler * handler = new DebugUncaughtExceptionHandler;
#else
    static UncaughtExceptionHandler * handler = new DefaultUncaughtExceptionHandler;
#endif
};

static UncaughtExceptionHandler UncaughtExceptionHandler::handler;

class DefaultUncaughtExceptionHandler : public UncaughtExceptionHandler {
    void handle(const Exception & ex) const;
};

class DebugUncaughtExceptionHandler : public UncaughtExceptionHandler {
    void handle(const Exception & ex) const;
};
SYLPH_END_NAMESPACE

#endif	/* _UNCAUGHTEXCEPTIONHANDLER_H */

