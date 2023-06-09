# mu0

Getting current toolchain Mac-M2 host:

```
>$ sudo port install clang-16
>$ sudo port install clang_select
>$ sudo port install libomp +universal
>$ sudo port select --set clang mp-clang-16
```

Makefile platform variants on Mac-M2 host:

```
PLATFORM_VARIANT := macos_macport
PLATFORM_VARIANT := macos_macport.arm64
PLATFORM_VARIANT := macos_macport.x86_64
PLATFORM_VARIANT := macos_macport.fat

# Default openmp disabled, no half-precision floating-point.
PLATFORM_VARIANT := macos_xcode

# Expecting install-path mu0/../toolchains/android-ndk
PLATFORM_VARIANT := macos_android
PLATFORM_VARIANT := macos_android.arm64
PLATFORM_VARIANT := macos_android.armv7
PLATFORM_VARIANT := macos_android.x86_64
PLATFORM_VARIANT := macos_android.all

```

Getting current toolchain Ubuntu-arm64 host:

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

# EOF