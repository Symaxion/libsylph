#include "Functions.h"

SYLPH_BEGIN_NAMESPACE
namespace Math {
    float fastsin(float a) {
    }

    double fastsin(double a) {
    }

    sint pow(sint x, suint y) {   if(y == 0) return 1;
       if(x == 0) return 0;
       for(sint i = 0; i < y; ++i) {
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
