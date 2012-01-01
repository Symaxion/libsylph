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
 */

#include "UncaughtExceptionHandler.h"
#include "StringBuffer.h"

SYLPH_BEGIN_NAMESPACE

#ifdef SYLPH_DEBUG
    UncaughtExceptionHandler * UncaughtExceptionHandler::handler =
            new DebugUncaughtExceptionHandler;
#else
    UncaughtExceptionHandler * UncaughtExceptionHandler::handler =
            new DefaultUncaughtExceptionHandler;
#endif
    
void DefaultUncaughtExceptionHandler::handle(const Exception& ex) const {
    StringBuffer buf;
    buf << "Uncaught Exception: "<<ex.name()<<": "<<ex.what()<<'\n';
    if(ex.tracemsg != null) {
        buf << "Trace messages: \n";
        Exception::TraceMessage * msg = ex.tracemsg;
        do {
            buf << "    " << String(msg->message) << '\n';
        } while((msg->next != null) && (msg = msg->next));
    }
    thisapp->fail(buf, false);
}

void DefaultUncaughtExceptionHandler::handleAssertion
    (const Assertion& ex) const {
    StringBuffer buf;
    buf << "Assertion failed: "<<ex.name()<<": "<<ex.what()<<'\n';
    if(ex.tracemsg != null) {
        buf << "Trace messages: \n";
        Exception::TraceMessage * msg = ex.tracemsg;
        do {
            buf << "    " << String(msg->message) << '\n';
        } while((msg->next != null) && (msg = msg->next));
    }
    thisapp->fail(buf, false);
}

void DebugUncaughtExceptionHandler::handle(const Exception& ex) const {
    StringBuffer buf;
    buf << "Uncaught Exception: "<<ex.name()<<": "<<ex.what()<<'\n';
    if(ex.tracemsg != null) {
        buf << "Trace messages: \n";
        Exception::TraceMessage * msg = ex.tracemsg;
        do {
            buf << "    " << String(msg->message) << '\n';
        } while((msg->next != null) && (msg = msg->next));
    }
    thisapp->fail(buf, ex._file, ex._line, false);
}

void DebugUncaughtExceptionHandler::handleAssertion(const Assertion& ex) const {
    StringBuffer buf;
    buf << "Assertion failed: "<<ex.name()<<": "<<ex.what()<<'\n';
    if(ex.tracemsg != null) {
        buf << "Trace messages: \n";
        Exception::TraceMessage * msg = ex.tracemsg;
        do {
            buf << "    " << String(msg->message) << '\n';
        } while((msg->next != null) && (msg = msg->next));
    }
    thisapp->fail(buf, ex._file, ex._line, false);
}

SYLPH_END_NAMESPACE
