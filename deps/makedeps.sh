#!/bin/bash

. ../makedeps.hdr

all() {
  subdir ./binreloc
  subdir ./gc
}

clean() {
  all
}

. ../makedeps.ftr