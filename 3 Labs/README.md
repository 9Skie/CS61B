# C++ labs

All programming starters and supplied tests use C++17. Run `make` inside a lab folder, then follow its `Instructions.html` for executable names and exercises. `lab04` is a Git exercise and has no programming starter.

Run `make test` for the supplied tests. Unfinished methods and deliberate debugging errors are part of the assignments, so the untouched starters are not expected to pass. For labs 6 and 8, the `Extra` test executables cover optional methods; run the ordinary test executable while working on required methods. `make clean` removes generated files.

Use a C++17 compiler and Make. On macOS, `xcode-select --install` supplies the compiler and LLDB. Linux users can use GCC or Clang with GDB. Builds include debug information. Open an executable with `lldb ./build/Name` or `gdb ./build/Name`; set an exception breakpoint when investigating bounds or missing-value errors.

Labs 9–10 and Project 3 also use SDL3, FreeType and libpng. Install them with `brew install sdl3 freetype libpng pkg-config` on macOS, or install the equivalent development packages using your Linux package manager. Set `CS61B_FONT` to a Unicode `.ttf` file if automatic font discovery fails.

`support/` contains the shared C++ test runner, reproducible random generator, drawing API and tile renderer. Each graphical exercise keeps its own `Tileset.hpp` so you can customize its tiles. Keep this folder alongside `4 Projects` when building Project 3.

Map values use `std::optional<V>`: `std::nullopt` can represent either an absent key or an explicitly empty value; `containsKey` distinguishes them. Template implementations live in headers. The disjoint-set operation is called `unite` because `union` is reserved in C++.
