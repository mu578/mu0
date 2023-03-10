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

# mu0_source.mk
#
# Copyright (C) 2023 mu578. All rights reserved.
#

define walk-dir-recursive
	$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk-dir-recursive, $(e)))
endef

define walk-dir
	$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(e))
endef

ifeq ($(strip $(MU0_ROOT_PATH)),)
$(error MU0_ROOT_PATH is not set)
endif

MU0_MODULE_NAME  ?= mu0
MU0_MODULE_PATH  ?= $(MU0_ROOT_PATH)
MU0_SOURCE_FILES ?= $(call walk-dir-recursive, $(MU0_MODULE_PATH)/source)
MU0_FILTER_FILES ?= $(filter %.c, $(MU0_SOURCE_FILES))

LOCAL_SRC_FILES += $(MU0_FILTER_FILES)
LOCAL_CFLAGS    += -I$(MU0_MODULE_PATH)

# EOF