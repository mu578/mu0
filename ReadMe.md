# mu0

Current toolchain Mac-M2 host:

```
>$ sudo port install clang-16
>$ sudo port install clang_select
>$ sudo port install libomp +universal
>$ sudo port select --set clang mp-clang-16
```

Current toolchain Ubuntu-arm64 host:

```
>$ sudo apt-get install make
>$ sudo apt-get install clang
>$ sudo apt-get install libomp-dev
```

or for a newer LLVM toolchain (recommended). 
llvm-14 is current on apt-get and does not support half-precision floating-point.

```
>$ sudo apt-get install make
>$ cd $HOME
>$ wget https://apt.llvm.org/llvm.sh
>$ sudo bash ./llvm.sh 16 all
>$ sudo rm -f /usr/bin/clang
>$ sudo ln -s /usr/bin/clang-16 /usr/bin/clang
>$ sudo rm -f /usr/lib/libomp.so
>$ sudo ln -s /usr/lib/llvm-16/libomptarget.so.16 /usr/lib/libomp.so
```

# EOF