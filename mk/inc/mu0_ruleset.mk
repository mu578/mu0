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

ifeq ($(strip $(PLATFORM)),)
	$(error PLATFORM is not set)
endif

ifeq ($(strip $(ARCH)),)
	$(error ARCH is not set)
endif

ifeq ($(strip $(LOCAL_MODULE)),)
	$(error LOCAL_MODULE is not set)
endif

ifeq ($(strip $(LOCAL_MODULE_PATH)),)
	$(error LOCAL_MODULE_PATH is not set)
endif

ifeq ($(strip $(LOCAL_BUILDDIR)),)
	$(error LOCAL_BUILDDIR is not set)
endif

MU0_CMD_RMDIR     := rm -Rf
MU0_CMD_RMFILE    := rm -f
MU0_CMD_MKDIR     := mkdir -p
MU0_CMD_MV        := mv -f
MU0_CMD_CD        := cd
MU0_CMD_LNS       := ln -s
MU0_CMD_LS        := ls -la

MU0_BUILD_FILES   := ""
MU0_OBJ_FILES     := ""
MU0_MISC_FILES    := ""

all:

ifneq (,$(findstring macos_android, $(PLATFORM_VARIANT)))

rule_all:: rule_static rule_linker_cmds

rule_list_objects::

rule_objects::

rule_static:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "LOCAL_PATH      := "$(LOCAL_MODULE_PATH)"/mk" >  $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "include \044(CLEAR_VARS)"                     >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "LOCAL_SRC_FILES := "$(LOCAL_SRC_FILES)""      >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "LOCAL_MODULE    := "$(LOCAL_MODULE)""         >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "LOCAL_CFLAGS    := "$(LOCAL_CFLAGS)""         >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "LOCAL_LDLIBS    := "                          >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "include \044(BUILD_STATIC_LIBRARY)"           >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@$(NDK_BUILD)      $(NDK_ARGS)         APP_BUILD_SCRIPT=$(LOCAL_BUILDDIR)"/android-static.mk"

rule_shared:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "LOCAL_PATH      := "$(LOCAL_MODULE_PATH)"/mk" >  $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "include \044(CLEAR_VARS)"                     >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_SRC_FILES := "$(LOCAL_SRC_FILES)""      >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_MODULE    := "$(LOCAL_MODULE)""         >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_CFLAGS    := "$(LOCAL_CFLAGS)""         >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_LDFLAGS   := "$(LOCAL_LDFLAGS)""        >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "include \044(BUILD_SHARED_LIBRARY)"           >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@$(NDK_BUILD)      $(NDK_ARGS)         APP_BUILD_SCRIPT=$(LOCAL_BUILDDIR)"/android-shared.mk"

rule_list_cmds::
	$(eval MU0_BUILD_FILES :=$(call walk-dir-recursive, $(LOCAL_MODULE_PATH)/misc))
	$(eval MU0_MISC_FILES  :=$(filter %-main.c, $(MU0_BUILD_FILES)))

rule_objects_cmds::

