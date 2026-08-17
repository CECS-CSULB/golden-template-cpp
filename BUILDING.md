# Building the C++ Demo

The project uses CMake and vcpkg. GoogleTest is the only vcpkg dependency.

Set `VCPKG_ROOT` to your vcpkg installation, then configure and build:

```powershell
cmake -S . -B build `
  -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build
ctest --test-dir build --output-on-failure
```

Run the demo and enter ten integers when prompted:

```powershell
.\build\Debug\mean_median.exe
```

With a single-configuration generator, such as Ninja, the executable is usually
located at `build/mean_median` (or `build/mean_median.exe` on Windows).
