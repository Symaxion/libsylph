#!/bin/sh
# 
# File:   build-gc.sh
# Author: Frank "SeySayux" Erens <seysayux@gmail.com>
#
# Created on 18 juli 2009, 19:27
#

pushd ../gc
./configure --enable-c++
make
cp .libs/libgc.a .
popd