# Windows Setup Guide for Mosaic Pattern Creator

This guide will help you install all required dependencies on Windows.

## Prerequisites Checklist

You need to install:
- [ ] CMake (3.16 or higher)
- [ ] Qt6 (Core and Widgets)
- [ ] OpenCV (4.x)
- [ ] A C++ compiler (MSVC 2017+ or MinGW)

## Installation Options

### Option 1: Using vcpkg (Recommended for Windows)

vcpkg is Microsoft's C++ package manager and makes dependency management easier.

#### 1. Install vcpkg

```powershell
# Clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg

# Navigate to vcpkg directory
cd C:\vcpkg

# Bootstrap vcpkg
.\bootstrap-vcpkg.bat

# Integrate with Visual Studio (if using MSVC)
.\vcpkg integrate install
```

#### 2. Install CMake

Download and install CMake from: https://cmake.org/download/

Or use Chocolatey (if installed):
```powershell
choco install cmake
```

Or use winget:
```powershell
winget install Kitware.CMake
```

#### 3. Install Qt6 and OpenCV via vcpkg

```powershell
# Navigate back to vcpkg directory
cd C:\vcpkg

# Install Qt6 (this may take a while)
.\vcpkg install qt6-base[widgets]:x64-windows

# Install OpenCV
.\vcpkg install opencv:x64-windows
```

#### 4. Build the Project

```powershell
# Navigate to project directory
cd D:\mosaic_pattern

# Create build directory
mkdir build
cd build

# Configure with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake

# Build
cmake --build . --config Release
```

### Option 2: Manual Installation

#### 1. Install CMake

Download from: https://cmake.org/download/
- Choose "Windows x64 Installer"
- During installation, select "Add CMake to system PATH"

Verify installation:
```powershell
cmake --version
```

#### 2. Install Qt6

Download from: https://www.qt.io/download-open-source
- Create a free Qt account if needed
- Download Qt Online Installer
- Install Qt 6.5 or later
- Make sure to select:
  - MSVC 2019 64-bit (or your compiler version)
  - Qt Widgets module

**Important**: Note the installation path (e.g., `C:\Qt\6.5.0\msvc2019_64`)

#### 3. Install OpenCV

**Option A: Pre-built binaries**
1. Download from: https://opencv.org/releases/
2. Extract to `C:\opencv`
3. Add `C:\opencv\build` to your PATH environment variable

**Option B: Build from source** (for better integration)
- Download source from: https://opencv.org/releases/
- Follow OpenCV Windows installation guide

#### 4. Set Environment Variables

Add Qt6 to your PATH:
```powershell
# Add Qt bin directory to PATH (replace version/path as needed)
$env:Path += ";C:\Qt\6.5.0\msvc2019_64\bin"
```

Or set permanently:
1. Open System Properties → Environment Variables
2. Add `C:\Qt\6.5.0\msvc2019_64\bin` to Path variable

Set OpenCV_DIR:
```powershell
[System.Environment]::SetEnvironmentVariable('OpenCV_DIR', 'C:\opencv\build', 'User')
```

#### 5. Build the Project

```powershell
# Navigate to project directory
cd D:\mosaic_pattern

# Create build directory
mkdir build
cd build

# Configure (may need to specify Qt6 path)
cmake .. -DCMAKE_PREFIX_PATH=C:\Qt\6.5.0\msvc2019_64

# Or if OpenCV not found automatically:
cmake .. -DCMAKE_PREFIX_PATH=C:\Qt\6.5.0\msvc2019_64 -DOpenCV_DIR=C:\opencv\build

# Build
cmake --build . --config Release
```

### Option 3: Using Visual Studio 2022 (Easiest)

Visual Studio includes CMake and MSVC compiler.

1. Install Visual Studio 2022 Community (free)
   - During installation, select:
     - Desktop development with C++
     - CMake tools for Windows

2. Install Qt6 and OpenCV using vcpkg (as in Option 1)

3. Open the project:
   - Open Visual Studio
   - File → Open → CMake...
   - Select `D:\mosaic_pattern\CMakeLists.txt`
   - Visual Studio will automatically configure and build

## Verifying Installation

Check each dependency:

```powershell
# Check CMake
cmake --version

# Check Qt6 (if in PATH)
qmake --version

# Check OpenCV (if installed)
# This may not show a version, but CMake should find it
```

## Troubleshooting

### CMake not found
- Ensure CMake is installed and added to PATH
- Restart PowerShell/terminal after installation
- Check PATH: `$env:Path -split ';'`

### Qt6 not found by CMake
```powershell
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.5.0\msvc2019_64"
```

### OpenCV not found
```powershell
cmake .. -DOpenCV_DIR="C:\opencv\build"
```

### Build errors
- Ensure you're using the correct compiler (MSVC vs MinGW)
- Make sure Qt6 and OpenCV are built for the same architecture (x64)
- Check that all DLLs are in PATH when running the executable

## Next Steps

After successful build:
- Run: `.\bin\MosaicPatternCreator.exe`
- Or from build directory: `.\bin\Release\MosaicPatternCreator.exe`

---

**Need help?** Check the main README.md for more details or file an issue on GitHub.
