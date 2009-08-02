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
FC=
AS=

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Sylph/OS/LinuxFHSAppSelf.o \
	${OBJECTDIR}/src/Sylph/Core/StringBuffer.o \
	${OBJECTDIR}/src/Sylph/IO/PrintWriter.o \
	${OBJECTDIR}/test/ThisApp.o \
	${OBJECTDIR}/src/Sylph/Core/String.o \
	${OBJECTDIR}/test/Arguments.o \
	${OBJECTDIR}/test/HelloWorld.o \
	${OBJECTDIR}/src/Sylph.o \
	${OBJECTDIR}/src/Sylph/Core/ByteBuffer.o \
	${OBJECTDIR}/src/Sylph/IO/BufferedInputStream.o \
	${OBJECTDIR}/src/Sylph/Core/Application.o \
	${OBJECTDIR}/src/Sylph/OS/MacOSFHSAppSelf.o \
	${OBJECTDIR}/src/Sylph/Core/Object.o \
	${OBJECTDIR}/src/Sylph/Core/Vector.o \
	${OBJECTDIR}/src/Sylph/IO/BufferedOutputStream.o \
	${OBJECTDIR}/src/Sylph/Core/File.o \
	${OBJECTDIR}/src/Sylph/OS/MacOSAppSelf.o \
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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/libsylph.so

dist/Release/GNU-Linux-x86/libsylph.so: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -dynamiclib -install_name -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsylph.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Sylph/OS/LinuxFHSAppSelf.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/OS/LinuxFHSAppSelf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/OS
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/OS/LinuxFHSAppSelf.o src/Sylph/OS/LinuxFHSAppSelf.cpp

${OBJECTDIR}/src/Sylph/Core/StringBuffer.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/StringBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/StringBuffer.o src/Sylph/Core/StringBuffer.cpp

${OBJECTDIR}/src/Sylph/IO/PrintWriter.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/IO/PrintWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/IO
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/IO/PrintWriter.o src/Sylph/IO/PrintWriter.cpp

${OBJECTDIR}/test/ThisApp.o: nbproject/Makefile-${CND_CONF}.mk test/ThisApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/ThisApp.o test/ThisApp.cpp

${OBJECTDIR}/src/Sylph/Core/String.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/String.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/String.o src/Sylph/Core/String.cpp

${OBJECTDIR}/test/Arguments.o: nbproject/Makefile-${CND_CONF}.mk test/Arguments.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/Arguments.o test/Arguments.cpp

${OBJECTDIR}/test/HelloWorld.o: nbproject/Makefile-${CND_CONF}.mk test/HelloWorld.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/HelloWorld.o test/HelloWorld.cpp

${OBJECTDIR}/src/Sylph.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph.o src/Sylph.cpp

${OBJECTDIR}/src/Sylph/Core/ByteBuffer.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/ByteBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/ByteBuffer.o src/Sylph/Core/ByteBuffer.cpp

${OBJECTDIR}/src/Sylph/IO/BufferedInputStream.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/IO/BufferedInputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/IO
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/IO/BufferedInputStream.o src/Sylph/IO/BufferedInputStream.cpp

${OBJECTDIR}/src/Sylph/Core/Application.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Application.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Application.o src/Sylph/Core/Application.cpp

${OBJECTDIR}/src/Sylph/OS/MacOSFHSAppSelf.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/OS/MacOSFHSAppSelf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/OS
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/OS/MacOSFHSAppSelf.o src/Sylph/OS/MacOSFHSAppSelf.cpp

${OBJECTDIR}/src/Sylph/Core/Object.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Object.o src/Sylph/Core/Object.cpp

${OBJECTDIR}/src/Sylph/Core/Vector.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Vector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Vector.o src/Sylph/Core/Vector.cpp

${OBJECTDIR}/src/Sylph/IO/BufferedOutputStream.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/IO/BufferedOutputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/IO
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/IO/BufferedOutputStream.o src/Sylph/IO/BufferedOutputStream.cpp

${OBJECTDIR}/src/Sylph/Core/File.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/File.o src/Sylph/Core/File.cpp

${OBJECTDIR}/src/Sylph/OS/MacOSAppSelf.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/OS/MacOSAppSelf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/OS
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/OS/MacOSAppSelf.o src/Sylph/OS/MacOSAppSelf.cpp

${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/UncaughtExceptionHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/UncaughtExceptionHandler.o src/Sylph/Core/UncaughtExceptionHandler.cpp

${OBJECTDIR}/src/Sylph/Core/Array.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/Array.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/Array.o src/Sylph/Core/Array.cpp

${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/OS/LinuxBundleAppSelf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/OS
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/OS/LinuxBundleAppSelf.o src/Sylph/OS/LinuxBundleAppSelf.cpp

${OBJECTDIR}/src/Sylph/Core/HashMap.o: nbproject/Makefile-${CND_CONF}.mk src/Sylph/Core/HashMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Sylph/Core
	${RM} $@.d
	$(COMPILE.cc) -O2 -Isrc -Ideps/binreloc -Ideps/boost -Ideps/gc/include -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Sylph/Core/HashMap.o src/Sylph/Core/HashMap.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/libsylph.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
