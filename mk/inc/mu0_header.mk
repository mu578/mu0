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

# mu0_header.mk
#
# Copyright (C) 2023 mu578. All rights reserved.
#

ifeq ($(strip $(MU0_ROOT_PATH)),)
$(error MU0_ROOT_PATH is not set)
endif

MU0_MODULE_NAME ?= mu0
MU0_MODULE_PATH ?= $(MU0_ROOT_PATH)
LOCAL_CFLAGS    += -I$(MU0_MODULE_PATH)

# EOF