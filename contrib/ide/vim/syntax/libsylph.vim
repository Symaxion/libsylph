" LibSylph
syn keyword cppType byte Array String seq uchar
syn keyword cppType frac vec2f vec2d vec3f vec3d complexf complexd anglef angled pt2f pt2d pt3f pt3d
syn keyword cppType mat2f mat3f mat4f mat2d mat3d mat4d quatf quatd
syn keyword cppType function
syn keyword cppType idx_t sidx_t
syn keyword cppType fsize_t fssize_t
syn keyword cppOperator over fpeq fpeqn
syn keyword cConstant noop
syn keyword cConditional if_nullptr check_nullptr
syn keyword cRepeat sforeach
syn keyword cppStatement newgc newgc_nothrow deletegc thisapp
syn keyword cppOperator over
syn keyword cppExceptions sthrow
syn keyword cConstant SYLPH_BEGIN_NAMESPACE SYLPH_END_NAMESPACE
syn keyword cConstant S_BEGIN_TRAITS S_END_TRAITS

" Do not use null anymore, use nullptr
syn keyword cError null 

" Constants and member variables
syn match cConstant /\<k[A-Z]\w\+/
syn match cppMember /\<m[A-Z]\w\+/
syn match cppGlobal /\<g[A-Z]\w\+/
hi def link cppMember Identifier
hi def link cppGlobal WarningMsg 
