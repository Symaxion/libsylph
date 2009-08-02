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

