# 7. Linking

## 7.1 Compiler Drivers
+ **Compiler Drivers**: Invokes the whole preprocessor, compiler, assembler, linker.

  + The term defines the whole compiling process, which eventually creates an executable object file.

  + Example: `gcc -Og -o prog main.c sum.c` which outputs an executable.

  + It comprises of translators, linker and loader (not dynamic linker)

    + Translators
      + translates source code(.c or .h) into (relocatable) object file(.o).
    + (Static) Linker
      + Links the object files(.o) and static libraries(.a) into executable file.

  + Example of how the compiler works in few steps.

    + main.c -> main.i -> main.s -> main.o -> prog
      1. main.c -> main.i
          C preprocessor: c file into intermediate file
          intermediate file removes macros and comments
          `cpp main.c /tmp/main.i`

      2. main.i -> main.s
          C compiler: intermediate file into assembly file
          `cc1 /tmp/main.i -Og -o /tmp/main.s`

      3. main.s -> main.o
          Assembler: assembly file into relocatable object file(.o)
          `as -o /tmp/main.o /tmp/main.s`

      4. main.o + sum.o -> prog
          Linker: system object file into executable object file
          `ld -o prog /tmp/main.o /tmp/sum.o`



## 7.2 Static Linking

+ **Static Linker**: relocatable object files(.o) -> executable object file
+ Why Linkers?
  - **Modularity**
    -  Programs can be written in set of smaller source files.
  - **Efficiency**
    - Time: Separate compilation
    - Space: Libraries
+ Linker performs 2 tasks
  1.  ***Symbol resolution***
      * **Symbol**
        * Each symbol represent a function, global variable or a static variable (variables that acts as field of functions)
        * Symbol definitions are stored (by compiler) in a symbol table.
      * Symbol resolution maps symbol *reference* to symbol *definition*. Definition of the symbol is where the function or variable is declared. The reference of the symbol is where the symbol is used.
  2.  ***Relocation***
      * Merges separate code and data sections into single section.
      * Relocates symbols from their relative locations to their final absolute locations in executable.
      * Updates all reference to these new symbol positions.



## 7.3 Object Files

+ ***Relocatable object file(.o)***
  Contains binary code and data that is used to make executable object files.

+ ***Executable object file***
   Binary code and data that can be copied directly into memory.

+ ***Shared object file(.so)***

   Special type of relocatable object file that can be loaded into memory and linked dynamically.



## 7.4 Relocatable Object Files

The following are the list of sections in the ELF

+ **ELF header**
  Word size, byte ordering...

+ **Segment header table**

  Page size, virtual address and memory segments.

+ **.text**
  Machine code

+ **.rodata**
  Read only data

+ **.data**
  Initialize global and static variables. Note that local variables are stored in the stack in run time

+ **.bss**
  Uninitialized global and static variables. Occupies no actual space in object file. (Better Save Space!)

+ **.symtab**
  Information about functions and global variables that are referenced in the program.

+ **.rel.text**

  A list of locations in the .text section that needs to be modified when linker combines object files.

+ **.rel.data**

  Relocation information for any global variables that are referenced or defined by the module.

+ **.debug**(-g)

  A debugging symbol table.

+ **.line**(-g)

  A mapping between lines in original C file and machine code in .text section.

+ **.strtab**

  A string table for symbol tables in .symtab and .debug.

+ **Section header table**

  The locations and sizes of the various sections.




## 7.5 Symbols and Symbol Tables

+ ***Global symbols***

  Defined in module *m* and that can be referenced by other modules. Includes **non-static functions** and **non-static global variables**.

+ ***External symbols***

  Global Symbols referenced in module *m* but defined in other modules.

+ ***Local Symbols***

  Defined and referenced exclusively by module *m*. Includes **static functions** and **static global variables**. Note that these do not refer to local variables.


## 7.6 Symbol Resolution

* Strong and weak symbols
  * ***Strong symbols***: functions and initialized globals
  * ***Weak symbols***: uninitialized globals

* Symbol rules
  1. Multiple strong symbols are not allowed. -> ERROR
  2. Given both strong symbol and weak symbol, choose the strong symbol.
  3. Given multiple weak symbols, peak arbitrary. -> Dangerous!!

* Linking with static libraries

  * **Archive**: Collection of concatenated relocatable object files storing static libraries.

  * Resolving reference conflicts with linkers

    In the command, the linker reads from left to right. So, the right archive must solve dependencies of the left side.

    ```
    1. scan .o files and .a files in the command line order
    2. During scan, keep list of unresolved references.
    3. As each new .o files or .a file is seen, resolve references if possible.
    4. If exists unresolved file at the end -> ERROR
    ```

