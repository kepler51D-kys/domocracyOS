Create a `cross_compiler.cmake` file with the following contents:
```cmake
set(CMAKE_C_COMPILER /path/to/cross/compiler)
```
Replace `/path/to/cross/compiler` with the path to your cross compiler (e.g. `/home/user/opt/cross/bin/i686-elf-gcc`) - [How to install a Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler).

Then, run `./setup`.

Every time you want to compile everything and start the kernel in QEMU, use `./recomprun`.