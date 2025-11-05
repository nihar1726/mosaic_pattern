# 🧩 Mosaic Pattern Creator

A desktop application that converts images into beautiful mosaic patterns using customizable tiles, shapes, and color modes.

## Features

- 📸 **Image Loading**: Support for PNG, JPG, JPEG, and BMP formats
- 🎨 **Multiple Tile Shapes**: Square, Circle, and Hexagon tiles
- 🌈 **Color Modes**:
  - **Average**: Uses the average color of each region
  - **Dominant**: Uses the dominant color (currently uses average as approximation)
  - **Quantized**: Reduces colors to a palette for artistic effect
- ⚙️ **Customizable Tile Size**: Adjustable from 5 to 100 pixels
- 💾 **Export**: Save your mosaics as PNG or JPEG images
- 🖥️ **Modern GUI**: Built with Qt for a professional desktop experience

## Requirements

### Build Dependencies

- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- **CMake** 3.16 or higher
- **Qt6** (Core and Widgets modules)
- **OpenCV** 4.x

### Installing Dependencies

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake
sudo apt-get install qt6-base-dev qt6-base-dev-tools
sudo apt-get install libopencv-dev
```

#### Windows (using vcpkg)
```bash
vcpkg install qt6-base
vcpkg install opencv
```

#### macOS (using Homebrew)
```bash
brew install cmake
brew install qt6
brew install opencv
```

## Building the Project

1. **Clone or navigate to the project directory**:
   ```bash
   cd mosaic_pattern
   ```

2. **Create build directory**:
   ```bash
   mkdir build
   cd build
   ```
   
   **PowerShell (Windows)**:
   ```powershell
   mkdir build; cd build
   ```
   Or run separately:
   ```powershell
   mkdir build
   cd build
   ```

3. **Configure with CMake**:
   ```bash
   cmake ..
   ```
   
   For Windows with vcpkg:
   ```bash
   cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
   ```

4. **Build the project**:
   ```bash
   cmake --build .
   ```
   
   Or use your system's build tool:
   ```bash
   make        # Linux/macOS
   nmake       # Windows (MSVC)
   ```

5. **Run the application**:
   ```bash
   ./bin/MosaicPatternCreator    # Linux/macOS
   ```
   ```powershell
   .\bin\MosaicPatternCreator.exe # Windows PowerShell
   ```

## Usage

1. **Launch the application**

2. **Load an image**:
   - Click "Load Image" button
   - Select an image file from your computer
   - The original image will appear in the left preview pane

3. **Adjust parameters**:
   - **Tile Size**: Set the size of each mosaic tile (5-100 pixels)
   - **Shape**: Choose between Square, Circle, or Hexagon tiles
   - **Color Mode**: Select Average, Dominant, or Quantized mode

4. **Generate mosaic**:
   - Click "Generate Mosaic" button
   - The mosaic will appear in the right preview pane
   - Adjust parameters and click again to regenerate

5. **Save your creation**:
   - Click "Save Mosaic" button
   - Choose a location and filename
   - Select PNG or JPEG format
   - Your mosaic will be saved!

## Project Structure

```
MosaicPatternCreator/
│
├── src/
│   ├── main.cpp                  # Entry point
│   ├── MosaicGenerator.cpp       # Mosaic creation logic
│   ├── ImageProcessor.cpp        # Image loading and processing
│   ├── UI.cpp                    # Qt GUI implementation
│   └── Utils.cpp                 # Utility functions
│
├── include/
│   ├── MosaicGenerator.h
│   ├── ImageProcessor.h
│   ├── UI.h
│   └── Utils.h
│
├── CMakeLists.txt                # Build configuration
└── README.md                     # This file
```

## Architecture

### Core Components

- **ImageProcessor**: Handles image loading, resizing, and color extraction using OpenCV
- **MosaicGenerator**: Converts images into mosaic patterns based on tile size, shape, and color mode
- **UI**: Provides a Qt-based graphical interface for user interaction
- **Utils**: Contains color utilities, file path helpers, and color quantization algorithms

### Design Patterns

- **Modular Design**: Clean separation of concerns between image processing, mosaic generation, and UI
- **RAII**: Proper resource management for OpenCV matrices and Qt objects
- **Factory-like Pattern**: Flexible tile generation based on shape selection

## Future Enhancements

- [ ] Custom tile pattern import
- [ ] Text-based mosaics (ASCII/emoji)
- [ ] Photo mosaics (using another image as tile set)
- [ ] Real-time preview while adjusting parameters
- [ ] Batch processing multiple images
- [ ] Export color codes to text file
- [ ] 3D tile rendering effects

## Contributing

Contributions are welcome! Feel free to submit issues, fork the repository, and create pull requests.

## License

This project is provided as-is for educational and personal use.

## Troubleshooting

### CMake can't find Qt6
- Ensure Qt6 is installed and `CMAKE_PREFIX_PATH` points to your Qt6 installation
- Example: `cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt6`

### OpenCV not found
- Make sure OpenCV is installed and in your system PATH
- Or specify OpenCV path: `cmake .. -DOpenCV_DIR=/path/to/opencv`

### Build errors on Windows
- Ensure you're using a compatible compiler (MSVC 2017+ or MinGW)
- Check that all dependencies are properly linked via vcpkg or manual installation

---

**Enjoy creating beautiful mosaics! 🎨**
