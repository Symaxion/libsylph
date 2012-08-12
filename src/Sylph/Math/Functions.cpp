#include "Functions.h"
#include "../Core/Debug.h"

SYLPH_BEGIN_NAMESPACE
namespace Math {
    float fastsin(float a) {
        // TODO implement this
        (void)a;
        SYLPH_STUB;
        return 0.0;
    }

    double fastsin(double a) {
        // TODO implement this
        (void)a;
        SYLPH_STUB;
        return 0.0;
    }

    sint pow(sint x, suint y) {
       if(y == 0) return 1;
       if(x == 0) return 0;
       for(suint i = 0; i < y; ++i) {
           x *= x;
       }
       return x;
    }

    #define S_GCD(R,A,B)

    S_GCD(sint,sint,sint)
    S_GCD(slong,sint,slong)
    S_GCD(slong,slong,sint)
    S_GCD(slong,slong,slong)

    #undef s_GCD
    
}
SYLPH_END_NAMESPACE

// vim: syntax=cpp11:ts=4:sts=4:sw=4:sta:et:tw=80:nobk
