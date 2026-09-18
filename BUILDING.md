# Building the C++ Demo

The project uses CMake and vcpkg. GoogleTest is the only vcpkg dependency.

Set `VCPKG_ROOT` to your vcpkg installation, then configure and build:

```bash
cmake --preset default
cmake --build --preset default
ctest --preset default
```

The grading tests are also a standalone CMake project. To configure them
without relying on the root `CMakeLists.txt`, run this from the repository root:

```powershell
cmake -S tests -B build-tests `
  -DREPO_ROOT="$PWD" `
  -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
cmake --build build-tests
ctest --test-dir build-tests --output-on-failure
```

Run the demo and enter ten integers when prompted:

```powershell
.\build\Debug\mean_median.exe
```

With a single-configuration generator, such as Ninja, the executable is usually
located at `build/mean_median` (or `build/mean_median.exe` on Windows).
