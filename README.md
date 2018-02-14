# Snake

Classic terminal snake game implemented in C

Binary file for macOS can be found in releases page.

## Build instructions
Building requires [cmake](https://cmake.org/).

From root project directory
``` bash
> cd cmake-build-release
> cmake -DCMAKE_BUILD_TYPE=Release ../
> make
```
This should result in a binary in the `cmake-build-release` directory

## Todo
* speed up snake after each size increase