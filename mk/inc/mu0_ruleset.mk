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

MU0_CMD_RMDIR   := rm -Rf
MU0_CMD_RMFILE  := rm -f
MU0_CMD_MKDIR   := mkdir -p
MU0_CMD_MV      := mv -f
MU0_CMD_CD      := cd
MU0_CMD_LNS     := ln -s
MU0_CMD_LS      := ls -la
MU0_CMD_GREP    := grep

MU0_OBJ_FILES   :=
MU0_MISC_FILES  :=

all:

ifneq (,$(findstring android, $(PLATFORM_VARIANT)))

rule_all:: rule_static rule_list_cmds rule_linker_cmds

rule_list_objects::

rule_objects::

rule_simple_objects::

rule_static:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "LOCAL_PATH      := "$(LOCAL_MODULE_PATH)"/mk" >  $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "include \044(CLEAR_VARS)"                     >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "LOCAL_SRC_FILES := "$(LOCAL_SRC_FILES)""      >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "LOCAL_MODULE    := "$(LOCAL_MODULE)""         >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "LOCAL_CFLAGS    := "$(LOCAL_CFLAGS)""         >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@echo "include \044(BUILD_STATIC_LIBRARY)"           >> $(LOCAL_BUILDDIR)"/android-static.mk"
	@$(NDK_BUILD) $(NDK_ARGS)              APP_BUILD_SCRIPT=$(LOCAL_BUILDDIR)"/android-static.mk"

rule_shared:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "LOCAL_PATH      := "$(LOCAL_MODULE_PATH)"/mk" >  $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "include \044(CLEAR_VARS)"                     >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_SRC_FILES := "$(LOCAL_SRC_FILES)""      >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_MODULE    := "$(LOCAL_MODULE)""         >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_CFLAGS    := "$(LOCAL_CFLAGS)""         >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "LOCAL_LDFLAGS   := "$(LOCAL_LDFLAGS)""        >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@echo "include \044(BUILD_SHARED_LIBRARY)"           >> $(LOCAL_BUILDDIR)"/android-shared.mk"
	@$(NDK_BUILD) $(NDK_ARGS)              APP_BUILD_SCRIPT=$(LOCAL_BUILDDIR)"/android-shared.mk"
	-@for ndk_arch in $(NDK_ARCH); do \
		$(NDK_OBJDUMP) -a $(LOCAL_BUILDDIR)/$${ndk_arch}/lib$(LOCAL_MODULE).so;                                                            \
		$(NDK_OBJDUMP) -p $(LOCAL_BUILDDIR)/$${ndk_arch}/lib$(LOCAL_MODULE).so | $(MU0_CMD_GREP) 'NEEDED';                                 \
	done

rule_list_cmds::
	$(eval MU0_BUILD_FILES :=$(call walk-dir-recursive, $(LOCAL_MODULE_PATH)/misc))
	$(eval MU0_MISC_FILES  :=$(filter %-main.c, $(MU0_BUILD_FILES)))

rule_objects_cmds::

