#include "HashMap.h"

SYLPH_BEGIN_NAMESPACE

extern template class HashMap<String,sshort>;
extern template class HashMap<String,sushort>;
extern template class HashMap<String,sint>;
extern template class HashMap<String,suint>;
extern template class HashMap<String,slong>;
extern template class HashMap<String,sulong>;
extern template class HashMap<String,bool>;
extern template class HashMap<String,double>;
extern template class HashMap<String,float>;

extern template class HashMap<String,String>;
extern template class HashMap<String,Any>;

SYLPH_END_NAMESPACE
