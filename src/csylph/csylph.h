/*
 * LibSylph Class Library
 * Copyright (C) 2010 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Created on 22 september 2009, 17:26
 */

#ifndef CSYLPH_H_
#define	CSYLPH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>

    static int syerror = 0;

    static char* sy_excp = (char*)malloc(255);

    #define SYENONE     0
    #define SYENULL     1
    #define SYECPPEXC   2

    enum sylph_apptype_t {
        sy_at_linux,
        sy_at_lfhs,
        sy_at_mac,
        sy_at_mfhs
    };

    typedef struct sylph_file_t {
        const char* sy_f_loc;
    } sylph_file_t;

    extern int sylph_init(int, char**, sylph_apptype_t,char*);
    extern int sylph_initm(int, char**, char**, sylph_apptype_t,char*);

    extern int sy_bundle(sylph_file_t*);
    extern int sy_rscdir(sylph_file_t*);
    extern int sy_rsc(sylph_file_t*, const char*);
    extern int sy_libdir(sylph_file_t*);
    extern int sy_pldir(sylph_file_t*);
    extern int sy_plddir(sylph_file_t*);

    extern int sy_sys_libdir(sylph_file_t*);
    extern int sy_sys_sts(sylph_file_t*);
    extern int sy_sys_stsdir(sylph_file_t*);
    extern int sy_sys_pldir(sylph_file_t*);
    extern int sy_sys_plddir(sylph_file_t*);
    extern int sy_sys_rscdir(sylph_file_t*);
    extern int sy_sys_rsc(sylph_file_t*,const char*);

    extern int sy_usr(sylph_file_t*);

    extern int sy_usr_libdir(sylph_file_t*);
    extern int sy_usr_sts(sylph_file_t*);
    extern int sy_usr_stsdir(sylph_file_t*);
    extern int sy_usr_pldir(sylph_file_t*);
    extern int sy_usr_plddir(sylph_file_t*);
    extern int sy_usr_rscdir(sylph_file_t*);
    extern int sy_usr_rsc(sylph_file_t*,const char*);

    extern int sy_prefix(sylph_file_t*);

    extern const char* sy_cppexp();

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif	/* CSYLPH_H_ */

