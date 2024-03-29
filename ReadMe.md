# mu0

In the realm of `mu0`, where tech meets friendliness, we're all about those cool C++ vibes. Imagine this: we're making things super smooth with seamless support for UTF-8 encoding and a rock-solid commitment to recognized specifications. But that's not all – we're adding a dash of OpenMP and OpenACC wizardry to level up our parallel processing game while keeping it cozy with standard C and those modern C++ twists.

Here's the scoop: `mu0` is not just your typical project; it's your trusty plain C library. We're mingling seamlessly with ARM64 and RISC-V architectures, making `mu0` the flexible sidekick for all your computing devices. And get this – behind the scenes for embedded C projects, `mu0` isn't just doing the job; it's building a laid-back ecosystem. Forget those usual toolkit boundaries; we're simplifying things, sprinkling C++ modern vibes into good ol' C, creating a tech universe that's not just smart but approachable. `mu0` is not just tech; it's a friendly face in the world of computing.

## brief

A cross-platform generalized Lib-c alike toolkit, carefully designed to target low power systems, truly type-strict, UTF-8, ISO, RFC, OpenMP, and OpenACC driven, no-optional (To note: the main design borrows quite a lot of C++ conceptual in terms of polymorphism, sure re-adapted within a plain embedded-C context: that's all the point).

Meanwhile, let's delve a bit into the enduring significance of OOP principles. Picture this – the foundational concepts of encapsulation, inheritance, polymorphism, and abstraction, `transcending the boundaries` of programming languages. Beyond the intricacies of coding, these principles serve as a lingua franca, fostering collaboration among developers.

The main ABI targets are ARM64 and RISC-V. Also, the host API provider and build system for all mu* projects. What we want to target at term:
```
macos, ios, ubuntu, android, freebsd, windows, nuttx, zephyr, bare-metal
+ kernel space build + firmware, and anything that runs on SoC.
```

Getting current toolchain Mac-M2 host:

```
>$ sudo port install clang-16
>$ sudo port install clang_select
>$ sudo port install libomp +universal
>$ sudo port select --set clang mp-clang-16

>$ sudo port install gcc13 +universal
>$ sudo port select --set gcc mp-gcc13
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