* Disadvantages of static library

  * Duplication in stored executables
  * Duplication in the running executables
  * Minor fixes need relinking



## 7.7 Relocation

After resolution step, it has associated each symbol reference with exactly one symbol definition.

* Relocation step

  1. Relocating sections and symbol definitions

     Linker merges all the section of the same type into a new aggregate section of the same type (Ex .data sections are merged into one section). Then, linker assigns run-time memory address to new aggregated sections and symbols.

  2. Relocating symbol references within sections

     Linker modifies every symbol references in the code and data sections so that they point to the correct run-time addresses.

* **Relocation Entries**

  * Relocation entry tells linker, how to modify the reference of location of the functions or global variable that has been defined externally.

  * Relocation entries for *code* is placed in .rel.text and data(variables) are placed in the .rel.data.


* Relocating Symbol References

  * ***R_X86_64_PC32***

    Use PC-relative address (offset from the current run-time value of the program counter).

  * ***R_X86_64_32***

    Use 32bit absolute address.

  ```
  foreach section s {
      foreach relocation entry r {
          refptr = s + r.offset;				//ptr to reference to be relocated
          if (r.type == R_X86_64_PC32) {
              refaddr = ADDR(s) + r.offset;	//ref's run time address
              *refptr = (unsigned) (ADDR(r.symbol) + r.addend - refaddr);
          }
          if (r.type == R_X86_64_32)
          	*refptr = (unsigned) (ADDR(r.symbol) + r.addend);
      }
  }
  ```

  ###Question: What does the ADDR(r.symbol), r.addend mean?

  r.symbol (pg. 726): The symbol identifies the symbol that the modified reference should point to.

  r.addend (pg. 726): It is a signed constant that is used by some types of relocations to bias the value of the modified reference.

  **LOOK AT PAGE 727 AND SLIDES FOR EXAMPLES!!!**


## 7.8 Executable Object Files

* **Entry Point**: Address of the first instruction to execute when the program runs. It is in the ELF header.
* Code Segment: Read only. Includes .init, .text, .rodata
* Data Segment: Read/Write. Includes .data, .bss.



## 7.9 Loading Executable Object Files

* Loader

  Running program invokes the loader. Any linux program can invoke loader by calling `execve` function. Loader copies the code and data in the executable object file from disk into memory, by jumping into entry point.

* **Heap**: Grows upwards when called with dynamic memory.

* **Kernel Memory**: OS's memory resident
* X86-64 run-time memory image (from up to bottom)
  1. Kernel memory
  2. User stack (grows down)
  3. Memory-mapped region for shared libraries
  4. Run-time heap (grows up)
  5. Read/Write segment (.data, .bss)
  6. Read-only code segment (.init, .text, .rodata)



## 7.10 Dynamic Linking with Shared Libraries

* Why dynamic library?
  1. The libraries are update.
  2. Save memory by allowing multiple processes to share the same library code in memory.
* **Shared Library**(.so): Object module that, in either run-time or load-time, can be loaded at an arbitrary memory address and linked with a program in memory.
  * Shared meaning

    1. The code and data in .so file are shared bu all of the executable object files that reference the library.

    2. A single copy of the .text section  of a shared library in memory can be shared by different running processes.
  * Link statically when creating executable file, then link dynamically.
* Commands for dynamic library
  use `man dlopen` !!!!!!
  * `void *dlopen(const char *filename, int flag)`: opens the shared object file
  * `void *dlsym(void *handle, char *symbol)`: returns pointer to symbol
  * `int dlclose(void *handle`: unloads the shared library
  * `const char *dlerror(void)`: returns a string describing the most recent error
  * To compile, use `gcc -rdynamic -o main main.c -ldl`



## 7.11 Loading and Linking Shared Libraries form Applications

### Question: Why does dynamic linking have advantage on caching?



## 7.12 Position-Independent Code (PIC)

* **PIC**: Code that can be loaded without needing any relocations. Compiled using PC-relative addressing and relocated by static linker.

* PIC Data References

  ## 아 몰랑~~~



## 7.13 Library Interpoisitioning

* **Library Interpositioning**: Allows you to intercept calls to shared library functions and execute your own code.
* Note that giving `-I` argument causes interpositioning.
* Compile-Time Interpositioning
* Link-Time Interpositioning
* Run-Time Interpositioning
*
