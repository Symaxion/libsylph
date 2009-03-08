#include "UncaughtExceptionHandler.h"

SYLPH_START_NAMESPACE(Core)
DefaultUncaughtExceptionHandler::handle(Exception& ex) const {
    thisapp->fail("Uncaught Exception: "+ex.name()+": "+ex.what());
}

DebugUncaughtExceptionHandler::handle(Exception& ex) const {
    thisapp->fail("Uncaught Exception: "+ex.name()+": "+ex.what(), ex.file, ex.line);
}

SYLPH_END_NAMESPACE(Core)