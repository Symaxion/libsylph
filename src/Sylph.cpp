#include "Sylph.h"
#include "Sylph/Core/Application.h"
#include <gc.h>
#include "Sylph/Core/UncaughtExceptionHandler.h"

#ifdef SYLPH_OS_MACOSX
int main(int argc, char * argv[], char * envp[], char * apple[]) {
    try {
    SylphInit(argc,argv,apple);
    return SylphMain();
    } catch (Sylph::Core::Exception & ex) {
        Sylph::Core::UncaughtExceptionHandler::handler->handle(ex);
    }
}
#else
int main(int argc, char * argv[]) {
    try {
    SylphInit(argc,argv,NULL);
    return SylphMain();
    } catch (Sylph::Core::Exception & ex) {
        Sylph::Core::UncaughtExceptionHandler::handler->handle(ex);
    }
}
#endif

namespace Sylph {
    template<class T> T * newgc(T & t) {
        T * tr = GC_MALLOC(sizeof(T));
        *tr = t;
        return tr;
    };
}