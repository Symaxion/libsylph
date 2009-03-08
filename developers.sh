#!/bin/bash
# 
# File:   developers.sh
# Author: SeySayux
#

do-svn() {
    #prepare for SVN
    cat > README-SVN << EOT
In order to compile the sources from SVN, you need to get a copy of The Boost
Library, v1.37.0. Put it in the directory "deps" and rename the folder you
got after untarring (i.e. boost-1.37.0) to "boost".

Note that code from SVN does not always compile or can be incomplete.
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
directory. You might need to recreate the CMakeLists.txt files. In order to do
so, please run:

        ./developers.sh cmake

This will create the required files for the build.
EOT

}

do-cmake() {
    echo "CMake not supported yet. Run make and hope the best..."
}

do-release() {
    rm -f README-SVN
    rm -f developers.sh
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
    ;;
    cmake)
        do-cmake
    ;;
    release)
        do-release
    ;;
    *)
    echo 'This script contains several useful functions for the libsylph devs.'
    ;;
esac