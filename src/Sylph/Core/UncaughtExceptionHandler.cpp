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