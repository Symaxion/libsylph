/*
 * LibSylph Class Library
 * Copyright (C) 2011 Frank "SeySayux" Erens <seysayux@gmail.com>
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
 * Partially adapted from The Boost Class Libraries, v1.47
 *
 * Original license below:
 * (C) Copyright John Maddock et.al. 2000.
 * Use, modification and distribution are subject to the Boost Software
 * License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt).
 *
 * See http://www.boost.org/libs/type_traits for most recent version including
 * documentation.
 *
 * Created on: 10 okt. 2011
 */


#ifndef SYLPH_CORE_TRAITS_H_
#define SYLPH_CORE_TRAITS_H_

#include "Object.h"
#include <type_traits>

SYLPH_BEGIN_NAMESPACE
namespace Traits {
    // STD traits
    struct TrueType : public std::true_type {
    };

    struct FalseType : public std::false_type {
    };

    template<class T, T t>
    struct IntegralConstant : public std::integral_constant<T,t> {};

    template<class T>
    struct Identity {
        typedef T type;
    };

    template<bool B, class T = void>
    struct EnableIf {
    };

    template<class T>
    struct EnableIf<true,T> {
        typedef T type;
    };

    template<bool B, class T1, class T2>
    struct Condition {
    };

    template<class T1, class T2>
    struct Condition<false,T1,T2> {
        typedef T2 type;
    };

    template<class T1, class T2>
    struct Condition<true,T1,T2> {
        typedef T1 type;
    };

    template<class T>
    struct IsVoid : public std::is_void<T> {};

    template<class T>
    struct IsIntegral : public std::is_integral<T> {};

    template<class T>
    struct IsFloatingPoint : public std::is_floating_point<T> {};

    template<class T>
    struct IsArray : public std::is_array<T> {};

    template<class T>
    struct IsPointer : public std::is_pointer<T> {};

    template<class T>
    struct IsLvalueReference : public std::is_lvalue_reference<T> {};

    template<class T>
    struct IsRvalueReference : public std::is_rvalue_reference<T> {};

    template<class T>
    struct IsMemberObjectPointer : public std::is_member_object_pointer<T> {};

    template<class T>
    struct IsMemberFunctionPointer : public std::is_member_function_pointer<T> {};

    template<class T>
    struct IsEnum : public std::is_enum<T> {};

    template<class T>
    struct IsUnion : public std::is_union<T> {};

    template<class T>
    struct IsClass : public std::is_class<T> {};

    template<class T>
    struct IsFunction : public std::is_function<T> {};

    template<class T>
    struct IsReference : public std::is_reference<T> {};

    template<class T>
    struct IsArithmetic : public std::is_arithmetic<T> {};

    template<class T>
    struct IsFundamental : public std::is_fundamental<T> {};

    template<class T>
    struct IsObject : public std::is_object<T> {};

    template<class T>
    struct IsScalar : public std::is_scalar<T> {};

    template<class T>
    struct IsCompound : public std::is_compound<T> {};

    template<class T>
    struct IsMemberPointer : public std::is_member_pointer<T> {};

    template<class T>
    struct IsConst : public std::is_const<T> {};

    template<class T>
    struct IsVolatile : public std::is_volatile<T> {};

    template<class T>
    struct IsTrivial : public std::is_trivial<T> {};

    /*template<class T>
    struct IsTriviallyCopyable : public std::is_trivially_copyable<T> {};*/

    template<class T>
    struct IsStandardLayout : public std::is_standard_layout<T> {};

    template<class T>
    struct IsPod : public std::is_pod<T> {};

    /*template<class T>
    struct IsLiteralType : public std::is_literal_type<T> {};*/

    template<class T>
    struct IsEmpty : public std::is_empty<T> {};

    template<class T>
    struct IsPolymorphic : public std::is_polymorphic<T> {};

    template<class T>
    struct IsAbstract : public std::is_abstract<T> {};

    template<class T>
    struct IsSigned : public std::is_signed<T> {};

    template<class T>
    struct IsUnsigned : public std::is_unsigned<T> {};

    template<class T>
    struct RemoveCv : public std::remove_cv<T> {};

    template<class T>
    struct RemoveConst : public std::remove_const<T> {};

    template<class T>
    struct RemoveVolatile : public std::remove_volatile<T> {};

    template<class T>
    struct AddCv : public std::add_cv<T> {};

    template<class T>
    struct AddConst : public std::add_const<T> {};

    template<class T>
    struct AddVolatile : public std::add_volatile<T> {};

    template<class T>
    struct RemoveReference : public std::remove_reference<T> {};

    template<class T>
    struct AddLvalueReference : public std::add_lvalue_reference<T> {};

