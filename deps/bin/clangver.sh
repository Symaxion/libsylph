#!/bin/bash
x=$(mktemp /tmp/XXXXXXXX)
cat << 'EOS' | "$*" -x c++ -std=c++11 -stdlib=libc++ - -o $x
#include <stdio.h>

int main() {
#ifdef __clang__ 
    #if __has_feature(cxx_generalized_initializers) && \
        __has_feature(cxx_lambdas) && \
        __has_feature(cxx_rvalue_references) && \
        (__has_feature(cxx_decltype) || \
        __has_extension(cxx_decltype))  && \
        (__has_feature(cxx_auto_type) || \
        __has_extension(cxx_auto_type)) && \
        (__has_feature(cxx_trailing_return) || \
        __has_extension(cxx_trailing_return)) && \
        __has_feature(cxx_variadic_templates)
        puts("1");
        return 0;
    #endif
#endif
    puts("0");
    return 0;
}
EOS
$x
rm $x
