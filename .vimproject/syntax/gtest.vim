if exists("b:current_syntax")
  finish
endif

syn match gtestOk   "\[----------\]"
syn match gtestOk   "\[==========\]"
syn match gtestOk   "\[ RUN      \]"
syn match gtestOk   "\[       OK \]"
syn match gtestOk   "\[  PASSED  \]"
syn match gtestFail "\[  FAILED  \]"

syn match gtestType "Test\w\+"
syn match gtestTest "test[A-Z]\w\+"
syn match gtestTime "(\d\+ ms.*)"

syn match Normal    "SylphTestExe"

hi gtestOk    guifg=DarkGreen gui=bold
hi gtestFail  guifg=DarkRed   gui=bold

hi def link gtestType   Type
hi def link gtestTest   Identifier
hi def link gtestTime   Constant

let b:current_syntax = "gtest"
