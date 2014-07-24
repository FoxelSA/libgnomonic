
#
#   make - Configuration - Bases
#

    MAKE_NAME:=libgnomonic
    MAKE_CODE:=c
    MAKE_TYPE:=libstatic

#
#   make - Configuration - Structures
#

    MAKE_BINARY:=bin
    MAKE_DOCUME:=doc
    MAKE_LIBRAR:=lib
    MAKE_OBJECT:=obj
    MAKE_SOURCE:=src

#
#   make - Configuration - Libraries
#

    MAKE_LINKLIB:=
    MAKE_INCLUDE:=$(MAKE_LIBRAR)/libinter

#
#   make - Configuration - Sources
#

    MAKE_SRCFILE:=$(wildcard $(MAKE_SOURCE)/*.$(MAKE_CODE) )
    MAKE_OBJFILE:=$(addprefix $(MAKE_OBJECT)/, $(addsuffix .o, $(notdir $(basename $(MAKE_SRCFILE) ) ) ) )

#
#   make - Configuration - Options
#

ifeq ($(MAKE_CODE),c)
    MAKE_SRCCOMP:=gcc
else
ifeq ($(MAKE_CODE),cpp)
    MAKE_SRCCOMP:=g++
endif
endif
ifeq ($(MAKE_TYPE),suite)
    MAKE_LIBSWAP:=../../
else
    MAKE_LIBSWAP:=
endif
ifeq ($(MAKE_TYPE),application)
    MAKE_OBJCOMP:=$(MAKE_SRCCOMP)
else
ifeq ($(MAKE_TYPE),libstatic)
    MAKE_OBJCOMP:=ar
endif
endif
    MAKE_DOCCOMP:=doxygen
    MAKE_GENOPTN:=-Wall -funsigned-char -O3 $(addprefix -I./$(MAKE_LIBSWAP), $(addsuffix /src, $(MAKE_INCLUDE) ) )
ifeq ($(MAKE_CODE),c)
    MAKE_SRCOPTN:=-std=gnu99 $(MAKE_GENOPTN)
else
ifeq ($(MAKE_CODE),cpp)
    MAKE_SRCOPTN:=-std=c++11 $(MAKE_GENOPTN)
endif
endif
    MAKE_OBJOPTN:=$(addprefix -l, $(subst lib, , $(notdir $(MAKE_INCLUDE) ) ) ) $(MAKE_LINKLIB) $(addprefix -L./, $(addsuffix /bin, $(MAKE_INCLUDE) ) )
    MAKE_DEPENDS:=$(foreach LIB, $(MAKE_INCLUDE), $(if $(findstring /lib/, $(LIB) ), , $(LIB) ) )

#
#   make - Build - Default
#

    all:directories libraries $(MAKE_NAME)

#
#   make - Build - Binaries
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
#   make - Build - Objects
#

    $(MAKE_OBJECT)/%.o:$(MAKE_SOURCE)/%.$(MAKE_CODE)
	$(MAKE_SRCCOMP) -c -o $@ $< $(MAKE_SRCOPTN)

#
#   make - Build - Libraries
#

    libraries:
	@$(foreach LIB, $(MAKE_DEPENDS), $(MAKE) -C $(LIB) clean && $(MAKE) -C $(LIB) all && ) true

#
#   make - Build - Documentation
#

    documentation:directories
	rm $(MAKE_DOCUME)/html -rf && $(MAKE_DOCCOMP)

#
#   make - Management - Directories
#

    directories:
	mkdir -p $(MAKE_BINARY)
	mkdir -p $(MAKE_DOCUME)
	mkdir -p $(MAKE_OBJECT)

#
#   make - Management - Cleaning
#

    clean:
	rm $(MAKE_BINARY)/* -f
	rm $(MAKE_OBJECT)/*.o -f

