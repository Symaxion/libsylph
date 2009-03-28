/* 
 * File:   Sylph.h
 * Author: frank
 *
 * Created on 17 januari 2009, 15:14
 */

#ifndef _SYLPH_H
#define	_SYLPH_H

#include "Sylph/OS/OS.h"
#include "Sylph/Core/Application.h"

namespace Sylph {
    /**
     * This enumeration contains the possible Application Types. Each element
     * is backed by an implementation of @c ApplicationSelf in @c Sylph::OS.<p>
     * When you want to use an alternative implementation of @c ApplicationSelf,
     * you can pass one of the elements of this enumeration as the definition
     * of the macro <code>APP_TYPE</code> to the compiler, e.g. for GCC:
     * <pre>g++ -o myapp -lSCore -DAPPTYPE=S_APPTYPE_FHS myapp.cpp</pre>
     * Note that this usage is not checked, i.e. with this command you can
     * compile perfectly on Mac %OS X or Windows, but <code>S_APPTYPE_FHS</code>
     * only works on Linux, but this error will not be reported. Therefore
     * using this kind of override requires support for a dynamic configuration
     * system, such as <i>GNU Autotools</i> or <i>CMake</i>
     */
    enum AppType {
        S_APPTYPE_BUNDLE, /**< This AppType uses a LibSylph-style 'bundle' 
                            *  structure. For more information about LibSylph
                            *  bundles, please see @c LinuxBundleAppSelf
                            *  or the wiki. This is the default AppType on Linux
                            * .
                            */
        S_APPTYPE_FHS, /**< This AppType uses a classic 'FHS'-like structure
                        *   on Linux. The application automatically detects
                        *   its prefix. See @c LinuxFHSAppSelf for more info. */
        S_APPTYPE_MACOS, /**< This is the default AppType on Mac %OS X. It uses
                          *   Mac %OS X-like bundles. It's not up to us to
                          *   document that, right? Just ask Apple. See
                          *   @c MacOSAppSelf*/
        S_APPTYPE_MACOS_FHS, /**< AppType on Mac %OS X that works similar to
                              *   @c S_APPTYPE_FHS . See @c MacOSFHSAppSelf.
                              *   (Yes, that <b>are</b> 6 capitals. Yes, you
                              *   <b>can</b> use CapsLock. No, you won't ever
                              *   have to type this -- it's all done internally)
                              */
        S_APPTYPE_WINDOWS /**< Default AppType on Windows. See @c WindowsAppSelf
                           * . I keep asking myself why whe have this, as
                           *   LibSylph won't even compile on Windows...*/
    };
    /**
     * Creates a new (non-LibSylph) object using the LibSylph garbage
     * collection. Example (using Qt):
     * <pre>
     * QPushButton but * = newgc(QPushButton("Hello"));
     * </pre>
     * The syntax is very similar to that of the normal new operator.
     */
     template<class T> T * newgc(T & t);
}

#ifndef SYLPH_NO_SYLPHMAIN
#ifdef SYLPH_OS_MACOSX
int main(int argc, char * argv[], char * envp[], char * apple[]);
#else
int main(int argc, char * argv[]);
#endif
static void SylphInit(int argc, char * argv[], char * apple[]) {
    Sylph::Core::Application::init(argc, argv, apple, APP_TYPE);
}
int SylphMain();
#endif

#endif	/* _SYLPH_H */

