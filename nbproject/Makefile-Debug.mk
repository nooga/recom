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
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/RJGenerator.o \
	${OBJECTDIR}/global.o \
	${OBJECTDIR}/parser.o \
	${OBJECTDIR}/RJStateSet.o \
	${OBJECTDIR}/RJAutomaton.o \
	${OBJECTDIR}/RJStateMachine.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/regej

dist/Debug/GNU-Linux-x86/regej: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/regej ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/RJGenerator.o: nbproject/Makefile-${CND_CONF}.mk RJGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/RJGenerator.o RJGenerator.cpp

${OBJECTDIR}/global.o: nbproject/Makefile-${CND_CONF}.mk global.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/global.o global.cpp

${OBJECTDIR}/parser.o: nbproject/Makefile-${CND_CONF}.mk parser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/parser.o parser.cpp

${OBJECTDIR}/RJStateSet.o: nbproject/Makefile-${CND_CONF}.mk RJStateSet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/RJStateSet.o RJStateSet.cpp

${OBJECTDIR}/RJAutomaton.o: nbproject/Makefile-${CND_CONF}.mk RJAutomaton.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/RJAutomaton.o RJAutomaton.cpp

${OBJECTDIR}/RJStateMachine.o: nbproject/Makefile-${CND_CONF}.mk RJStateMachine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/RJStateMachine.o RJStateMachine.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/regej

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
