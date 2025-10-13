1. Copy `CMakeLists.example.txt` to `CMakeLists.txt`.
2. Change `<CROSS COMPILER>` (line 4) to the path to your cross compiler (e.g. `/home/user/opt/cross/bin/i686-elf-gcc`) - [How to install a Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler).
3. Run `./setup`
4. To compile and run the kernel, use `./recomprun`