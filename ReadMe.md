# mu0

Getting current toolchain Mac-M2 host:

```
>$ sudo port install clang-16
>$ sudo port install clang_select
>$ sudo port install libomp +universal
>$ sudo port select --set clang mp-clang-16

>$ sudo port install gcc12 +universal
>$ sudo port select --set gcc mp-gcc12
```

Makefile platform variants on Mac-M2 host:

```
# Default variant if empty; openmp disabled, no half-precision floating-point.
PLATFORM_VARIANT := macos_xcode
PLATFORM_VARIANT := macos_xcode.arm64
PLATFORM_VARIANT := macos_xcode.x86_64
PLATFORM_VARIANT := macos_xcode.fat

PLATFORM_VARIANT := macos_macport
PLATFORM_VARIANT := macos_macport.gcc
PLATFORM_VARIANT := macos_macport.arm64
PLATFORM_VARIANT := macos_macport.x86_64
PLATFORM_VARIANT := macos_macport.fat

# openmp disabled, no half-precision floating-point.
PLATFORM_VARIANT := macos_ios
PLATFORM_VARIANT := macos_ios.arm64
PLATFORM_VARIANT := macos_ios.arm32
PLATFORM_VARIANT := macos_ios.x86_64
PLATFORM_VARIANT := macos_ios.fat

# Expecting NDK install-path: ${project_root}/../toolchains/macos-android-ndk
PLATFORM_VARIANT := macos_android
PLATFORM_VARIANT := macos_android.arm64
PLATFORM_VARIANT := macos_android.arm32
PLATFORM_VARIANT := macos_android.x86_64
PLATFORM_VARIANT := macos_android.all

```

Getting current toolchain Ubuntu arm64 and x86_64 hosts:

```
>$ sudo apt-get install make
>$ sudo apt-get install clang
>$ sudo apt-get install libomp-dev
```

Or for a newer LLVM toolchain (recommended). llvm-14 is current on apt-get and does not support half-precision floating-point.

```
>$ sudo apt-get install make
>$ cd $HOME
>$ wget https://apt.llvm.org/llvm.sh
>$ sudo bash ./llvm.sh 16 all
>$ sudo rm -f /usr/bin/clang
>$ sudo ln -s /usr/bin/clang-16 /usr/bin/clang
>$ sudo rm -f /usr/bin/clang++
>$ sudo ln -s /usr/bin/clang++-16 /usr/bin/clang++
>$ sudo rm -f /usr/lib/libomp.so
>$ sudo ln -s /usr/lib/llvm-16/lib/libomp.so /usr/lib/libomp.so
```

Known to build c99/c11 pedandic on:
```
- macos   x86_64, arm64
- ios     x86_64, arm64, arm32
- ubuntu  x86_64, arm64
- android x86_64, arm64, arm32
- freebsd x86_64, arm64
- windows x86_64 (clang-msvc and clang-gnu)
```

# EOF