# R-TYPE
## About
The Epitech RType project is an adaptation of the famous video game R-Type, which is a classic side-scrolling shooter game. The goal is to recreate a playable version of this game using the C++ programming language.

In order to have a personnal game engine, we decide to use our open source game engine `GuismusEngine`. For more information go to this github repository: https://github.com/Guismus/GuismusEngine
## Installation

### Linux
To compile game and server using Linux, you just have to clone this project, enter in the directory with a terminal then launch this command:
```
./build.sh
```
If build does not work, is it maybe because you do not have require version of `CMake` or `Ninja`.

To install ninja: https://earthly.dev/blog/ninjabuild-for-faster-build/

To install Cmake: https://geeksww.com/tutorials/operating_systems/linux/installation/downloading_compiling_and_installing_cmake_on_linux.php (version 3.25 minimum required)

Once build is acheive, you just have to go to the build directory create with this command then launch rtype_client or/and rtype_server

### Windows

Compile with windows is still possible but is it unstable, we recommend to download last version on github then unzip `win-rtype_xxx.zip`. once this acheive, you just have to enter the directory then click on shortcuts rtype_client and/or rtype_server.