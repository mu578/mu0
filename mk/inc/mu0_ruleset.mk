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

LOCAL_BUILDDIR    := /tmp/build/$(PLATFORM)

BUILD_FILES       :=
OBJECTS_FILES     :=
MISC_FILES        :=

all:

rule_all:: rule_clean rule_buildir rule_objects rule_list_objects rule_list_cmds rule_objects_cmds rule_link_cmds

rule_static:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= "lib$(LOCAL_MODULE).a
	@$(AR) -crv $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).a $(OBJECTS_FILES) 2>/dev/null

rule_shared:: rule_clean rule_buildir rule_objects rule_list_objects
	-@if [ "$(PLATFORM)" = "Darwin" ]; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= "lib$(LOCAL_MODULE).dylib; \
		$(LD) -dynamiclib $(OBJECTS_FILES) \
			-install_name @rpath/lib$(LOCAL_MODULE).dylib \
			-compatibility_version 1.0 \
			-current_version       1.0.0 \
			-o $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).dylib; \
	fi

rule_list_cmds::
	$(eval BUILD_FILES :=$(call walk-dir-recursive, $(LOCAL_MODULE_PATH)/misc))
	$(eval MISC_FILES  :=$(filter %-main.c, $(BUILD_FILES)))

rule_objects_cmds::
	-@for src_file in $(MISC_FILES); do \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= "$$(basename $${src_file}); \
		$(CC) $(LOCAL_CFLAGS) -c $${src_file} -o \
			$(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).o; \
	done

rule_link_cmds::
	-@for src_file in $(MISC_FILES); do \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= "$$(basename $${src_file%.*}).cmd; \
		$(LD) $(OBJECTS_FILES) $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).o \
			-o $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).cmd; \
	done

rule_list_objects::
	$(eval BUILD_FILES   := $(call walk-dir-recursive, $(LOCAL_BUILDDIR)))
	$(eval OBJECTS_FILES := $(filter %.o, $(BUILD_FILES)))

rule_buildir::
	@mkdir -p $(LOCAL_BUILDDIR)

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
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)" <= "$${name}; \
		$(CC) $${visibility} $(LOCAL_CFLAGS) -c $${src_file} -o \
			$(LOCAL_BUILDDIR)/$${prefix}$$(basename $${src_file%.*})_$(ARCH).o; \
	done

rule_clean::
	@$(RMDIR) $(LOCAL_BUILDDIR)
	@find .. -name ".DS_Store" -exec rm -f {} \;

# EOF