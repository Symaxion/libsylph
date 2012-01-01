namespace Concepts {
    /**
     * A function is any object that has an overloaded @c operator(). 
     *
     * A function is said to be <i>n-ary</i> if it accepts n parameters.
     */
    template<class T, class... A>
    struct Function {
        /** &nbsp; */
        T operator()(A...);
    };

    /**
     * A predicate is a unary function returning bool.
     */
    template<class T>
    struct Predicate : public Function<bool,T> {};

    /**
     * A relation is a binary function returing bool.
     */
    template<class T1, class T2>
    struct Relation : public Function<bool, T1, T2> {};

    /**
     * A relation is same-typed when both parameters are of the same type.
     */
    template<class T>
    struct SameTypeRelation : public Relation<T, T> {};
    
    /**
     * A same-typed relation @c R is reflexive whenever it holds that for any
     * object @c t of type @c T holds that <code>R(t,t) == true</code>.
     */
    template<class T>
    struct ReflexiveRelation : public virtual SameTypeRelation<T> {};

    /**
     * irreflexive
     */
    template<class T>
    struct IrreflexiveRelation : public virtual SameTypeRelation<T> {};

    /**
     * symmetric
     */
    template<class T>
    struct SymmetricRelation : public virtual SameTypeRelation<T> {};

    /**
     * antisymmetric
     */
    template<class T>
    struct AntisymmetricRelation : public virtual SameTypeRelation<T> {};

    /**
     * transitive
     */
    template<class T>
    struct TransitiveRelation : public virtual SameTypeRelation<T> {};

    /**
     * equivalence
     */
    template<class T>
    struct EquivalenceRelation : public ReflexiveRelation<T>,
            public SymmetricRelation<T>, public TransitiveRelation<T> {};

    /**
     * weak order
     */
    template<class T>
    struct WeakOrderRelation : public ReflexiveRelation<T>,
            public AntisymmetricRelation<T>, public TransitiveRelation<T> {};

    /**
     * strong order
     */
    template<class T>
    struct StrongOrderRelation : public IrreflexiveRelation<T>,
            public AntisymmetricRelation<T>, public TransitiveRelation<T> {};
            
}
