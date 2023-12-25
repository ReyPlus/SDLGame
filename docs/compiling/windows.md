# Compiling on Windows with MSVC

## Requirements

- [Visual Studio](https://visualstudio.microsoft.com)
- [CMake 3.28.1 or Newer](https://cmake.org/download/)
- [vcpkg](https://github.com/Microsoft/vcpkg)
- [Git](https://git-scm.com/downloads)


## Compiling and installing the dependencies

After building vcpkg the required libraries can be installed:
```powershell
vcpkg install sdl2 sdl2-mixer sdl2-mixer[libflac] sdl2-mixer[libmodplug] sdl2-mixer[mpg123] sdl2-mixer[opusfile] sdl2-ttf sdl2-sdl_image
vcpkg integrate install
```

There are optional libraries depending on the file types wanted.

Use `--triplet` to specify the target triplet, e.g. `x64-windows` or `x86-windows`.


## Compile SDLGame

### a) Using vcpkg toolchain and CMake GUI

1. Open cmd
2. cd into directory for repo to be created
3. git clone https://github.com/ReyPlus/SDLGame.git
4. cd SDLGame
5. mkdir out
6. cd out
7. mkdir build
8. cd build
9. cmake -S ../../
10. Open SDLGame.sln in Visual Studio
11. Click Project then Set as Startup Project
12. Compile SDLGame inside Visual Studio