    template<class T>
    struct AddRvalueReference : public std::add_rvalue_reference<T> {};

    template<class T>
    struct RemovePointer : public std::remove_pointer<T> {};

    template<class T>
    struct AddPointer : public std::add_pointer<T> {};

    template<class T>
    struct MakeSigned : public std::make_signed<T> {};

    template<class T>
    struct MakeUnsigned : public std::make_unsigned<T> {};

    template<class T>
    struct RemoveExtent : public std::remove_extent<T> {};

    template<class T>
    struct RemoveAllExtents : public std::remove_all_extents<T> {};

    template<class T>
    struct AlignmentOf : public std::alignment_of<T> {};

    template<class T>
    struct RankOf : public std::rank<T> {};

    template<class T, unsigned N = 0>
    struct ExtentOf : public std::extent<T,N> {};

    template<class T1, class T2>
    struct IsSame : public std::is_same<T1,T2> {};

    /*template<class T1, class T2>
    struct IsBaseOf : public std::is_base_of<T1,T2> {};*/

    template<class T1, class T2>
    struct IsConvertibe : public std::is_convertible<T1,T2> {};

    template<std::size_t S1, std::size_t S2>
    struct AlignedStorage : public std::aligned_storage<S1,S2> {};

    // TODO: AlignedUnion

    template<class... T>
    struct CommonType : public std::common_type<T...> {};

    // TODO: UnderlyingType

    template <class T>
    typename AddRvalueReference<T>::type declval();

    template<class>
    struct ResultOf {};

    template<class F, class... A>
    struct ResultOf<F(A...)> {
        typedef decltype(declval<F>()(declval<A>()...)) type;
    };

    template<class T>
    struct Decay : public std::decay<T> {};

    // TODO: 'magic' compiler stuff

    // Our traits

    // Logical

    template<bool B1, bool B2, bool B3 = true, bool B4 = true>
    struct And : public FalseType {};

    template<>
    struct And<true,true,true,true> : public TrueType {};

    template<bool B1, bool B2 = false, bool B3 = false, bool B4 = false>
    struct Or : public TrueType {};

    template<>
    struct Or<false,false,false,false> : public FalseType {};

    template<bool B1>
    struct Not {};

    template<>
    struct Not<false> : public TrueType {};

    template<>
    struct Not<true> : public FalseType {};

    // Copy

    template<class T, class U>
    struct CopyConst {
        typedef typename Condition<IsConst<T>::value,
                typename AddConst<U>::type,
                typename RemoveConst<U>::value>::type type;
    };

    template<class T, class U>
    struct CopyVolatile {
        typedef typename Condition<IsVolatile<T>::value,
                typename AddVolatile<U>::type,
                typename RemoveVolatile<U>::value>::type type;
    };

    template<class T, class U>
    struct CopyCv {
        typedef typename CopyConst<T,
                typename CopyVolatile<T,U>::type>::type type;
    };

    template<class T, class U>
    struct CopyLvalueReference {
         typedef typename Condition<IsLvalueReference<T>::value,
                 typename AddLvalueReference<U>::type,
                 typename RemoveReference<U>::type>::type type;
    };

    template<class T, class U>
    struct CopyRvalueReference {
        typedef typename Condition<IsRvalueReference<T>::value,
                typename AddRvalueReference<U>::type,
                typename RemoveReference<U>::type>::type type;
    };

    template<class T, class U>
    struct CopyPointer {
        typedef typename Condition<IsPointer<T>::value,
                typename AddPointer<U>::type,
                typename RemovePointer<U>::type>::type type;
    };

    template<class T, class U>
    struct CopySigned {
        typedef typename Condition<IsSigned<T>::value,
                typename MakeSigned<U>::type,
                typename MakeUnsigned<U>::type>::type type;
    };

    // Efficiency

    template<class T>
    struct IsEfficientlyCopyable : public Condition<IsPod<T>::value,
            TrueType, FalseType>::type {};

    template<class T>
    struct EfficientPass {
        typedef typename Condition<IsEfficientlyCopyable<T>::value,
                T, const T&>::type type;
    };

    // Collection related

    /**
     * Operations supported:
     * begin/end: iterator
     * contains(T)
     * indexOf(T)
     */
    template<class T>
    struct IsCollection : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     *
     * Operations supported:
     * operator[](idx_t)
     * rbegin/rend: iterator
     */
    template<class T>
    struct IsSequentialCollection : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     *
     * Operations supported:
     * add(T): ensures element is in collection
     * remove(T)
     */
    template<class T>
    struct IsExpandableCollection : public FalseType {
    };

