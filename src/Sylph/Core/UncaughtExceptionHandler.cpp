#include "UncaughtExceptionHandler.h"
#include "StringBuffer.h"

SYLPH_BEGIN_NAMESPACE
void DefaultUncaughtExceptionHandler::handle(const Exception& ex) const {
    StringBuffer buf;
    buf << "Uncaught Exception: "<<ex.name()<<": "<<ex.what()<<'\n';
    if(ex.tracemsg != NULL) {
        buf << "Trace messages: \n";
        Exception::TraceMessage * msg = ex.tracemsg;
        while(msg->next != NULL) {
            buf << '\t' << String(msg->message) << '\n';
            msg = msg->next;
        }
    }
    thisapp->fail(buf);
}

void DebugUncaughtExceptionHandler::handle(const Exception& ex) const {
    StringBuffer buf;
    buf << "Uncaught Exception: "<<ex.name()<<": "<<ex.what()<<'\n';
    if(ex.tracemsg != NULL) {
        buf << "Trace messages: \n";
        Exception::TraceMessage * msg = ex.tracemsg;
        while(msg->next != NULL) {
            buf << '\t' << String(msg->message) << '\n';
            msg = msg->next;
        }
    }
    thisapp->fail(buf, ex._file, ex._line);
}

SYLPH_END_NAMESPACE