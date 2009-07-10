#include "Sylph.h"
#include "Sylph/Core/Application.h"
#include <gc.h>
#include <new>
#include "Sylph/Core/UncaughtExceptionHandler.h"

#ifdef SYLPH_OS_MACOSX

int main(int argc, char * argv[], char * envp[], char * apple[]) {
    try {
        SylphInit(argc, argv, apple);
        return SylphMain(Sylph::Array<Sylph::String>::fromPointer(argc, argv));
    } catch (Sylph::Exception & ex) {
        Sylph::UncaughtExceptionHandler::handler->handle(ex);
    }
}
#else

int main(int argc, char * argv[]) {
    try {
        SylphInit(argc, argv, NULL);
        return SylphMain();
    } catch (Sylph::Core::Exception & ex) {
        Sylph::Core::UncaughtExceptionHandler::handler->handle(ex);
    }
}
#endif

namespace Sylph {

    template<class T,class... Args> T * newgc(const Args...& args) {
        T * tr = GC_MALLOC(sizeof (T));
        if(!tr) throw std::bad_alloc();
        tr = new(tr) T(args...);
        GC_finalization_proc oldProc;
        void* oldData;
        void* base = GC_base((void *) tr);
        if (0 != base) {
            // Don't call the debug version, since this is a real base address.
            GC_register_finalizer_ignore_self(
                    base, (GC_finalization_proc) cleanupgc, (void*) ((char*) tr - (char*) base),
                    &oldProc, &oldData);
            if (0 != oldProc) {
                GC_register_finalizer_ignore_self(base, oldProc, oldData, 0, 0);
            }
        }
        return tr;
    }

    template<class T>
    void cleanupgc(void* obj, void* displ) {
        ((T*) ((char*) obj + (ptrdiff_t) displ))->~T();
    }

    template<class T>
    void deletegc(const T * obj) {
        GC_FREE(obj);
    }
}