    /**
     * Traits:
     * Sequential and Expandable
     *
     * Operations supported:
     * peekFront(T)
     * pushFront(T)
     * popFront(T)
     * peekBack(T)
     * pushBack(T)
     * popBack(T)
     */
    template<class T>
    struct IsExpandableSequence : public And<IsSequentialCollection<T>::value,
            IsExpandableCollection<T>::value> {
    };

    /**
     * Traits:
     * IsSequentialCollection
     *
     * RandomAccessIterator available
     */
    template<class T>
    struct IsRandomAccessCollection : public FalseType {
    };

    template<class T>
    struct IsEfficientFrontInsertable : public FalseType {
    };

    template<class T>
    struct IsEfficientMiddleInsertable : public FalseType {
    };

    template<class T>
    struct IsEfficientBackInsertable : public FalseType {
    };

    template<class T>
    struct IsEfficientFrontRetrievable : public FalseType {
    };

    template<class T>
    struct IsEfficientMiddleRetrievable : public FalseType {
    };

    template<class T>
    struct IsEfficientBackRetrievable : public FalseType {
    };

    /**
     * Traits:
     * IsCollection
     */
    template<class T>
    struct IsUniqueElementCollection : public FalseType {
    };

    // Generic compatibility
    template<class T>
    struct IsSylphClass : public FalseType {
    };

    template<class T>
    struct SylphEquivalent {
    };

    // Std compatibility
    template<class T>
    struct IsStdClass : public FalseType {
    };

    template<class T>
    struct StdEquivalent {
    };

}

#define S_BEGIN_TRAITS namespace Sylph { namespace Traits {
#define S_END_TRAITS }}

#define S_SET_TRAIT(Trait,Class) \
        struct Trait<Class> : public TrueType {}
#define S_SET_TRAIT2(Trait,Class1,Class2) \
        struct Trait<Class1,Class2> : public TrueType {}
#define S_SET_TRAIT3(Trait,Class1,Class2,Class3) \
        struct Trait<Class1,Class2,Class3> : public TrueType {}
#define S_SET_TRAIT4(Trait,Class1,Class2,Class3,Class4) \
        struct Trait<Class1,Class2,Class3,Class4> : public TrueType {}

#define S_SET_TRAIT_FALSE(Trait,Class) \
        struct Trait<Class> : public FalseType {}
#define S_SET_TRAIT_FALSE2(Trait,Class1,Class2) \
        struct Trait<Class1,Class2> : public FalseType {}
#define S_SET_TRAIT_FALSE3(Trait,Class1,Class2,Class3) \
        struct Trait<Class1,Class2,Class3> : public FalseType {}
#define S_SET_TRAIT_FALSE4(Trait,Class1,Class2,Class3,Class4) \
        struct Trait<Class1,Class2,Class3,Class4> : public FalseType {}

#define S_SET_TRAIT_TYPE(Trait,Type,Class) \
        struct Trait<Class> { typedef Type type; }
#define S_SET_TRAIT_TYPE2(Trait,Type,Class1,Class2) \
        struct Trait<Class1,Class2> { typedef Type type; }
#define S_SET_TRAIT_TYPE3(Trait,Type,Class1,Class2,Class3) \
        struct Trait<Class1,Class2,Class3> { typedef Type type; }
#define S_SET_TRAIT_TYPE4(Trait,Type,Class1,Class2,Class3,Class4) \
        struct Trait<Class1,Class2,Class3,Class4> { typedef Type type; }

#define S_TRAIT(Trait,Class) \
        ::Sylph::Traits::Trait<Class>::value
#define S_TRAIT2(Trait,Class1,Class2) \
        ::Sylph::Traits::Trait<Class1,Class2>::value
#define S_TRAIT3(Trait,Class1,Class2,Class3) \
        ::Sylph::Traits::Trait<Class1,Class2,Class3>::value
#define S_TRAIT4(Trait,Class1,Class2,Class3,Class4) \
        ::Sylph::Traits::Trait<Class1,Class2,Class3,Class4>::value

#define S_TRAIT_TYPE(Trait,Class) \
        typename ::Sylph::Traits::Trait<Class>::type
#define S_TRAIT_TYPE2(Trait,Class1,Class2) \
        typename ::Sylph::Traits::Trait<Class1,Class2>::type
#define S_TRAIT_TYPE3(Trait,Class1,Class2,Class3) \
        typename ::Sylph::Traits::Trait<Class1,Class2,Class3>::type
#define S_TRAIT_TYPE4(Trait,Class1,Class2,Class3,Class4) \
        typename ::Sylph::Traits::Trait<Class1,Class2,Class3,Class4>::type

#define S_ENABLE_IF(Type, Condition) \
        typename ::Sylph::Traits::EnableIf<Condition,Type>::type
SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_TRAITS_H_ */
