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

LOCAL_MODULE := mu0

include mk/mu0_source.mk
include mk/mu0_toolchain.mk
include mk/mu0_ruleset.mk

all:   rule_all
all:   rule_all
clean: rule_clean

# EOF