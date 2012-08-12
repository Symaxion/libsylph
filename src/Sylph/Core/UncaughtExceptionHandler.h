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
 * Created on 12 februari 2009, 19:21
 */

#ifndef SYLPH_CORE_UNCAUGHTEXCEPTIONHANDLER_H
#define	SYLPH_CORE_UNCAUGHTEXCEPTIONHANDLER_H

#include "Object.h"
#include "Exception.h"
#include "Application.h"
#include "Debug.h"

SYLPH_BEGIN_NAMESPACE


class UncaughtExceptionHandler : public Object {
public:
    UncaughtExceptionHandler() {}
    virtual ~UncaughtExceptionHandler() {}
    virtual void handle(const Exception & ex) const = 0;
    virtual void handleAssertion(const Assertion& as) const = 0;
public:
    static UncaughtExceptionHandler * handler;
};

struct DefaultUncaughtExceptionHandler : public UncaughtExceptionHandler {
    DefaultUncaughtExceptionHandler() {}
    void handle(const Exception & ex) const;
    void handleAssertion(const Assertion& as) const;
};

struct DebugUncaughtExceptionHandler : public UncaughtExceptionHandler {
    DebugUncaughtExceptionHandler() {}
    void handle(const Exception & ex) const;
    void handleAssertion(const Assertion& as) const;
};
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_UNCAUGHTEXCEPTIONHANDLER_H */


// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
