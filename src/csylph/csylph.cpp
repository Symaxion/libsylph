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
 */

#include <sys/stat.h>
#include <string.h>

#include "csylph.h"
#include "../Sylph/Core/Application.h"
#include "../Sylph/Core/File.h"

int sylph_init(int argc, char** argv, sylph_apptype_t app, char* name) {
    try {
        if (argv == 0 || name == 0) {
            syerror = SYENULL;
            return 0;
        }
        Sylph::AppType type;
        switch (app) {
            case sy_at_linux:
                type = Sylph::S_APPTYPE_BUNDLE;
                break;
            case sy_at_lfhs:
                type = Sylph::S_APPTYPE_FHS;
                break;
            case sy_at_mac:
                type = Sylph::S_APPTYPE_MACOS;
                break;
            case sy_at_mfhs:
                type = Sylph::S_APPTYPE_MACOS_FHS;
                break;
            default:
                exit(1);
                break;
        }
        Sylph::Application::init(argc, argv, 0, type, name);
        return 1;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sylph_initm(int argc, char** argv, char** apple, sylph_apptype_t app,
        char* name) {
    try {
        if (argv == 0 || name == 0) {
            syerror = SYENULL;
            return 0;
        }
        Sylph::AppType type;
        switch (app) {
            case sy_at_linux:
                type = Sylph::S_APPTYPE_BUNDLE;
                break;
            case sy_at_lfhs:
                type = Sylph::S_APPTYPE_FHS;
                break;
            case sy_at_mac:
                type = Sylph::S_APPTYPE_MACOS;
                break;
            case sy_at_mfhs:
                type = Sylph::S_APPTYPE_MACOS_FHS;
                break;
            default:
                exit(1);
                break;
        }
        Sylph::Application::init(argc, argv, apple, type, name);
        return 1;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_bundle(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->bundle();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_rscdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->resourceDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_rsc(sylph_file_t* in, const char* fname) {
    try {
        if (in == 0 || fname == 0) {
            syerror = SYENULL;
            return 1;
        }
        Sylph::File f = thisapp->resource(fname);
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_libdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->libraryDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_pldir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->pluginDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_plddir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->plugindisabledDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_sys_libdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->systemLibraryDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_sys_sts(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->systemSettings();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_sys_stsdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->systemSettingsDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_sys_pldir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->systemPluginDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_sys_plddir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->systemPluginDisabledDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_sys_rscdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->systemResourceDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_sys_rsc(sylph_file_t* in, const char* fname) {
    try {
        if (in == 0 || fname == 0) {
            syerror = SYENULL;
            return 1;
        }
        Sylph::File f = thisapp->systemResource(fname);
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_usr(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->userHome();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_usr_libdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->userLibraryDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_usr_sts(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->userSettings();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_usr_stsdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->userSettingsDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_usr_pldir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->userPluginDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_usr_plddir(sylph_file_t* in)
try {
    if (in == 0) {
        syerror = SYENULL;
        return 1;
    }
    static Sylph::File f = thisapp->userPluginDisabledDir();
    in->sy_f_loc = f.toCanonicalName();
    return 0;
} catch (Sylph::Exception ex) {
    strncpy(sy_excp, ex.what(), 255);
    syerror = SYECPPEXC;
    return 1;
}

int sy_usr_rscdir(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->userResourceDir();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_usr_rsc(sylph_file_t* in, const char* fname) {
    try {
        if (in == 0 || fname == 0) {
            syerror = SYENULL;
            return 1;
        }
        Sylph::File f = thisapp->systemResource(fname);
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

int sy_prefix(sylph_file_t* in) {
    try {
        if (in == 0) {
            syerror = SYENULL;
            return 1;
        }
        static Sylph::File f = thisapp->prefix();
        in->sy_f_loc = f.toCanonicalName();
        return 0;
    } catch (Sylph::Exception ex) {
        strncpy(sy_excp, ex.what(), 255);
        syerror = SYECPPEXC;
        return 1;
    }
}

const char* sy_cppexp() {
    return sy_excp;
}
