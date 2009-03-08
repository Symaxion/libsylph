#!/bin/bash

. ../../makedeps.hdr

all() {
  gcc -DENABLE_BINRELOC -c binreloc.c -o binreloc.o
  ar rcs libbinreloc.a binreloc.o
  cp libbinreloc.a ../../lib
}

clean() {
  rm binreloc.o libbinreloc.a
}

. ../../makedeps.ftr 