rule_linker_cmds::
	-@i=1 ; for src_file in $(MU0_MISC_FILES); do \
		if [ -z "$${src_file}" ]; then \
			break; \
		fi; \
		echo "LOCAL_PATH      := "$(LOCAL_MODULE_PATH)"/mk"          >  $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		echo "include \044(CLEAR_VARS)"                              >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		echo "LOCAL_SRC_FILES := "$(LOCAL_SRC_FILES)""               >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		echo "LOCAL_SRC_FILES += "$${src_file}""                     >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		echo "LOCAL_MODULE    := "$$(basename $${src_file%.*}).cmd"" >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		echo "LOCAL_CFLAGS    := "$(LOCAL_CFLAGS)""                  >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		echo "LOCAL_LDFLAGS   := "$(LOCAL_LDFLAGS)""                 >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		echo "include \044(BUILD_EXECUTABLE)"                        >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		$(NDK_BUILD)       $(NDK_ARGS)                 APP_BUILD_SCRIPT=$(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk"; \
		((i = i + 1)) ; \
	done

rule_show_buildir::
	@$(MU0_CMD_LS) $(LOCAL_BUILDDIR)/android/local

else

rule_all:: rule_clean rule_buildir rule_objects rule_list_objects rule_list_cmds rule_objects_cmds rule_linker_cmds

rule_list_objects::
	$(eval MU0_BUILD_FILES := $(call walk-dir-recursive, $(LOCAL_BUILDDIR)))
	$(eval MU0_OBJ_FILES   := $(filter %.o, $(MU0_BUILD_FILES)))

rule_objects::
	-@for src_file in $(LOCAL_SRC_FILES); do \
		if [ -z "$${src_file}" ]; then \
			break; \
		fi; \
		base=$${src_file#"$(LOCAL_MODULE_PATH)/sdk/vendor/"}; \
		prefix=$${base%%/*}; \
		if [ "$${#prefix}" -le 3 ]; then \
			prefix=""; \
		else \
			prefix="$(LOCAL_MODULE)_$${prefix}_"; \
		fi; \
		name=$$(basename $${src_file}); \
		if case $${name} in $(LOCAL_MODULE)*) ;; *) false;; esac; then \
			visibility="-fvisibility=default"; \
		else \
			visibility="-fvisibility=hidden"; \
		fi; \
		if case $(PLATFORM) in mingw*) ;; *) false;; esac; then \
			visibility=$${visibility}; \
		else \
			visibility="-fpic "$${visibility}; \
		fi; \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)" <= '"$${name}"'"; \
		if case $(PLATFORM) in mingw*) ;; *) false;; esac; then \
			$(CC) $${visibility} $(LOCAL_CFLAGS) -c $${src_file} -o \
				$(LOCAL_BUILDDIR)/$${prefix}$$(basename $${src_file%.*}).o; \
		else \
			$(CC) $${visibility} $(LOCAL_CFLAGS) -c $${src_file} -o \
				$(LOCAL_BUILDDIR)/$${prefix}$$(basename $${src_file%.*})_$(ARCH).o; \
		fi; \
	done

rule_static:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= lib"$(LOCAL_MODULE).a
	-@if [ "$(ARCH)" = "fat" ]; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= Arch is "$(ARCH)" discarding."; \
	else \
		$(AR) -crv $(LOCAL_BUILDDIR)"/lib"$(LOCAL_MODULE)".a" $(MU0_OBJ_FILES); \
	fi

rule_shared:: rule_clean rule_buildir rule_objects rule_list_objects
	-@if [ "$(PLATFORM)" = "darwin" ]; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= 'lib"$(LOCAL_MODULE)"-1.0.0.dylib'"; \
		$(LD) -dynamiclib $(MU0_OBJ_FILES) \
			-install_name @rpath/lib$(LOCAL_MODULE).dylib \
			-compatibility_version 1.0 \
			-current_version       1.0.0 \
			-o $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dylib; \
		otool -L    $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dylib; \
		lipo  -info $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dylib; \
	elif [ "$(PLATFORM)" = "linux" ] || [ "$(PLATFORM)" = "freebsd" ]; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= 'lib"$(LOCAL_MODULE)".so.1.0.0'"; \
		$(LD) -shared $(MU0_OBJ_FILES) \
			-o $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).so.1.0.0; \
		ldd        $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).so.1.0.0; \
		objdump -p $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).so.1.0.0 | grep 'NEEDED'; \
		objdump -a $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).so.1.0.0; \
	elif case $(PLATFORM) in mingw*) ;; *) false;; esac; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= 'lib"$(LOCAL_MODULE)"-1.0.0.dll'"; \
		$(LD) -shared $(MU0_OBJ_FILES) \
			-o $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dll; \
		objdump -a $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dll; \
	fi

rule_list_cmds::
	$(eval MU0_BUILD_FILES :=$(call walk-dir-recursive, $(LOCAL_MODULE_PATH)/misc))
	$(eval MU0_MISC_FILES  :=$(filter %-main.c, $(MU0_BUILD_FILES)))

rule_objects_cmds::
	-@for src_file in $(MU0_MISC_FILES); do \
		if [ -z "$${src_file}" ]; then \
			break; \
		fi; \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= '"$$(basename $${src_file})"'"; \
		$(CC) $(LOCAL_CFLAGS) -c $${src_file} -o \
			$(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo; \
	done

rule_linker_cmds::
	-@if [ "$(ARCH)" = "fat" ]; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= Arch is "$(ARCH)" discarding."; \
	else \
		$(AR) -crv $(LOCAL_BUILDDIR)"/lib"$(LOCAL_MODULE)"_linker.a" $(MU0_OBJ_FILES); \
	fi;
	-@for src_file in $(MU0_MISC_FILES); do \
		if [ -z "$${src_file}" ]; then \
			break; \
		fi; \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= "$$(basename $${src_file%.*}).cmd; \
		if [ "$(ARCH)" = "fat" ]; then \
			$(LD) $(MU0_OBJ_FILES) \
				   $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo \
				-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).cmd; \
		else \
			if case $(PLATFORM) in linu*) ;; *) false;; esac; then \
				$(LD) -Wl,--whole-archive $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)_linker.a -Wl,--no-whole-archive \
					   $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo \
					-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).cmd; \
			else \
				$(LD) $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)_linker.a \
					   $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo \
					-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).cmd; \
			fi; \
		fi; \
	done

rule_show_buildir::
	@$(MU0_CMD_LS) $(LOCAL_BUILDDIR)

endif

rule_buildir::
	@$(MU0_CMD_MKDIR) $(LOCAL_BUILDDIR)

rule_clean::
	@$(MU0_CMD_RMDIR) $(LOCAL_BUILDDIR)
	@find .. -name ".DS_Store" -exec rm -f {} \;

# EOF