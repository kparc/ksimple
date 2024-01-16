# k/simple

a tiny k interpreter for educational purposes by arthur whitney

## target audience

the contents of this repository assume a readership who have read and 
understood [k&r](https://en.wikipedia.org/wiki/The_C_Programming_Language)
at some point in their careers. any experience with using interpreters of
vector languages is beneficial but not necessary. any experience with
**implementing** vector language interpreters would definitely help a lot.

## background

in early january 2024, a group of motivated individuals asked arthur whitney
to demonstrate the fundamentals of the design, organization and style of his
method of writing c in the most succinct and approachable way possible.

about a day later, arthur offered a tiny interpreter of a toy vector 
language, implemented in about 25 lines of c with a small header file.
his code is published in this repository under [/ref](/ref).

a few days later, the regents of kparc were invited to share their 
impressions on this codebase, and optionally provide some additional 
commentary.

such commentary is offered in form of two files `a.[ch]` in the root of 
this repository, which serve a number of purposes:

1. both files can be seen as two chapters of a small "essay", header
   file [a.h](/a.h) being the first chapter, [`a.c`](/a.c) source file being the second.
   not only the text seeks to explain the code in reasonable detail,
   which is strictly line by line, but also takes a few liberties and
   diversions in a bid to elucidate the "bigger picture" behind this tiny piece of code.

3. for the ease of comprehension, the enclosed narrative has been made
   **completely linear**, and hopefully makes for an easy, entertaining and
   useful read. to make this possible, the original code had seen some
   very minor restructuring and regrouping; however, no refactoring,
   no changes to logic or naming conventions have taken place, except 
   for a handful cosmetic enhancements which have been discussed with
   atw and are seen as beneficial to the cause. the net amount of
   non-cosmetic changes made to [ref/a.c](/ref/a.c) should be in range of 20-25 keystrokes.
   a number of less trivial one-line functions (e.g. `e()`) are presented
   in "exploded view" to simplify discussion of their control flow and role
   of individual components.


4. with help of the included [makefile](/makefile), kparc's "essay" can
   be built to any available architecture, e.g. arm, riscv, wasm32 or extensa.
   default make target assumes presence of a recent gcc, clang or tinyc compiler.
   there are also two additional handy build targets: `make mm`, which
   removes kparc remarks from the code except for the most essential markup,
   while the `make m` target removes it completely and restores the formatting
   to resemble the original as close as possible for the ease of reference.
   these build targets produce files `a.min.c` and `a.m.c` respectively,
   build them, and perform a bitwise diff to ensure all three resulting 
   binaries are identical.

## quick start

```
$ cd && git clone git@github.com:kparc/ksimple.git
$ cd ksimple && make
$ ./a
k/simple (c) 2024 atw/kpc
 2+2
4
 x:!9
 y:2+!9
 x-y
-2 -2 -2 -2 -2 -2 -2 -2 -2
 z:x,y
 #z
18
 x+!3
Add:length
 x@1,5,7
1 5 7
 ^C
$

```

## language specification

[WIP]


