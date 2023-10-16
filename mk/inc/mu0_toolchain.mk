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
		ifeq ("$(wildcard $(LOCAL_MODULE_PATH)/../toolchains/macos-android-ndk)", "")
			PLATFORM_VARIANT := macos_xcode
		endif
	endif
else
	ifeq ($(strip $(PLATFORM_VARIANT)),)
		PLATFORM_VARIANT    := $(PLATFORM)
	endif
endif

ifeq (,$(findstring darwin, $(PLATFORM)))
	ifneq (,$(findstring macos, $(PLATFORM_VARIANT)))
		PLATFORM_VARIANT    := $(PLATFORM)
	endif
endif

ifeq ($(strip $(LOCAL_BUILDDIR)),)
	ifneq (,$(findstring mingw, $(PLATFORM)))
		LOCAL_BUILDDIR      := ../_
	else
		LOCAL_BUILDDIR      := /tmp/build/$(basename $(PLATFORM_VARIANT))/$(LOCAL_MODULE)
	endif
endif

PLATFORM_ARCH             := -arch $(ARCH)

ifneq (,$(findstring darwin, $(PLATFORM)))
	ifneq (,$(findstring macos_macport, $(PLATFORM_VARIANT)))
		PORT_PATH           := /opt/local/bin
		CC                  := $(PORT_PATH)/clang
		AR                  := $(PORT_PATH)/ar
		OBJDUMP             := $(PORT_PATH)/objdump
		OTOOL               := $(PORT_PATH)/otool
		LIPO                := $(PORT_PATH)/lipo

		ifneq (,$(findstring .gcc, $(PLATFORM_VARIANT)))
			CC               := $(PORT_PATH)/gcc
			LOCAL_CFLAGS     += -Wno-format
			PLATFORM_ARCH    := -arch $(ARCH)
		else ifneq (,$(findstring .x86_64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch x86_64
			ARCH             := x86_64
		else ifneq (,$(findstring .arm64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch arm64
			ARCH             := arm64
		else ifneq (,$(findstring .fat, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			ifeq (,$(findstring x86_64, $(ARCH)))
				PLATFORM_ARCH := -arch $(ARCH) -arch x86_64
				ARCH          := fat
			else
				PLATFORM_ARCH := -arch $(ARCH)
			endif
		endif
		ifneq (,$(findstring .gcc, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			LD               :=          \
				$(CC)                     \
				$(PLATFORM_ARCH)          \
				-Wl,-ld_classic           \
				-fopenmp                  \
				-lm                       \
				-mmacosx-version-min=14.0
		else
			LD               :=          \
				$(CC)                     \
				$(PLATFORM_ARCH)          \
				-fopenmp=libomp           \
				-lm                       \
				-mmacosx-version-min=14.0
		endif

		LOCAL_CFLAGS        +=       \
			-x c                      \
			-std=c11                  \
			-O3                       \
			-fopenmp                  \
			$(PLATFORM_ARCH)          \
			-mmacosx-version-min=14.0 \
			-Wall                     \
			-Wno-unused-function      \
			-Wno-newline-eof          \
			-pedantic

	else ifneq (,$(findstring macos_xcode, $(PLATFORM_VARIANT)))
		XCODE_VERS          := $(shell xcodebuild -sdk -version | grep "\- macOS " | cut -d "-" -f 1 | tr -d '[:space:]')
		XCODE_PATH          := $(shell dirname `xcrun -f clang`)
		XCODE_SDK           := $(shell xcrun --show-sdk-path)
		CC                  := $(XCODE_PATH)/clang
		AR                  := $(XCODE_PATH)/ar
		OBJDUMP             := $(XCODE_PATH)/objdump
		OTOOL               := $(XCODE_PATH)/otool
		LIPO                := $(XCODE_PATH)/lipo
		ifneq (,$(findstring .x86_64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch x86_64
			ARCH             := x86_64
		else ifneq (,$(findstring .arm64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch arm64
			ARCH             := arm64
		else ifneq (,$(findstring .fat, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			ifeq (,$(findstring x86_64, $(ARCH)))
				PLATFORM_ARCH := -arch $(ARCH) -arch x86_64
				ARCH          := fat
			else
				PLATFORM_ARCH := -arch $(ARCH)
			endif
		endif
		LD                  :=        \
			$(CC)                      \
			$(PLATFORM_ARCH)           \
			-lm                        \
			-mmacosx-version-min=10.15 \
			-isysroot $(XCODE_SDK)

		LOCAL_CFLAGS        +=        \
			-x c                       \
			-std=c11                   \
			-O3                        \
			$(PLATFORM_ARCH)           \
			-mmacosx-version-min=10.15 \
			-isysroot $(XCODE_SDK)     \
			-Wall                      \
			-Wno-unused-function       \
			-Wno-newline-eof           \
			-pedantic

	else ifneq (,$(findstring macos_ios, $(PLATFORM_VARIANT)))
		XCODE_VERS          := $(shell xcodebuild -sdk -version | grep "iphoneos"  | cut -d "-" -f 1 | tr -d '[:space:]')
		XCODE_PATH          := $(shell dirname `xcrun -f clang`)
		XCODE_SDK           := 
		ifneq (,$(findstring .x86_64, $(PLATFORM_VARIANT)))
			XCODE_SDK        := $(shell xcrun --sdk iphonesimulator --show-sdk-path)
		else
			XCODE_SDK        := $(shell xcrun --sdk iphoneos --show-sdk-path)
		endif
		CC                  := $(XCODE_PATH)/clang
		AR                  := $(XCODE_PATH)/ar
		OBJDUMP             := $(XCODE_PATH)/objdump
		OTOOL               := $(XCODE_PATH)/otool
		LIPO                := $(XCODE_PATH)/lipo
		ifneq (,$(findstring .arm64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch arm64
			ARCH             := arm64
		else ifneq (,$(findstring .arm32, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch armv7s
			ARCH             := armv7s
		else ifneq (,$(findstring .x86_64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch x86_64
			ARCH             := x86_64
		else ifneq (,$(findstring .fat, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch arm64 -arch armv7 -arch armv7s
			ARCH             := fat
		else
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			PLATFORM_ARCH    := -arch arm64 -arch armv7s
			ARCH             := fat
		endif
		LD                  :=       \
			$(CC)                     \
			$(PLATFORM_ARCH)          \
			-lm                       \
			-framework CoreFoundation \
			-mios-version-min=8.0     \
			-isysroot $(XCODE_SDK)

		LOCAL_CFLAGS        +=       \
			-x c                      \
			-std=c11                  \
			-O3                       \
			$(PLATFORM_ARCH)          \
			-mios-version-min=8.0     \
			-isysroot $(XCODE_SDK)    \
			-Wall                     \
			-Wno-unused-function      \
			-Wno-newline-eof          \
			-pedantic

	else ifneq (,$(findstring macos_android, $(PLATFORM_VARIANT)))
		NDK_PATH            := $(LOCAL_MODULE_PATH)/../toolchains/macos-android-ndk
		NDK_BUILD           := $(NDK_PATH)/ndk-build
		NDK_OBJDUMP         := $(shell $(NDK_PATH)/ndk-which objdump)
		NDK_ARCH            :=
		ifneq (,$(findstring .arm64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			NDK_ARCH         := arm64-v8a
		else ifneq (,$(findstring .arm32, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			NDK_ARCH         := armeabi-v7a
		else ifneq (,$(findstring .x86_64, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			NDK_ARCH         := x86_64
		else ifneq (,$(findstring .all, $(PLATFORM_VARIANT)))
			PLATFORM_VARIANT := $(basename $(PLATFORM_VARIANT))
			NDK_ARCH         := arm64-v8a armeabi-v7a x86_64 x86
		else
			NDK_ARCH         := arm64-v8a armeabi-v7a
		endif
		NDK_ARGS            :=                   \
			NDK_PROJECT_PATH=$(LOCAL_MODULE_PATH) \
			NDK_OUT=$(LOCAL_BUILDDIR)             \
			NDK_LIBS_OUT=$(LOCAL_BUILDDIR)        \
			APP_ABI="$(NDK_ARCH)"                 \
			APP_STL=none                          \
			APP_PLATFORM=android-29

		LOCAL_LDFLAGS       += -llog -fopenmp=libomp -lm
		LOCAL_CFLAGS        +=                   \
			-x c                                  \
			-std=c11                              \
			-O3                                   \
			-fopenmp                              \
			-Wall                                 \
			-Wno-unused-function                  \
			-Wno-newline-eof                      \
			-pedantic

	endif

else ifneq (,$(findstring linux, $(PLATFORM)))
	CC              := clang
	AR              := ar
	OBJDUMP         := objdump
	OTOOL           :=
	LIPO            :=

	ifneq ("$(wildcard /usr/lib/libomp.so)", "")
		LD           :=         \
			$(CC)                \
			-isysroot /          \
			-fopenmp=libomp      \
			-lm

		LOCAL_CFLAGS +=         \
			-x c                 \
			-std=gnu11           \
			-O3                  \
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
			-O3                  \
			-isysroot /          \
			-Wall                \
			-Wno-unused-function \
			-Wno-newline-eof     \
			-pedantic

	endif

else ifneq (,$(findstring freebsd, $(PLATFORM)))
	CC           := clang
	AR           := ar
	OBJDUMP      := objdump
	OTOOL        :=
	LIPO         :=

	LD        :=            \
		$(CC)                \
		-isysroot /          \
		-fopenmp=libomp      \
		-lm

	LOCAL_CFLAGS +=         \
		-x c                 \
		-std=c11             \
		-O3                  \
		-isysroot /          \
		-Wall                \
		-Wno-unused-function \
		-Wno-newline-eof     \
		-pedantic

else ifneq (,$(findstring mingw, $(PLATFORM)))
	CC           := clang
	AR           := ar
	OBJDUMP      := objdump
	OTOOL        :=
	LIPO         :=

	LD           :=                   \
		$(CC)                          \
		-fuse-ld=lld                   \
		-fopenmp=libomp                \
		-target x86_64-pc-windows-msvc

	LOCAL_CFLAGS +=                   \
		-x c                           \
		-std=c11                       \
		-O3                            \
		-target x86_64-pc-windows-msvc \
		-Wall                          \
		-Wno-unused-function           \
		-Wno-newline-eof               \
		-Wno-language-extension-token  \
		-Wno-deprecated-declarations   \
		-pedantic

else

CC           := clang
AR           := ar
OBJDUMP      := objdump
OTOOL        :=
LIPO         :=

LD           :=     \
	$(CC)            \
	$(PLATFORM_ARCH) \
	-isysroot /      \
	-lm

LOCAL_CFLAGS +=     \
	-x c             \
	-std=c11         \
	-O3              \
	$(PLATFORM_ARCH) \
	-isysroot /

endif

# EOF