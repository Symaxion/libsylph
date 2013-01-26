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
    set(CMAKE_EXE_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_SHARED_LINKER_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_MODULE_LINKER_FLAGS "-std=c++11 -stdlib=libc++")

    set(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_EXE_LINKER_FLAGS})
    check_cxx_source_runs(
"
#include <stdio.h>

int main() {
#ifdef __clang__ 
#if __has_feature(cxx_lambdas) && \\\\
    (__has_feature(cxx_auto_type) || \\\\
    __has_extension(cxx_auto_type)) && \\\\
    (__has_feature(cxx_trailing_return) || \\\\
    __has_extension(cxx_trailing_return)) && \\\\
    (__has_feature(cxx_alias_templates) || \\\\
    __has_extension(cxx_alias_templates)) && \\\\
    (__has_feature(cxx_alignas) || \\\\
    __has_extension(cxx_alignas)) && \\\\
    (__has_feature(cxx_attributes) || \\\\
    __has_extension(cxx_attributes)) && \\\\
    __has_feature(cxx_constexpr) && \\\\
    (__has_feature(cxx_decltype) || \\\\
    __has_extension(cxx_decltype))  && \\\\
    (__has_feature(cxx_default_function_template_args) || \\\\
    __has_extension(cxx_default_function_template_args)) && \\\\
    (__has_feature(cxx_defaulted_functions) || \\\\
    __has_extension(cxx_defaulted_functions)) && \\\\
    (__has_feature(cxx_deleted_functions) || \\\\
    __has_extension(cxx_deleted_functions)) && \\\\
    __has_feature(cxx_explicit_conversions) && \\\\
    __has_feature(cxx_generalized_initializers) && \\\\
    __has_feature(cxx_implicit_moves) && \\\\
    (__has_feature(cxx_noexcept) || \\\\
    __has_extension(cxx_noexcept)) && \\\\
    __has_feature(cxx_nonstatic_member_init) && \\\\
    (__has_feature(cxx_nullptr) || \\\\
    __has_extension(cxx_nullptr)) && \\\\
    (__has_feature(cxx_override_control) || \\\\
    __has_extension(cxx_override_control)) && \\\\
    (__has_feature(cxx_range_for) || \\\\
    __has_extension(cxx_range_for)) && \\\\
    (__has_feature(cxx_raw_string_literals) || \\\\
    __has_extension(cxx_raw_string_literals)) && \\\\
    (__has_feature(cxx_static_assert) || \\\\
    __has_extension(cxx_static_assert)) && \\\\
    (__has_feature(cxx_variadic_templates) || \\\\
    __has_extension(cxx_variadic_templates))

    return 0;
#endif
#endif
    return 1;
}" 
            S_CLANGVER)
    if(S_CLANGVER_EXITCODE EQUAL 1)
        set(S_CLANG_HAS_REQUIRED_FEATURES 0)
    else()
        set(S_CLANG_HAS_REQUIRED_FEATURES 1)
    endif()
    unset(CMAKE_REQUIRED_DEFINITIONS)
endif()