rule_linker_cmds::
	-@i=1 ; for src_file in $(MU0_MISC_FILES); do \
		echo "LOCAL_PATH      := "$(LOCAL_MODULE_PATH)"/mk"          >  $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		echo "include \044(CLEAR_VARS)"                              >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		echo "LOCAL_SRC_FILES := "$(LOCAL_SRC_FILES)""               >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		echo "LOCAL_SRC_FILES += "$${src_file}""                     >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		echo "LOCAL_MODULE    := "$$(basename $${src_file%.*}).cmd"" >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		echo "LOCAL_CFLAGS    := "$(LOCAL_CFLAGS)""                  >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		echo "LOCAL_LDFLAGS   := "$(LOCAL_LDFLAGS)""                 >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		echo "include \044(BUILD_EXECUTABLE)"                        >> $(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		$(NDK_BUILD) $(NDK_ARGS)                       APP_BUILD_SCRIPT=$(LOCAL_BUILDDIR)"/android-cmd"$${i}".mk";                         \
		((i = i + 1)) ; \
	done

else ifneq (,$(findstring mingw, $(PLATFORM)))

rule_all:: rule_clean rule_buildir rule_objects rule_list_objects rule_list_cmds rule_objects_cmds rule_linker_cmds

rule_list_objects::
	$(eval MU0_OBJ_FILES := $(call filter-dir, %.o, $(LOCAL_BUILDDIR)))

rule_objects::
	-@for src_file in $(LOCAL_SRC_FILES); do base=$${src_file#"$(LOCAL_MODULE_PATH)/sdk/vendor/"};                                        \
		prefix=$${base%%/*}; if [ "$${#prefix}" -le 3 ]; then prefix=""; else prefix="$(LOCAL_MODULE)_$${prefix}_"; fi;                    \
		name=$$(basename $${src_file}); visibility="-fvisibility=hidden";                                                                  \
		if case $${name} in $(LOCAL_MODULE)*) ;; *) false;; esac; then visibility="-fvisibility=default"; fi;                              \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)" <= '"$${name}"'";                                                      \
		$(CC) $${visibility} $(LOCAL_CFLAGS) -c $${src_file} -o $(LOCAL_BUILDDIR)/$${prefix}$$(basename $${src_file%.*}).o;                \
	done

rule_simple_objects::
	-@for src_file in $(LOCAL_SRC_FILES); do                                                                                              \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)" <= '"$$(basename $${src_file})"'";                                     \
		$(CC) $(LOCAL_CFLAGS) -c $${src_file} -o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).o;                                         \
	done

rule_static:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= "$(LOCAL_MODULE).lib
	@$(AR) -crv $(LOCAL_BUILDDIR)"/"$(LOCAL_MODULE)".lib" $(MU0_OBJ_FILES)

rule_shared:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= '"$(LOCAL_MODULE)"-1.0.0.dll'"
	@$(LD) -shared $(MU0_OBJ_FILES) -o $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-1.0.0.dll
	@$(OBJDUMP) -a $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-1.0.0.dll
	@$(OBJDUMP) -p $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-1.0.0.dll | $(MU0_CMD_GREP) 'DLL Name'

rule_list_cmds::
	$(eval MU0_MISC_FILES := $(call filter-dir, %-main.c, $(LOCAL_MODULE_PATH)/misc))

rule_objects_cmds::
	-@for src_file in $(MU0_MISC_FILES); do                                                                                               \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= '"$$(basename $${src_file})"'";                                \
		$(CC) $(LOCAL_CFLAGS) -c $${src_file} -o $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo;                        \
	done

rule_linker_cmds::
	@$(AR) -crv $(LOCAL_BUILDDIR)"/"$(LOCAL_MODULE)"_linker.lib" $(MU0_OBJ_FILES)
	-@for src_file in $(MU0_MISC_FILES); do                                                                                               \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= "$$(basename $${src_file%.*}).exe;                             \
		$(LD) $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)_linker.lib $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo               \
			-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).exe;                                                                          \
	done

else

rule_all:: rule_clean rule_buildir rule_objects rule_list_objects rule_list_cmds rule_objects_cmds rule_linker_cmds

rule_list_objects::
	$(eval MU0_OBJ_FILES := $(call filter-dir, %.o, $(LOCAL_BUILDDIR)))

rule_objects::
	-@for src_file in $(LOCAL_SRC_FILES); do                                                                                              \
		base=$${src_file#"$(LOCAL_MODULE_PATH)/sdk/vendor/"};                                                                              \
		prefix=$${base%%/*};                                                                                                               \
		if [ "$${#prefix}" -le 3 ]; then                                                                                                   \
			prefix="";                                                                                                                      \
		else                                                                                                                               \
			prefix="$(LOCAL_MODULE)_$${prefix}_";                                                                                           \
		fi;                                                                                                                                \
		name=$$(basename $${src_file});                                                                                                    \
		if case $${name} in $(LOCAL_MODULE)*) ;; *) false;; esac; then                                                                     \
			visibility="-fpic -fvisibility=default";                                                                                        \
		else                                                                                                                               \
			visibility="-fpic -fvisibility=hidden";                                                                                         \
		fi;                                                                                                                                \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)" <= '"$${name}"'";                                                      \
		$(CC) $${visibility} $(LOCAL_CFLAGS) -c $${src_file} -o $(LOCAL_BUILDDIR)/$${prefix}$$(basename $${src_file%.*})_$(ARCH).o;        \
	done

rule_simple_objects::
	-@for src_file in $(LOCAL_SRC_FILES); do                                                                                              \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)" <= '"$$(basename $${src_file})"'";                                     \
		$(CC) -fpic $(LOCAL_CFLAGS) -c $${src_file} -o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*})_$(ARCH).o;                           \
	done

rule_static:: rule_clean rule_buildir rule_objects rule_list_objects
	@echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= lib"$(LOCAL_MODULE).a
	-@if [ "$(ARCH)" = "fat" ]; then                                                                                                      \
		echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= Arch is "$(ARCH)" discarding.";                                     \
	else                                                                                                                                  \
		$(AR) -crv $(LOCAL_BUILDDIR)"/lib"$(LOCAL_MODULE)".a" $(MU0_OBJ_FILES);                                                            \
	fi

rule_shared:: rule_clean rule_buildir rule_objects rule_list_objects
	-@if [ "$(PLATFORM)" = "darwin" ]; then                                                                                               \
		echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= 'lib"$(LOCAL_MODULE)"-1.0.0.dylib'";                                \
		$(LD) -dynamiclib $(MU0_OBJ_FILES) -install_name @rpath/lib$(LOCAL_MODULE).dylib -compatibility_version 1.0 -current_version 1.0.0 \
			-o $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dylib;                                                                            \
		echo ""; $(LIPO)  -info $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dylib;                                                          \
		echo ""; $(OTOOL) -L    $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)-1.0.0.dylib;                                                          \
	elif [ "$(PLATFORM)" = "linux" ] || [ "$(PLATFORM)" = "freebsd" ]; then                                                               \
		echo "["$(PLATFORM)"-"$(ARCH)"] Library : "$(LOCAL_MODULE)" <= 'lib"$(LOCAL_MODULE)".so.1.0.0'";                                   \
		$(LD) -shared $(MU0_OBJ_FILES) -o $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).so.1.0.0;                                                   \
		$(OBJDUMP) -a $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).so.1.0.0;                                                                       \
		$(OBJDUMP) -p $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE).so.1.0.0 | $(MU0_CMD_GREP) 'NEEDED';                                            \
	fi

rule_list_cmds::
	$(eval MU0_MISC_FILES := $(call filter-dir, %-main.c, $(LOCAL_MODULE_PATH)/misc))

rule_objects_cmds::
	-@for src_file in $(MU0_MISC_FILES); do \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= '"$$(basename $${src_file})"'";                               \
		$(CC) $(LOCAL_CFLAGS) -c $${src_file} -o $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo;                       \
	done

rule_linker_cmds::
	-@if [ "$(ARCH)" = "fat" ]; then \
		echo "["$(PLATFORM)"-"$(ARCH)"] Archive : "$(LOCAL_MODULE)" <= Arch is "$(ARCH)" discarding.";                                    \
	else                                                                                                                                 \
		$(AR) -crv $(LOCAL_BUILDDIR)"/lib"$(LOCAL_MODULE)"_linker.a" $(MU0_OBJ_FILES);                                                    \
	fi;                                                                                                                                  \
	for src_file in $(MU0_MISC_FILES); do                                                                                                \
		echo "["$(PLATFORM)"-"$(ARCH)"] Compile : "$(LOCAL_MODULE)-misc" <= "$$(basename $${src_file%.*}).cmd;                            \
		if [ "$(ARCH)" = "fat" ]; then                                                                                                    \
			$(LD) $(MU0_OBJ_FILES) $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo                                       \
				-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).cmd;                                                                      \
		else                                                                                                                              \
			if case $(PLATFORM) in linu*) ;; *) false;; esac; then                                                                         \
				$(LD) -Wl,--whole-archive $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)_linker.a -Wl,--no-whole-archive                              \
					$(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo                                                        \
					-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).cmd;                                                                   \
			else                                                                                                                           \
				$(LD) $(LOCAL_BUILDDIR)/lib$(LOCAL_MODULE)_linker.a $(LOCAL_BUILDDIR)/$(LOCAL_MODULE)-$$(basename $${src_file%.*}).lo       \
					-o $(LOCAL_BUILDDIR)/$$(basename $${src_file%.*}).cmd;                                                                   \
			fi;                                                                                                                            \
		fi;                                                                                                                               \
	done

endif

rule_buildir::
	@$(MU0_CMD_MKDIR) $(LOCAL_BUILDDIR)

rule_show_buildir::
	@$(MU0_CMD_LS) $(LOCAL_BUILDDIR)

rule_clean::
	@$(MU0_CMD_RMDIR) $(LOCAL_BUILDDIR)
	@find .. -name ".DS_Store" -exec rm -f {} \;

# EOF