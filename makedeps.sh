#!/bin/bash

. ./makedeps.hdr

all() {
  subdir deps
}

clean() {
  subdir deps
}

. ./makedeps.ftr