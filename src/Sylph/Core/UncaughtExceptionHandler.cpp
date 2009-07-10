#include "UncaughtExceptionHandler.h"

SYLPH_BEGIN_NAMESPACE
DefaultUncaughtExceptionHandler::handle(const Exception& ex) const {
    //2do: add traceinfo
    thisapp->fail("Uncaught Exception: "+ex.name()+": "+ex.what());
}

DebugUncaughtExceptionHandler::handle(const Exception& ex) const {
    //2do: add traceinfo
    thisapp->fail("Uncaught Exception: "+ex.name()+": "+ex.what(), ex._file,
            ex._line);
}

SYLPH_END_NAMESPACE