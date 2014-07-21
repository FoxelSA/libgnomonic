
#
#   make - Configuration
#

	MAKE_NAME=libgnomonic
	MAKE_CODE=c
	MAKE_TYPE=libstatic

#
#   make - Structure
#

	MAKE_BINARY=bin
	MAKE_DOCUME=doc
	MAKE_LIBRAR=lib
	MAKE_OBJECT=obj
	MAKE_SOURCE=src

#
#   make - Source
#

	MAKE_SRCFILE=$(wildcard $(MAKE_SOURCE)/*.$(MAKE_CODE))
	MAKE_OBJFILE=$(addprefix $(MAKE_OBJECT)/, $(addsuffix .o, $(notdir $(basename $(MAKE_SRCFILE)))))

#
#   make - Compilation and linkage
#

ifeq ($(MAKE_CODE),c)
	MAKE_SRCCOMP=gcc
else
ifeq ($(MAKE_CODE),cpp)
	MAKE_SRCCOMP=g++
endif
endif
ifeq ($(MAKE_TYPE),application)
	MAKE_OBJCOMP=$(MAKE_SRCCOMP)
else
ifeq ($(MAKE_TYPE),libstatic)
	MAKE_OBJCOMP=ar
endif
endif
	MAKE_DOCCOMP=doxygen
    MAKE_GENOPTN=-Wall -funsigned-char -I./$(MAKE_LIBRAR)/libinter/src -O3
ifeq ($(MAKE_CODE),c)
	MAKE_SRCOPTN=-std=gnu99 $(MAKE_GENOPTN)
else
ifeq ($(MAKE_CODE),cpp)
	MAKE_SRCOPTN=-std=c++11 $(MAKE_GENOPTN)
endif
endif
	MAKE_OBJOPTN=

#
#   make - All
#

    all:libraries directories $(MAKE_NAME)

#
#   make - Binaries
#

    $(MAKE_NAME):$(MAKE_OBJFILE)
ifeq ($(MAKE_TYPE),application)
	$(MAKE_OBJCOMP) -o $(MAKE_BINARY)/$(MAKE_NAME) $^ $(MAKE_OBJOPTN)
else
ifeq ($(MAKE_TYPE),libstatic)
	$(MAKE_OBJCOMP) rcs $(MAKE_BINARY)/$(MAKE_NAME).a $^
endif
endif

#
#   make - Objects
#

    $(MAKE_OBJECT)/%.o:$(MAKE_SOURCE)/%.$(MAKE_CODE)
	$(MAKE_SRCCOMP) -c -o $@ $< $(MAKE_SRCOPTN)

#
#   make - Libraries
#

    libraries:
	$(MAKE) -C $(MAKE_LIBRAR)/libinter clean && $(MAKE) -C $(MAKE_LIBRAR)/libinter all

#
#   make - Documentation
#

    documentation:directories
	rm $(MAKE_DOCUME)/html -rf && $(MAKE_DOCCOMP)

#
#   make - Directories
#

    directories:
	mkdir -p $(MAKE_BINARY)
	mkdir -p $(MAKE_DOCUME)
	mkdir -p $(MAKE_OBJECT)

#
#   make - Cleaning
#

    clean:
	rm $(MAKE_BINARY)/* -f
	rm $(MAKE_OBJECT)/*.o -f

