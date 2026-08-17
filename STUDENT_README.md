# Student Build Guide

This project reads ten integers and prints their mean and median. It uses:

- C++17
- CMake 3.21 or newer
- vcpkg for the GoogleTest dependency
- CTest to run the test suite

You need an internet connection the first time you configure the project because
vcpkg downloads and builds GoogleTest. These instructions assume that you run
commands from a terminal and that the repository has already been downloaded.

## macOS setup

### 1. Install the compiler and basic build tools

Apple's Command Line Tools for Xcode include Apple Clang (the C++ compiler),
Git, Make, the macOS SDK, and other command-line development tools.

Open Terminal and run:

```bash
xcode-select --install
```

Complete the installation dialog. See Apple's official
[Command Line Tools installation guide](https://developer.apple.com/documentation/xcode/installing-the-command-line-tools/)
for more information.

### 2. Install CMake and supporting packages

Install [Homebrew](https://docs.brew.sh/Installation) if the `brew` command is
not already available. Then run:

```bash
brew update
brew install cmake autoconf automake libtool pkg-config
```

macOS provides `curl`, `tar`, `zip`, and `unzip`, which vcpkg uses to download
and extract source archives. Confirm that all required commands are available:

```bash
clang++ --version
cmake --version
git --version
curl --version
tar --version
zip -v
unzip -v
```

### 3. Install vcpkg

The following commands install vcpkg in your home directory. If `~/vcpkg`
already exists, use that installation instead of cloning it again.

```bash
git clone https://github.com/microsoft/vcpkg.git "$HOME/vcpkg"
"$HOME/vcpkg/bootstrap-vcpkg.sh" -disableMetrics
export VCPKG_ROOT="$HOME/vcpkg"
echo 'export VCPKG_ROOT="$HOME/vcpkg"' >> "$HOME/.zshrc"
```

The `export` command sets the variable for the current terminal. Adding it to
`.zshrc` makes it available in new Terminal windows. See Microsoft's official
[vcpkg repository and setup instructions](https://github.com/microsoft/vcpkg).

## Windows setup with WSL

These instructions use Ubuntu inside Windows Subsystem for Linux (WSL). Do not
enter the Linux setup or build commands in PowerShell; enter them in the Ubuntu
terminal.

### 1. Install WSL and Ubuntu

Follow Microsoft's official
[Install WSL walkthrough](https://learn.microsoft.com/windows/wsl/install).
For a standard installation, open PowerShell as Administrator and run:

```powershell
wsl --install -d Ubuntu
```

Restart Windows if prompted. Open Ubuntu and finish creating your Linux username
and password before continuing.

### 2. Install the compiler, CMake, and vcpkg prerequisites

In the Ubuntu terminal, run:

```bash
sudo apt update
sudo apt install -y build-essential g++ cmake git curl zip unzip tar pkg-config autoconf automake libtool
```

`build-essential` installs the standard GNU build tools, including Make and the
GCC/G++ compiler toolchain. The other packages provide CMake, Git, and the
archive and download utilities required by vcpkg.

Verify the main tools:

```bash
g++ --version
cmake --version
git --version
zip --version
unzip -v
```

### 3. Install vcpkg

Still in the Ubuntu terminal, run:

```bash
git clone https://github.com/microsoft/vcpkg.git "$HOME/vcpkg"
"$HOME/vcpkg/bootstrap-vcpkg.sh" -disableMetrics
export VCPKG_ROOT="$HOME/vcpkg"
echo 'export VCPKG_ROOT="$HOME/vcpkg"' >> "$HOME/.bashrc"
```

If `~/vcpkg` already exists, use that installation instead of cloning it again.
The `.bashrc` entry makes `VCPKG_ROOT` available in future Ubuntu terminals.

For the best WSL filesystem performance, keep the repository in the Linux
filesystem, such as `~/projects/golden-template-cpp`, rather than under
`/mnt/c`. Microsoft's
[WSL development-environment guide](https://learn.microsoft.com/windows/wsl/setup/environment)
explains this recommendation and other WSL setup practices.

## Build the project

The remaining commands are the same on macOS and WSL. Open a terminal, change to
the repository directory, and confirm that it contains `CMakeLists.txt`:

```bash
cd /path/to/this/project
ls CMakeLists.txt
```

The repository includes `CMakePresets.json`. Its `default` preset selects a
Debug build, enables testing, and gets the vcpkg toolchain path from the
`VCPKG_ROOT` environment variable. Configure the project with:

```bash
cmake --preset default
```

The preset tells CMake to read `vcpkg.json`, so vcpkg installs GoogleTest
automatically. The first configuration may take several minutes while vcpkg
builds GoogleTest. After configuration succeeds, compile the project:

```bash
cmake --build --preset default
```

## Run the project

Run the executable from the repository root:

```bash
./build/mean_median
```

Enter ten integers when prompted. For example:

```text
Enter 10 integers:
1 2 3 4 5 6 7 8 9 10
Mean: 5.5
Median: 5.5
```

## Run the tests

CTest runs every GoogleTest case registered by CMake:

```bash
ctest --preset default
```

A successful run ends with output similar to:

```text
100% tests passed, 0 tests failed out of 5
```

You can also run the GoogleTest executable directly:

```bash
./build/tests
```

Use the CTest command for normal development and grading because it matches the
test command used by continuous integration.

## Common problems

### `VCPKG_ROOT` is empty

Check the variable:

```bash
echo "$VCPKG_ROOT"
```

If it prints a blank line, set it again:

```bash
export VCPKG_ROOT="$HOME/vcpkg"
```

### CMake cannot find the compiler, preset, or toolchain file

Confirm that the expected files and commands exist:

```bash
command -v cmake
command -v c++
test -f CMakePresets.json && echo "CMake preset found"
test -f "$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" && echo "vcpkg toolchain found"
```

If you changed compilers or moved vcpkg after configuring, remove only this
project's generated `build` directory and configure it again:

```bash
rm -rf ./build
```
