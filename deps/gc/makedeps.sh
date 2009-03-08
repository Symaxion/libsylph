#!/bin/bash

. ../../makedeps.hdr

all() {
  ./configure --enable-cplusplus
  make
  cp .libs/lib{cord,gc}.a ../../lib
}

clean() {
  make distclean
}

. ../../makedeps.ftr