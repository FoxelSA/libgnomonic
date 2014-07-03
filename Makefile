
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
ifeq ($(MAKE_CODE),c)
	MAKE_SRCOPTN=-Wall -funsigned-char -std=gnu99 -O3
else
ifeq ($(MAKE_CODE),cpp)
	MAKE_SRCOPTN=-Wall -funsigned-char -std=c++11 -O3
endif
endif
	MAKE_OBJOPTN=

#
#   make - All
#

    all:directories $(MAKE_NAME)

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

