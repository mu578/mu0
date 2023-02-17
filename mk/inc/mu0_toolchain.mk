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

# mu0_toolchain.mk
#
# Copyright (C) 2023 mu578. All rights reserved.
#

RMDIR            ?= rm -Rf
MV               ?= mv -f
CD               ?= cd
LNS              ?= ln -s

ifeq ($(strip $(ARCH)),)
ARCH             := $(shell uname -m)
endif

ifeq ($(strip $(PLATFORM)),)
PLATFORM         := $(shell uname -s | tr '[:upper:]' '[:lower:]')
endif
ifeq ($(strip $(PLATFORM_VARIANT)),)
PLATFORM_VARIANT := "macos_xcode"
endif

ifneq (,$(findstring darwin, $(PLATFORM)))
	ifneq (,$(findstring macos_xcode, $(PLATFORM_VARIANT)))
		XCODE_VERS   := $(shell xcodebuild -sdk -version | grep "\- macOS " | cut -d "-" -f 1 | tr -d '[:space:]')
		XCODE_PATH   := $(shell dirname `xcrun -f clang`)
		XCODE_SDK    := $(shell xcrun --show-sdk-path)
		CC           := $(XCODE_PATH)/clang
		AR           := $(XCODE_PATH)/ar

		LD           :=               \
			$(CC)                      \
			-arch $(ARCH)              \
			-mmacosx-version-min=10.13 \
			-isysroot $(XCODE_SDK)

		LOCAL_CFLAGS +=               \
			-x c                       \
			-std=c11                   \
			-arch $(ARCH)              \
			-mmacosx-version-min=10.13 \
			-isysroot $(XCODE_SDK)     \
			-Wall                      \
			-Wno-unused-function       \
			-Wno-newline-eof           \
			-pedantic
	endif
else

CC           := clang
AR           := ar

LD           :=  \
	$(CC)         \
	-arch $(ARCH) \
	-isysroot /

LOCAL_CFLAGS +=  \
	-x c          \
	-std=c11      \
	-arch $(ARCH) \
	-isysroot /

endif

# EOF