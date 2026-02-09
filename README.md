# IT Crowd DVD Game

A retro-style DVD game with chromatic aberration and scanline effects.

## Building

### Windows

#### Using Visual Studio:
1. Install SFML 3.0 for Windows
2. Open CMake GUI or use command line:
   ```cmd
   mkdir build
   cd build
   cmake .. -DSFML_DIR="C:/path/to/SFML/lib/cmake/SFML"
   cmake --build .
   ```
3. Or open the folder in Visual Studio (it will detect CMakeLists.txt)

#### Using CMake command line:
```cmd
cmake -B build
cmake --build build
build\Debug\game.exe
```

### Linux

#### Using CMake:
```bash
cmake -B build
cmake --build build
./build/game
```

#### Using Make (legacy):
```bash
make
make run
```

## Requirements

- SFML 3.0+
- C++20 compiler (MSVC, GCC, or Clang)
- CMake 3.16+ (for CMake build)

## Assets

Place all game assets in the `assets/` folder:
- `assets/Main Menu Assets/` - Fonts and menu graphics
- `assets/shaders/` - GLSL shader files
