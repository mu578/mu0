#
# # -*- coding: utf-8, tab-width: 3 -*-

#                                                           ___                                            #
#                                                          / _ \                                           #
#                                            _   _  _   _ | | | |                                          #
#                                           | | | || | | || | | |                                          #
#                                           | |_| || |_| || |_| |                                          #
#                                           | ._,_| \___/  \___/                                           #
#                                           | |                                                            #
#                                           |_|                                                            #

# mu0_ruleset.mk
#
# Copyright (C) 2023 mu578. All rights reserved.
#

ifeq ($(strip $(LOCAL_MODULE)),)
$(error LOCAL_MODULE is not set)
endif

ifeq ($(strip $(LOCAL_MODULE_PATH)),)
$(error LOCAL_MODULE_PATH is not set)
endif

LOCAL_BUILDDIR     := /tmp/build/$(PLATFORM)
ifneq (,$(findstring mingw, $(PLATFORM)))
	LOCAL_BUILDDIR  := ../build/$(PLATFORM)
endif

MU0_CMD_RMDIR      := rm -Rf
MU0_CMD_MKDIR      := mkdir -p
MU0_CMD_MV         := mv -f
MU0_CMD_CD         := cd
MU0_CMD_LNS        := ln -s
MU0_CMD_LS         := ls -la

MU0_BUILD_FILES    := ""
MU0_OBJ_FILES      := ""
MU0_MISC_FILES     := ""

all:

rule_all:: rule_clean rule_buildir rule_objects rule_list_objects rule_list_cmds rule_objects_cmds rule_link_cmds

rule_static:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= "lib$(LOCAL_MODULE).a
	@$(AR) -crv $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).a $(MU0_OBJ_FILES) 2>/dev/null

rule_shared:: rule_clean rule_buildir rule_objects rule_list_objects
	-@if [ "$(PLATFORM)" = "darwin" ]; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= "lib$(LOCAL_MODULE)-1.0.0.dylib; \
		$(LD) $(LOCAL_LDFLAGS) -dynamiclib $(MU0_OBJ_FILES) \
			-install_name @rpath/lib$(LOCAL_MODULE).dylib \
			-compatibility_version 1.0 \
			-current_version       1.0.0 \
			-o $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dylib; \
	fi

rule_list_cmds::
	$(eval MU0_BUILD_FILES :=$(call walk-dir-recursive, $(LOCAL_MODULE_PATH)/misc))
	$(eval MU0_MISC_FILES  :=$(filter %-main.c, $(MU0_BUILD_FILES)))

rule_objects_cmds::
	-@for src_file in $(MU0_MISC_FILES); do \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= "$$(basename $${src_file}); \
		$(CC) $(LOCAL_CFLAGS) -c $${src_file} -o \
			$(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).o; \
	done

rule_link_cmds::
	-@for src_file in $(MU0_MISC_FILES); do \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= "$$(basename $${src_file%.*}).cmd; \
		$(LD) $(LOCAL_LDFLAGS) $(MU0_OBJ_FILES) $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).o \
			-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).cmd; \
	done

rule_list_objects::
	$(eval MU0_BUILD_FILES := $(call walk-dir-recursive, $(LOCAL_BUILDDIR)))
	$(eval MU0_OBJ_FILES   := $(filter %.o, $(MU0_BUILD_FILES)))

rule_buildir::
	@$(MU0_CMD_MKDIR) $(LOCAL_BUILDDIR)

rule_objects::
	-@for src_file in $(LOCAL_SRC_FILES); do \
		base=$${src_file#"$(LOCAL_MODULE_PATH)/sdk/vendor/"}; \
		prefix=$${base%%/*}; \
		if [ "$${#prefix}" -le 3 ]; then \
			prefix=""; \
		else \
			prefix="$(LOCAL_MODULE)_$${prefix}_"; \
		fi; \
		name=$$(basename $${src_file}); \
		visibility="-fpic -fvisibility=default"; \
		if case $(PLATFORM) in mingw*) ;; *) false;; esac; then \
			visibility="-fvisibility=default"; \
		fi; \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)" <= "$${name}; \
		$(CC) $${visibility} $(LOCAL_CFLAGS) -c $${src_file} -o \
			$(LOCAL_BUILDDIR)/$${prefix}$$(basename $${src_file%.*})_$(ARCH).o; \
	done

rule_show_buildir::
	@$(MU0_CMD_LS) $(LOCAL_BUILDDIR)

rule_clean::
	@$(MU0_CMD_RMDIR) $(LOCAL_BUILDDIR)
	@find .. -name ".DS_Store" -exec rm -f {} \;

# EOF