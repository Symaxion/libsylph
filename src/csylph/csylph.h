/*
 * LibSylph Class Library
 * Copyright (C) 2009 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LibSylph Pulbic License as published
 * by the LibSylph Developers; either version 1.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the LibSylph
 * Public License for more details.
 *
 * You should have received a copy of the LibSylph Public License
 * along with this Library, if not, contact the LibSylph Developers.
 *
 * Created on 22 september 2009, 17:26
 */

#ifndef CSYLPH_H_
#define	CSYLPH_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    static int syerror = 0;

    #define SYENULL 1
    #define SYECPPEXC 2

    enum sylph_apptype_t {
        sy_at_linux,
        sy_at_lfhs,
        sy_at_mac,
        sy_at_mfhs
    };

    typedef struct sylph_file_t {
        const char* sy_f_loc;
    } sylph_file_t;

    extern int sylph_init(int, char**, sylph_apptype_t);
    extern int sylph_initm(int, char**, char**, sylph_apptype_t);

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

