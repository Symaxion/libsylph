#########################################################################
#
# LibSylph Class Library (build script)
# Copyright (C) 2013 Frank "SeySayux" Erens <seysayux@gmail.com>
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
#     1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#
#     2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#
#     3. This notice may not be removed or altered from any source
#     distribution.
#
#########################################################################

include(CheckCXXSourceRuns)

# Workaround for CMake not detecting this...
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_CLANG 1)
    set(CMAKE_EXE_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_SHARED_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_MODULE_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
endif()

if(CMAKE_COMPILER_IS_CLANG)
    set(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_EXE_LINKER_FLAGS})
    check_cxx_source_runs(
"
#include <stdio.h>

int main() {
#ifdef __clang__ 
#if __has_feature(cxx_generalized_initializers) && \\\\
    __has_feature(cxx_lambdas) && \\\\
    __has_feature(cxx_rvalue_references) && \\\\
    (__has_feature(cxx_decltype) || \\\\
    __has_extension(cxx_decltype))  && \\\\
    (__has_feature(cxx_auto_type) || \\\\
    __has_extension(cxx_auto_type)) && \\\\
    (__has_feature(cxx_trailing_return) || \\\\
    __has_extension(cxx_trailing_return)) && \\\\
    __has_feature(cxx_variadic_templates)
    return 0;
#endif
#endif
    return 1;
}" 
            S_CLANGVER)
    if(S_CLANGVER_EXITCODE EQUAL 1)
        set(CLANG_VERSION 0)
    else()
        set(CLANG_VERSION 1)
    endif()
    unset(CMAKE_REQUIRED_DEFINITIONS)
endif()


