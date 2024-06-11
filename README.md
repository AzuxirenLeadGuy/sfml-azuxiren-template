# SFML Azuxiren's Template

This template is for my personal projects, but feel free to use/change it to your needs.


## Pre-requisites

- clang or gcc compiler for C++
- Build tools (Either [GNU Make](https://www.gnu.org/software/make/) or [Taskfile](https://taskfile.dev))
- Optional tools:
    - clang-tidy : For providing analysis
    - clang-format : For formatting the code
    - [bear](https://github.com/rizsotto/Bear): For generation of [compile_commands.json] that will be used by your IDE as well as the above two tools to work properly.


Please go through the Makefile to understand how each tool work for each other. The build commands `build` and `debug` (in Makefile as well as the taskfile) compiles the program, without using any of the mentioned optional tools. 


## Purpose

This template is an initial boilerplate. A game can be abstracted in a series of "Scenes", while the `SfmlGameClass` does the low level tasks for all the scenes, i.e polling for events, storing settings that last for the entire game, invoking the main loop, etc. More details and examples would be provided in the wiki (Hopefully in the near future)

## License

This repository is licensed under the MIT license while the SFML library is licensed under [zlib/libpng](https://github.com/SFML/SFML/blob/master/license.md) license. 
