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
LOCAL_MODULE_PATH := ../../$(LOCAL_MODULE)
MU0_ROOT_PATH     := $(LOCAL_MODULE_PATH)

# PLATFORM_VARIANT := macos_xcode
# PLATFORM_VARIANT := macos_xcode.arm64
# PLATFORM_VARIANT := macos_xcode.x86_64
# PLATFORM_VARIANT := macos_xcode.fat
# PLATFORM_VARIANT := macos_macport
# PLATFORM_VARIANT := macos_macport.arm64
# PLATFORM_VARIANT := macos_macport.x86_64
# PLATFORM_VARIANT := macos_macport.fat

# PLATFORM_VARIANT := macos_ios
# PLATFORM_VARIANT := macos_ios.arm64
# PLATFORM_VARIANT := macos_ios.arm32
# PLATFORM_VARIANT := macos_ios.x86_64
PLATFORM_VARIANT := macos_ios.all

# PLATFORM_VARIANT := macos_android
# PLATFORM_VARIANT := macos_android.arm64
# PLATFORM_VARIANT := macos_android.arm32
# PLATFORM_VARIANT := macos_android.x86_64
# PLATFORM_VARIANT := macos_android.all

include $(MU0_ROOT_PATH)/mk/inc/mu0_function.mk
include $(MU0_ROOT_PATH)/mk/inc/mu0_source.mk
include $(MU0_ROOT_PATH)/mk/inc/mu0_toolchain.mk
include $(MU0_ROOT_PATH)/mk/inc/mu0_ruleset.mk

all       : rule_all
static    : rule_static
shared    : rule_shared
clean     : rule_clean
distcheck : rule_all rule_static rule_shared rule_show_buildir rule_clean

# EOF