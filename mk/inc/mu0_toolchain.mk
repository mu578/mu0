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

ifeq ($(strip $(LOCAL_MODULE)),)
	$(error LOCAL_MODULE is not set)
endif

ifeq ($(strip $(LOCAL_MODULE_PATH)),)
	$(error LOCAL_MODULE_PATH is not set)
endif

ifeq ($(strip $(ARCH)),)
ARCH                      := $(shell uname -m)
endif

ifeq ($(strip $(PLATFORM)),)
PLATFORM                  := $(shell uname -s | tr '[:upper:]' '[:lower:]')
endif

ifneq (,$(findstring darwin, $(PLATFORM)))
	ifeq ($(strip $(PLATFORM_VARIANT)),)
		PLATFORM_VARIANT    := macos_xcode
	endif
	ifneq (,$(findstring macos_macport, $(PLATFORM_VARIANT)))
		ifeq ("$(wildcard /opt/local/bin)", "")
			PLATFORM_VARIANT := macos_xcode
		endif
	endif
	ifneq (,$(findstring macos_android, $(PLATFORM_VARIANT)))
		PLATFORM_VARIANT    := macos_android
	endif
endif

LOCAL_BUILDDIR            := /tmp/build/$(PLATFORM)/$(LOCAL_MODULE)
ifneq (,$(findstring mingw, $(PLATFORM)))
	LOCAL_BUILDDIR         := ../tmp
endif

PLATFORM_ARCH             := -arch $(ARCH)

ifneq (,$(findstring darwin, $(PLATFORM)))
	ifneq (,$(findstring .x86_64, $(PLATFORM_VARIANT)))
		PLATFORM_VARIANT := $(basename  $(PLATFORM_VARIANT))
		PLATFORM_ARCH    := -arch x86_64
		ARCH             := x86_64
	else ifneq (,$(findstring .fat, $(PLATFORM_VARIANT)))
		PLATFORM_VARIANT := $(basename  $(PLATFORM_VARIANT))
		ifeq (,$(findstring x86_64, $(ARCH)))
			PLATFORM_ARCH := -arch $(ARCH) -arch x86_64
			ARCH          := fat
		else
			PLATFORM_ARCH := -arch $(ARCH)
		endif
	endif
	ifneq (,$(findstring macos_macport, $(PLATFORM_VARIANT)))
		PORT_PATH    := /opt/local/bin
		CC           := $(PORT_PATH)/clang
		AR           := $(PORT_PATH)/ar

		LD           :=              \
			$(CC)                     \
			$(PLATFORM_ARCH)          \
			-fopenmp=libomp           \
			-mmacosx-version-min=13.0

		LOCAL_CFLAGS +=              \
			-x c                      \
			-std=c11                  \
			-fopenmp                  \
			$(PLATFORM_ARCH)          \
			-mmacosx-version-min=13.0 \
			-Wall                     \
			-Wno-unused-function      \
			-Wno-newline-eof          \
			-pedantic

	else ifneq (,$(findstring macos_xcode, $(PLATFORM_VARIANT)))
		XCODE_VERS   := $(shell xcodebuild -sdk -version | grep "\- macOS " | cut -d "-" -f 1 | tr -d '[:space:]')
		XCODE_PATH   := $(shell dirname `xcrun -f clang`)
		XCODE_SDK    := $(shell xcrun --show-sdk-path)
		CC           := $(XCODE_PATH)/clang
		AR           := $(XCODE_PATH)/ar

		LD           :=               \
			$(CC)                      \
			$(PLATFORM_ARCH)           \
			-mmacosx-version-min=10.15 \
			-isysroot $(XCODE_SDK)

		LOCAL_CFLAGS +=               \
			-x c                       \
			-std=c11                   \
			$(PLATFORM_ARCH)           \
			-mmacosx-version-min=10.15 \
			-isysroot $(XCODE_SDK)     \
			-Wall                      \
			-Wno-unused-function       \
			-Wno-newline-eof           \
			-pedantic

	else ifneq (,$(findstring macos_android, $(PLATFORM_VARIANT)))
		ifeq ($(strip $(NDK_BUILD)),)
			ifeq ($(strip $(NDK_PATH)),)
				NDK_PATH := $(LOCAL_MODULE_PATH)/../toolchains/android-ndk
			endif
			NDK_BUILD   := $(NDK_PATH)/ndk-build
		endif
		ifeq ("$(wildcard $(NDK_BUILD))", "")
			$(error NDK_BUILD is not set)
		endif

		LOCAL_BUILDDIR := ../tmp
		LOCAL_LDFLAGS  += -fopenmp=libomp -lm

		LOCAL_CFLAGS   +=                    \
			-x c                              \
			-std=c11                          \
			-fopenmp                          \
			-Wall                             \
			-Wno-unused-function              \
			-Wno-newline-eof                  \
			-pedantic

		ifeq ($(strip $(NDK_ARGS)),)
			NDK_ARGS    :=                    \
				NDK_PROJECT_PATH=.             \
				NDK_LIBS_OUT=$(LOCAL_BUILDDIR) \
				NDK_OUT=$(LOCAL_BUILDDIR)      \
				NDK_TOOLCHAIN_VERSION=clang    \
				APP_PLATFORM=android-29
		endif
	endif

else ifneq (,$(findstring linux, $(PLATFORM)))
	CC              := clang
	AR              := ar

	ifneq ("$(wildcard /usr/lib/libomp.so)", "")
		LD           :=         \
			$(CC)                \
			-isysroot /          \
			-fopenmp=libomp      \
			-lm

		LOCAL_CFLAGS +=         \
			-x c                 \
			-std=gnu11           \
			-fopenmp             \
			-isysroot /          \
			-Wall                \
			-Wno-unused-function \
			-Wno-newline-eof     \
			-pedantic

	else
		LD           :=         \
			$(CC)                \
			-isysroot /          \
			-lm

		LOCAL_CFLAGS +=         \
			-x c                 \
			-std=gnu11           \
			-isysroot /          \
			-Wall                \
			-Wno-unused-function \
			-Wno-newline-eof     \
			-pedantic

	endif

else ifneq (,$(findstring freebsd, $(PLATFORM)))
	CC           := clang
	AR           := ar

	LD        :=            \
		$(CC)                \
		-isysroot /          \
		-fopenmp=libomp      \
		-lm

	LOCAL_CFLAGS +=         \
		-x c                 \
		-std=c11             \
		-isysroot /          \
		-Wall                \
		-Wno-unused-function \
		-Wno-newline-eof     \
		-pedantic

else ifneq (,$(findstring mingw, $(PLATFORM)))
	CC           := clang
	AR           := ar

	LD           :=                   \
		$(CC)                          \
		-fuse-ld=lld                   \
		-fopenmp=libomp                \
		-target x86_64-pc-windows-msvc

	LOCAL_CFLAGS +=                   \
		-x c                           \
		-std=c11                       \
		-target x86_64-pc-windows-msvc \
		-Wall                          \
		-Wno-unused-function           \
		-Wno-newline-eof               \
		-Wno-language-extension-token  \
		-pedantic

else

CC           := clang
AR           := ar

LD           :=     \
	$(CC)            \
	$(PLATFORM_ARCH) \
	-isysroot /      \
	-lm

LOCAL_CFLAGS +=     \
	-x c             \
	-std=c11         \
	$(PLATFORM_ARCH) \
	-isysroot /

endif

# EOF