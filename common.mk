# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== USEFILE - the file containing the usage message for the application. 
USEFILE=

# Next lines are for C++ projects only

EXTRA_SUFFIXES+=cxx cpp

#===== LDFLAGS - add the flags to the linker command line.
LDFLAGS+=-lang-c++ -Y _gpp -std=c++11 -Wl,-E

#===== CCFLAGS - add the flags to the C compiler command line. 
CCFLAGS+=-O2 -Y _gpp -std=c++11 -Wp,-MMD,$(basename $@).d

#===== EXTRA_INCVPATH - a space-separated list of directories to search for include files.
EXTRA_INCVPATH+= \
	$(PROJECT_ROOT)/include  \
	$(QNX_TARGET)/usr/include

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+=$(PROJECT_ROOT)/src

#===== NAME - name of the project (default - name of project directory).
NAME=ese_festo

#===== EXTRA_CLEAN - additional files to delete when cleaning the project.
EXTRA_CLEAN+=*.d

include $(MKFILES_ROOT)/qmacros.mk
ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

-include *.d

include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

