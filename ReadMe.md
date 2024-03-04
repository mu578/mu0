# mu0

**UNVEILING A RAD CROSS-PLATFORM PARADIGM**<br />
**---------------------------------------------**

**GET READY TO ENTER THE DIGITAL FRONTIER**<br />
Step into a realm where a meticulously crafted cross-platform paradigm transcends the ordinary definitions. This ain't your average toolkit; it's a philosophy intricately designed to embrace and excel in the unique challenges posed by low-power systems. At its core lies a truly type-strict design, not just for functionality but for orchestrating optimal performance across a diverse spectrum of computing environments.

**FEATURING RAD UTF-8 ENCODING**<br />
Central to this paradigm is a seamless support for `UTF-8` encoding, going beyond character representation. It's a robust solution, elegantly handling characters from various languages and scripts. This isn't just about data representation; it's about flawless transmission, vital for global applications with diverse linguistic requirements.

**ISO STANDARDS, WHERE COOL MEETS ROBUST**<br />
In alignment with `ISO` standards, this paradigm establishes a robust foundation built upon internationally recognized specifications. This commitment extends far beyond compliance checkboxes; it's a vow to deliver robustness, interoperability, and compatibility. In an ever-evolving technological landscape, adherence to `ISO` standards underscores a dedication to providing a stable and future-proof solution.

**STAYIN' RFC COMPLIANT, LIKE A BOSS**<br />
Incorporating compliance with `RFC` standards, this paradigm embodies a commitment to industry best practices and open standards. `RFCs` are more than guidelines; they are essential documents defining various aspects of internet protocols and technologies. By adhering to `RFC` standards, this paradigm ensures not only reliability but also compatibility in today's interconnected world.

**POWER UP WITH OPENMP TECHNOLOGY**<br />
Strategically leveraging `OpenMP` (Open Multi-Processing) technology, this paradigm elevates parallel processing capabilities. `OpenMP` provides standardized directives for parallel programming, empowering developers to unlock the potential of multi-core processors. It's more than parallelism; it's a strategic approach to efficient resource utilization, enhancing computational performance across a broad range of applications.

**BLAZIN' TRAILS WITH OPENACC INTEGRATION**<br />
Continuing its commitment to parallel programming, the paradigm embraces `OpenACC` (Open Accelerators). This integration transcends mere optimization; it's a deliberate effort to extend parallel programming capabilities to accelerators like GPUs. By doing so, the paradigm demonstrates adaptability to modern computing architectures, remaining at the forefront of computational methodologies.

**MODERN C++ VIBES IN STANDARD C, AND IT'S TOTALLY TUBULAR**<br />
This paradigm aspires to reintroduce modern C++ paradigms into the realm of standard C, transcending the limitations of traditional definitions. It's more than functionality; it's a conscious effort to bridge the gap and infuse modern programming practices into the foundations of standard C. Some base C++ object-oriented programming (OOP) paradigms can be re-adapted even in languages that do not support advanced OOP language constructs.

**COMPARABLE TO C++ RUNTIME LIBRARY, BUT WITH AN EDGE**<br />
Comparable to the `C++` runtime library, this paradigm shares similarities but with a notable distinction—it omits the algorithm and container components. This nuanced approach places a spotlight on fundamental functionalities, ensuring seamless integration with the underlying system. The focus is not just on compatibility but on delivering optimal performance tailored for low-power systems.

**BLAST TO THE PAST WITH ABI TARGETS**<br />
The primary ABI (Application Binary Interface) targets for this paradigm are `ARM64` and `RISC-V` architectures. This deliberate focus ensures compatibility and optimization for these architectures, catering to a wide range of computing devices and systems.

**EMBEDDED C PROJECTS, LIKE, WOW!**<br />
This paradigm serves as the backend for all `mu` embedded C projects, contributing to a cohesive ecosystem that transcends the boundaries of traditional toolkits. Beyond what's visible, it adheres to a philosophy that simplifies and reintroduces C++ modern paradigms into vanilla C. This unifying approach streamlines development, fosters consistency, and ensures that `mu` embedded C projects share a common foundation.

**BEYOND A TOOLKIT - A RAD TRANSCENDENT PHILOSOPHY**<br />
In summary, this paradigm, enriched by its support for `UTF-8`, adherence to `ISO` standards, `RFC` compliance, strategic integration of `OpenMP`, `OpenACC`, and modern C++ paradigms in standard C, stands as a versatile and forward-looking solution. It's not just about addressing the unique challenges of low-power systems; it's about introducing a paradigm that goes beyond the language itself—a philosophy that transcends traditional boundaries to reimagine and reintroduce powerful concepts into the fabric of computing.

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