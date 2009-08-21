#!/bin/bash
# 
# File:   developers.sh
# Author: SeySayux
#

log() {
    echo $@ >&2
}

do-svn() {
    #prepare for SVN
    cat > README-SVN << EOT
You have checked out the current trunk from SVN. Code from SVN does not always
compile or can be incomplete. It is possible that certain build
EOT
    if [ "$1" == "compile" ]; then
cat >> README-SVN << EOT
However, current code seems to compile. Be warned that it may still have many
bugs, or can be simply incomplete. If you want to have working code, please
check out the latest relase from the 'unstable' branch.
EOT
    else
    cat >> README-SVN << EOT
SVN is currently known to be broken. Please check out the latest release from
the 'unstable' branch.
EOT
    fi
    cat >> README-SVN << EOT

For instructions on building and installing, please see the README file in this
directory. You might need to recreate the src/SourcesList.txt files. In order to
do so, please run:

        ./developers.sh cmake

This will create the required files for the build.
EOT

}

do-cmake() {
    log Creating/updating SourcesList.txt...
    pushd src
    echo '# This file is automatically generated by developers.sh in' \
        >> SourcesList.txt
    echo '# the main source directory. DO NOT EDIT MANUALLY!' >> SourcesList.txt
    echo >> SourcesList.txt
    echo 'SET ( SYLPH_ALL_SRC ' >> SourcesList.txt
    
    for x in `find * | grep '\.cpp$'`; do
        echo -n "$x " >> SourcesList.txt
    done

    echo ' )' >> SourcesList.txt
    popd

    pushd test
    echo '# This file is automatically generated by developers.sh in' \
        >> SourcesList.txt
    echo '# the main source directory. DO NOT EDIT MANUALLY!' >> SourcesList.txt
    echo >> SourcesList.txt
    echo 'SET ( STEST_ALL_SRC ' >> SourcesList.txt

    for x in `find * | grep '\.cpp$'`; do
        echo -n "$x " >> SourcesList.txt
    done

    echo ' )' >> SourcesList.txt
    popd
    log 'Done!'
}

do-release() {
    if [ -z "$1" ]; then error; fi
    log Preparing for release "$1" of LibSylph...
    log Cleaning SVN stuff...
    rm -f README-SVN
    find . -name '.svn' -exec rm -rf '{}' \;
    log Creating CMake stuff
    do-cmake
    log Cleaning build...
    make clean
    log Removing old builds
    for x in `ls | grep "^libsylph-.*-src.tar.bz2$"`; do
        rm -v $x;
    done;
    log Creating tarball in parent directory...
    pushd ..
    cp sylph libsylph-"$1"-src
    tar cjf libsylph-"$1"-src libsylph-"$1"-src.tar.bz2
    rm -rf libsylph-"$1"-src
    popd
    log Removing this script '('don\'t worry, it\'s up in SVN')'...
    rm -f developers.sh
    log 'Done!'
}

error() {
    echo "Syntax error."
    exit 1
}

case "$1" in
    svn)
        case "$2" in
            compile|nocompile)
              do-svn "$2"
              ;;
            *)
              error
            ;;
        esac
    ;;
    cmake)
        do-cmake
    ;;
    release)
        do-release "$1"
    ;;
    *)
    echo 'This script contains several useful functions for the libsylph devs.'
    ;;
esac