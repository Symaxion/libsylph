#!/bin/sh
echo "__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__" | "$*" -E - | grep '^[^#]' | tr -d ' '
