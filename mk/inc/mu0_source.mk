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

ifeq ($(strip $(MU0_ROOT_PATH)),)
$(error MU0_ROOT_PATH is not set)
endif

LOCAL_SRC_FILES += $(call filter-dir-recursive, %.c, $(MU0_ROOT_PATH)/source)
LOCAL_CFLAGS    += -I$(MU0_ROOT_PATH)

# EOF