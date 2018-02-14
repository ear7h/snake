# Snake

![snake gif](https://i.imgur.com/BXtXbcM.gif)

Classic terminal snake game implemented in C. Runs mostly smooth.
Please submit an issue if you have any problems running or building 🎫


Binary file for macOS can be found in [releases page](https://github.com/ear7h/snake/releases).

## Build instructions

Building requires [cmake](https://cmake.org/).

From root project directory
``` bash
> mkdir cmake-build-release
> cd cmake-build-release
> cmake -DCMAKE_BUILD_TYPE=Release ../
> make
```
This should result with a built binary in the `cmake-build-release` directory

## Todo

* Refresh only the snake piece being pushed out