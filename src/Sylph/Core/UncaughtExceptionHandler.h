/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 12 februari 2009, 19:21
 */

#ifndef _UNCAUGHTEXCEPTIONHANDLER_H
#define	_UNCAUGHTEXCEPTIONHANDLER_H

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

#endif	/* _UNCAUGHTEXCEPTIONHANDLER_H */

