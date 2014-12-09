
#
#   make - Configuration
#

    CONFIG_NAME:=libgnomonic
    CONFIG_CODE:=c
    CONFIG_TYPE:=libstatic

    MAKE_BINARY:=bin
    MAKE_DOCUME:=doc
    MAKE_LIBRAR:=lib
    MAKE_OBJECT:=obj
    MAKE_SOURCE:=src
    MAKE_INPATH:=/usr/lib
    MAKE_CMCOPY:=cp
    MAKE_CMRMFL:=rm -f
    MAKE_CMRMDR:=rm -rf
    MAKE_CMMKDR:=mkdir -p
    MAKE_CC_BLD:=gcc
    MAKE_CPPBLD:=g++
    MAKE_STABLD:=ar
    MAKE_DOCBLD:=doxygen

    BUILD_FLAGS:=-Wall -funsigned-char -O3
    BUILD_LINKD:=-lm
    BUILD_SUBMD:=$(MAKE_LIBRAR)/libinter

#
#   make - Modules
#

    MAKE_MODULE:=$(foreach LIBS, $(BUILD_SUBMD), $(if $(findstring /lib/, $(LIBS) ), , $(LIBS) ) )

#
#   make - Auto-configuration
#

ifeq ($(CONFIG_TYPE),suite)
    MAKE_LIBSWAP:=../../
else
ifeq ($(CONFIG_TYPE),libcommon)
    MAKE_LIBSWAP:=../../
else
    MAKE_LIBSWAP:=
endif
endif
ifeq ($(CONFIG_TYPE),libstatic)
    MAKE_SUFFIX:=.a
else
ifeq ($(CONFIG_TYPE),libcommon)
    MAKE_SUFFIX:=.a
else
    MAKE_SUFFIX:=
endif
endif
ifeq ($(CONFIG_CODE),c)
ifeq ($(CONFIG_TYPE),libstatic)
    MAKE_LINKER:=$(MAKE_STABLD)
else
ifeq ($(CONFIG_TYPE),libcommon)
    MAKE_LINKER:=$(MAKE_STABLD)
else
    MAKE_LINKER:=$(MAKE_CC_BLD)
endif
endif
    MAKE_COMPIL:=$(MAKE_CC_BLD)
endif
ifeq ($(CONFIG_CODE),cpp)
ifeq ($(CONFIG_TYPE),libstatic)
    MAKE_LINKER:=$(MAKE_STABLD)
else
ifeq ($(CONFIG_TYPE),libcommon)
    MAKE_LINKER:=$(MAKE_STABLD)
else
    MAKE_LINKER:=$(MAKE_CPPBLD)
endif
endif
    MAKE_COMPIL:=$(MAKE_CPPBLD)
endif
    MAKE_OPTION:=$(BUILD_FLAGS) $(addprefix -I./$(MAKE_LIBSWAP), $(addsuffix /src, $(BUILD_SUBMD) ) )
ifeq ($(CONFIG_CODE),c)
    MAKE_OPTION:=$(MAKE_OPTION) -std=gnu99
else
ifeq ($(CONFIG_CODE),cpp)
    MAKE_OPTION:=$(MAKE_OPTION) -std=c++11
endif
endif
ifneq ($(OPENMP),false)
    MAKE_OPTION:=$(MAKE_OPTION) -fopenmp -D __OPENMP__
    BUILD_LINKD:=$(BUILD_LINKD) -lgomp
endif
    MAKE_BUILDD:=$(addprefix -l, $(subst lib, , $(notdir $(BUILD_SUBMD) ) ) ) $(BUILD_LINKD) $(addprefix -L./$(MAKE_LIBSWAP), $(addsuffix /bin, $(BUILD_SUBMD) ) )

#
#   make - Enumeration
#

    MAKE_SRCFILE:=$(wildcard $(MAKE_SOURCE)/*.$(CONFIG_CODE) )
    MAKE_OBJFILE:=$(addprefix $(MAKE_OBJECT)/, $(addsuffix .o, $(notdir $(basename $(MAKE_SRCFILE) ) ) ) )

#
#   make - Targets
#

ifeq ($(CONFIG_TYPE),suite)
    all:make-directories $(CONFIG_NAME)
    build:all
    modules:
    clean:make-clean
    clean-all:clean
    clean-modules:
else
ifeq ($(CONFIG_TYPE),libcommon)
    all:make-directories $(CONFIG_NAME)
    build:all
    modules:
    clean:make-clean
    clean-all:clean
    clean-modules:
else
    all:make-directories make-modules $(CONFIG_NAME)
    build:make-directories $(CONFIG_NAME)
    modules:make-modules
    clean:make-clean
    clean-all:make-clean make-clean-modules
    clean-modules:make-clean-modules
endif
endif
    documentation:make-directories make-documentation
    clean-documentation:make-clean-documentation
    install:make-install
    uninstall:make-uninstall

#
#   make - Directives
#

    $(CONFIG_NAME):$(MAKE_OBJFILE)
ifeq ($(CONFIG_TYPE),libstatic)
	$(MAKE_LINKER) rcs $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $^
else
ifeq ($(CONFIG_TYPE),libcommon)
	$(MAKE_LINKER) rcs $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $^
else
	$(MAKE_LINKER) -o $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $^ $(MAKE_BUILDD)
endif
endif

    $(MAKE_OBJECT)/%.o:$(MAKE_SOURCE)/%.$(CONFIG_CODE)
	$(MAKE_COMPIL) -c -o $@ $< $(MAKE_OPTION)

    make-modules:
	@$(foreach LIB, $(MAKE_MODULE), $(MAKE) -C $(LIB) all OPENMP=$(OPENMP) && ) true

    make-documentation:make-directories
	$(MAKE_DOCBLD)

#
#   make - Cleaning
#

    make-clean:
	$(MAKE_CMRMFL) $(MAKE_BINARY)/* $(MAKE_OBJECT)/*.o

    make-clean-modules:
	@$(foreach LIBS, $(MAKE_MODULE), $(MAKE) -C $(LIBS) clean-all && ) true

    make-clean-documentation:
	$(MAKE_CMRMDR) $(MAKE_DOCUME)/html

#
#   make - Implementation
#

    make-install:
	$(MAKE_CMCOPY) $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $(MAKE_INPATH)/$(CONFIG_NAME)$(MAKE_SUFFIX)

    make-uninstall:
	$(MAKE_CMRMFL) $(MAKE_INPATH)/$(CONFIG_NAME)$(MAKE_SUFFIX)

#
#   make - Directories
#

    make-directories:
	$(MAKE_CMMKDR) $(MAKE_BINARY) $(MAKE_DOCUME) $(MAKE_OBJECT)

