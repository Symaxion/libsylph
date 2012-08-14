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
 * Created on 1 augustus 2009, 9:15
 */

#ifndef SYLPH_CORE_APPTYPE_H_
#define	SYLPH_CORE_APPTYPE_H_

#include "Object.h"

SYLPH_BEGIN_NAMESPACE
/**
 * This enumeration contains the possible Application Types.
 *
 * Each element is backed by an implementation of @c ApplicationSelf in
 * @c Sylph::OS.
 *
 * When you want to use an alternative implementation of @c ApplicationSelf,
 * you can pass one of the elements of this enumeration as the definition
 * of the macro <code>APP_TYPE</code> to the compiler, e.g. for GCC:
 * <pre>g++ -o myapp -lSylph -DAPPTYPE=S_APPTYPE_FHS myapp.cpp</pre>
 * Note that LibSylph does not check if the given apptype makes sense on the
 * current platform, i.e. with the above command you can
 * compile perfectly under Mac %OS X or Windows, while
 * <code>S_APPTYPE_FHS</code> only works on Linux. No error will directly be
 * reported for faulty use of an APPTYPE, however, runtime errors are highly
 * likely to occur.
 *
 * It is therefore recommended that any overrides to this variable go through
 * an automated, cross-platform build system, such as <i>GNU Autotools</i> or
 * <i>CMake</i>.
 */
enum AppType {
    S_APPTYPE_BUNDLE, /**< This AppType uses a LibSylph-style 'bundle'
                            *  structure. For more information about LibSylph
                            *  bundles, please see @c LinuxBundleAppSelf
                            *  or the wiki. This is the default AppType on 
                            *  Linux.
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
SYLPH_END_NAMESPACE

#endif	/* SYLPH_CORE_APPTYPE_H_ */


// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
