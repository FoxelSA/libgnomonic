
    include Version

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
    MAKE_BNPATH:=/usr/lib
    MAKE_HDPATH:=/usr/include
    MAKE_CMCOPY:=cp
    MAKE_CMRMFL:=rm -f
    MAKE_CMRMRF:=rm -rf
    MAKE_CMMKDR:=mkdir -p
    MAKE_CMRMDR:=rmdir -p --ignore-fail-on-non-empty
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

    MAKE_MODULE:=$(foreach LIBS,$(BUILD_SUBMD),$(if $(findstring /lib/,$(LIBS)),,$(LIBS)))

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
ifeq ($(STATIC),true)
    MAKE_SUFFIX:=.a
else
    MAKE_SUFFIX:=.so
endif
else
ifeq ($(CONFIG_TYPE),libcommon)
    MAKE_SUFFIX:=.a
else
    MAKE_SUFFIX:=
endif
endif
ifeq ($(CONFIG_CODE),c)
ifeq ($(CONFIG_TYPE),libstatic)
ifeq ($(STATIC),true)
    MAKE_LINKER:=$(MAKE_STABLD)
else
    MAKE_LINKER:=$(MAKE_CC_BLD)
    MAKE_OPTION:=$(MAKE_OPTION) -fpic
endif
else
ifeq ($(CONFIG_TYPE),libcommon)
    MAKE_LINKER:=$(MAKE_STABLD)
else
    MAKE_LINKER:=$(MAKE_CC_BLD)
endif
endif
    MAKE_HEADEX:=h
    MAKE_COMPIL:=$(MAKE_CC_BLD)
    MAKE_OPTION:=$(MAKE_OPTION) -std=gnu99
else
ifeq ($(CONFIG_CODE),cpp)
ifeq ($(CONFIG_TYPE),libstatic)
ifeq ($(STATIC),true)
    MAKE_LINKER:=$(MAKE_STABLD)
else
    MAKE_LINKER:=$(MAKE_CPPBLD)
    MAKE_OPTION:=$(MAKE_OPTION) -fpic
endif
else
ifeq ($(CONFIG_TYPE),libcommon)
    MAKE_LINKER:=$(MAKE_STABLD)
else
    MAKE_LINKER:=$(MAKE_CPPBLD)
endif
endif
    MAKE_HEADEX:=hpp
    MAKE_COMPIL:=$(MAKE_CPPBLD)
    MAKE_OPTION:=$(MAKE_OPTION) -std=c++11
endif
endif
ifneq ($(OPENMP),false)
    MAKE_OPTION:=$(MAKE_OPTION) -fopenmp -D __OPENMP__
    BUILD_LINKD:=$(BUILD_LINKD) -lgomp
endif
    MAKE_OPTION:=$(MAKE_OPTION) $(BUILD_FLAGS) $(addprefix -I./$(MAKE_LIBSWAP),$(addsuffix /src,$(BUILD_SUBMD)))
    MAKE_BUILDD:=$(MAKE_BUILDD) $(addprefix -l,$(subst lib,,$(notdir $(BUILD_SUBMD)))) $(BUILD_LINKD) $(addprefix -L./$(MAKE_LIBSWAP),$(addsuffix /bin,$(BUILD_SUBMD)))

ifeq ($(CONFIG_TYPE),libstatic)
    MAKE_VERSIO:=$(VER_MAJ).$(VER_MIN)$(if $(filter $(VER_REV),0),,.$(VER_REV))
    MAKE_HDPATH:=$(MAKE_HDPATH)/$(subst lib,,$(CONFIG_NAME))/$(MAKE_VERSIO)
endif

#
#   make - Enumeration
#

    MAKE_SRCFILE:=$(wildcard $(MAKE_SOURCE)/*.$(CONFIG_CODE))
    MAKE_OBJFILE:=$(addprefix $(MAKE_OBJECT)/,$(addsuffix .o,$(notdir $(basename $(MAKE_SRCFILE)))))

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
ifneq ($(STATIC),false)
	$(MAKE_LINKER) rcs $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $^
else
	$(MAKE_LINKER) -shared -Wl,-soname,$(CONFIG_NAME)$(MAKE_SUFFIX).$(MAKE_VERSIO) -o $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $^
endif
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
	$(MAKE_CMRMRF) $(MAKE_DOCUME)/html

#
#   make - Implementation
#

    make-install:
ifeq ($(CONFIG_TYPE),libstatic)
	$(MAKE_CMCOPY) $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $(MAKE_BNPATH)/$(CONFIG_NAME)$(MAKE_SUFFIX).$(MAKE_VERSIO)
	$(MAKE_CMMKDR) $(MAKE_HDPATH)
	$(MAKE_CMCOPY) $(addprefix $(MAKE_SOURCE)/,$(notdir $(wildcard $(MAKE_SOURCE)/*.$(MAKE_HEADEX)))) $(MAKE_HDPATH)
else
	$(MAKE_CMCOPY) $(MAKE_BINARY)/$(CONFIG_NAME)$(MAKE_SUFFIX) $(MAKE_BNPATH)/$(CONFIG_NAME)$(MAKE_SUFFIX)
endif

    make-uninstall:
ifeq ($(CONFIG_TYPE),libstatic)
	$(MAKE_CMRMFL) $(addprefix $(MAKE_HDPATH)/,$(notdir $(wildcard $(MAKE_SOURCE)/*.$(MAKE_HEADEX))))
	$(MAKE_CMRMDR) $(MAKE_HDPATH)
	$(MAKE_CMRMFL) $(MAKE_BNPATH)/$(CONFIG_NAME)$(MAKE_SUFFIX).$(MAKE_VERSIO)
else
	$(MAKE_CMRMFL) $(MAKE_BNPATH)/$(CONFIG_NAME)$(MAKE_SUFFIX)
endif

#
#   make - Directories
#

    make-directories:
	$(MAKE_CMMKDR) $(MAKE_BINARY) $(MAKE_DOCUME) $(MAKE_OBJECT)

