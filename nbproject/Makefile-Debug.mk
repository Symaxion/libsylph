#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=

# Macros
CND_PLATFORM=GNU_C++0x-MacOSX
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/test/ThisApp.o \
	${OBJECTDIR}/src/Sylph/Core/String.o \
	${OBJECTDIR}/test/Arguments.o \
	${OBJECTDIR}/test/HelloWorld.o \
	${OBJECTDIR}/src/csylph/csylph.o \
	${OBJECTDIR}/src/Sylph.o \
	${OBJECTDIR}/src/Sylph/Core/Util.o \
	${OBJECTDIR}/src/Sylph/Core/Application.o \
	${OBJECTDIR}/src/Sylph/Core/Object.o \
	${OBJECTDIR}/src/Sylph/Core/Vector.o \
	${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o \
	${OBJECTDIR}/src/Sylph/Core/Array.o \
	${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o \
	${OBJECTDIR}/src/Sylph/Core/HashMap.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Llib -lboost -lcord -lgc -lpthread -lbinreloc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU_C++0x-MacOSX/libsylph.dylib

dist/Debug/GNU_C++0x-MacOSX/libsylph.dylib: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU_C++0x-MacOSX
	${LINK.cc} -dynamiclib -install_name libsylph.dylib -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsylph.dylib -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/test/ThisApp.o: nbproject/Makefile-${CND_CONF}.mk test/ThisApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/ThisApp.o test/ThisApp.cpp

${OBJECTDIR}/src/Sylph/Core/String.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/String.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/String.o src/Sylph/Core/String.cpp

${OBJECTDIR}/test/Arguments.o: nbproject/Makefile-${CND_CONF}.mk test/Arguments.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/Arguments.o test/Arguments.cpp

${OBJECTDIR}/test/HelloWorld.o: nbproject/Makefile-${CND_CONF}.mk test/HelloWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/HelloWorld.o test/HelloWorld.cpp

${OBJECTDIR}/src/csylph/csylph.o: nbproject/Makefile-${CND_CONF}.mk src/csylph/csylph.c 
	${MKDIR} -p ${OBJECTDIR}/src/csylph
	${RM} $@.d
	$(COMPILE.c) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/csylph/csylph.o src/csylph/csylph.c

${OBJECTDIR}/src/Sylph.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph.o src/Sylph.cpp

${OBJECTDIR}/src/Sylph/Core/Util.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Util.o src/Sylph/Core/Util.cpp

${OBJECTDIR}/src/Sylph/Core/Application.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Application.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Application.o src/Sylph/Core/Application.cpp

${OBJECTDIR}/src/Sylph/Core/Object.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Object.o src/Sylph/Core/Object.cpp

${OBJECTDIR}/src/Sylph/Core/Vector.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Vector.o src/Sylph/Core/Vector.cpp

${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/UncaughtExceptionHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o src/Sylph/Core/UncaughtExceptionHandler.cpp

${OBJECTDIR}/src/Sylph/Core/Array.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Array.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Array.o src/Sylph/Core/Array.cpp

${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/OS/LinuxBundleAppSelf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/OS
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o src/Sylph/OS/LinuxBundleAppSelf.cpp

${OBJECTDIR}/src/Sylph/Core/HashMap.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/HashMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -g -DSYLPH_DEBUG -D__GXX_EXPERIMENTAL_CXX0X__ -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/HashMap.o src/Sylph/Core/HashMap.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU_C++0x-MacOSX/libsylph.dylib

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
