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

# mu0.mk
#
# Copyright (C) 2023 mu578. All rights reserved.
#

LOCAL_MODULE      := mu0
LOCAL_MODULE_PATH := $(dir $(abspath ..))$(LOCAL_MODULE)
MU0_ROOT_PATH     := $(LOCAL_MODULE_PATH)

PLATFORM_VARIANT  := macos_macport.fat

include $(MU0_ROOT_PATH)/mk/inc/mu0_source.mk
include $(MU0_ROOT_PATH)/mk/inc/mu0_toolchain.mk
include $(MU0_ROOT_PATH)/mk/inc/mu0_ruleset.mk

all       :    rule_all
static    : rule_static
shared    : rule_shared
clean     :  rule_clean

distcheck : rule_all

# EOF