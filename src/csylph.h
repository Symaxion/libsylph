/* 
 * File:   sylphcf.h
 * Author: frank
 *
 * Created on 16 april 2009, 17:35
 */

#ifndef SYLPHBF_H_
#define	SYLPHBF_H_

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdbool.h>
#define SY_alloc(_type,_amt) malloc(sizeof(_type)*amt)
#define SY_calloc(_type,_amt) calloc(sizeof(_type),amt)
#define SY_free(_obj) free(_obj);

    typedef const char * SY_file_t;
    typedef SY_file_t SY_bundle_t;

    // List stuff

    struct SY_list_node {
        void * contents;
        SY_list_node * next;
        SY_list_node * previous;
    };

    typedef struct SY_list {
        size_t length;
        struct SY_list_node * first;
        struct SY_list_node * last;
    } SY_list;

    extern SY_list * SY_list_new();
    extern void SY_list_destroy(SY_list * self);
    extern void SY_list_append(SY_list * self, void * append);
    extern void * SY_list_pop(SY_list * self);

    typedef struct SY_iterator {
        SY_list_node * current;
    } SY_iterator;

    extern SY_iterator * SY_iterator_new(SY_list * list);
    extern void SY_iterator_destroy(SY_iterator * self);
    extern void * SY_iterator_current(SY_iterator * self);
    extern bool SY_iterator_forward(SY_iterator * self);
    extern bool SY_iterator_backward(SY_iterator * self);
    extern void SY_iterator_insert(SY_iterator * self, void * p);
    extern void SY_iterator_remove(SY_iterator * self);

    // End of list stuff

    struct SY_app_impl {
        SY_file_t(*locate_binary)();
        SY_file_t(*locate_resource)(SY_file_t name);
        SY_file_t(*locate_prefix)();
        bool(*has_bundle)();
        SY_bundle_t(*locate_bundle)();
    };

    #define SY_predeclare_app_impl(name) \
    extern SY_file_t   SY_##name##_locate_binary(); \
    extern SY_file_t   SY_##name##_locate_resource(SY_file_t name); \
    extern SY_file_t   SY_##name##_locate_prefix(); \
    extern bool        SY_##name##_has_bundle(); \
    extern SY_bundle_t SY_##name##_locate_bundle()

    SY_predeclare_app_impl(LB); // Linux bundle
    SY_predeclare_app_impl(LF); // Linux FHS
    SY_predeclare_app_impl(MB); // Mac bundle
    SY_predeclare_app_impl(MF); // Mac FHS
    SY_predeclare_app_impl(Woe); // Woe32

    #define SY_decl_app_impl(name) \
    extern struct SY_app_impl SY_##name##_app_impl

    SY_decl_app_impl(LB);
    SY_decl_app_impl(LF);
    SY_decl_app_impl(MB);
    SY_decl_app_impl(MF);
    SY_decl_app_impl(Woe);

    #define SY_def_app_impl(name) \
    struct SY_app_impl SY_##name##_app_impl = { \
        .locate_binary   = SY_##name##_locate_binary; \
        .locate_resource = SY_##name##_locate_resource; \
        .locate_prefix   = SY_##name##_locate_prefix; \
        .has_bundle      = SY_##name##_has_bundle; \
        .locate_bunlde   = SY_##name##_locate_bunlde; \
    }

    /* No, not defined here, but in the source file
     This is because C++ doesn't understand this syntax */

#ifdef	__cplusplus
}
#endif

#endif	/* SYLPHBF_H_ */

