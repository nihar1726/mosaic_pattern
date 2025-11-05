# 🧩 Mosaic Pattern Creator

A desktop application that transforms images into stunning mosaic artworks using customizable tile shapes, sizes, and color modes.

## ✨ Overview

**Mosaic Pattern Creator** lets users load any image and generate a beautiful mosaic effect. You can adjust tile size, choose between different shapes (Square, Circle, or Hexagon), and apply various color processing modes for artistic effects — all through an elegant, Qt-based interface.

---

## 🚀 Features

- 📸 **Image Loading** — Supports PNG, JPG, JPEG, and BMP formats  
- 🎨 **Multiple Tile Shapes** — Square ▪️ | Circle ⚪ | Hexagon ⬡  
- ⚙️ **Customizable Tile Size** — Adjustable between 5 and 100 pixels  
- 🌈 **Color Modes**  
  - **Average**: Uses the average color per tile  
  - **Dominant**: Uses the dominant color (currently approximated via average)  
  - **Quantized**: Reduces image colors for a stylized appearance  
- 💾 **Save & Export** — Export your generated mosaics as PNG or JPEG files  
- 🖥️ **Modern GUI** — Built with **Qt6**, ensuring a smooth and interactive user experience  

---

## 🧱 Requirements

### Build Dependencies

- **C++17** compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)  
- **CMake** 3.16 or newer  
- **Qt6** (Core + Widgets modules)  
- **OpenCV** 4.x  

---

## ⚙️ Installation

### Ubuntu / Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake
sudo apt-get install qt6-base-dev qt6-base-dev-tools
sudo apt-get install libopencv-dev
Windows (via vcpkg)
bash

Copy code
vcpkg install qt6-base
vcpkg install opencv
macOS (via Homebrew)
bash

Copy code
brew install cmake
brew install qt6
brew install opencv
🏗️ Building the Project
Navigate to the project folder:

bash

Copy code
cd mosaic_pattern
Create a build directory:

bash

Copy code
mkdir build
cd build
Windows PowerShell:

powershell

Copy code
mkdir build; cd build
Configure using CMake:

bash

Copy code
cmake ..
For Windows with vcpkg:

bash

Copy code
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path_to_vcpkg]/scripts/buildsystems/vcpkg.cmake
Build the project:

bash

Copy code
cmake --build .
Run the application:

bash

Copy code
./bin/MosaicPatternCreator     # Linux / macOS
powershell

Copy code
.\bin\MosaicPatternCreator.exe # Windows PowerShell
🧭 Usage Guide
Launch the App
Open Command Prompt, navigate to the executable location:

bash

Copy code
D:\mosaic_pattern\build\bin>
and run:

bash

Copy code
MosaicPatternCreator.exe
Load an Image
Click “Load Image”
Select your image (PNG, JPG, BMP, etc.)
The image appears in the left preview pane
Adjust Parameters
Tile Size: 5–100 pixels
Shape: Square ▪️ | Circle ⚪ | Hexagon ⬡
Color Mode: Average | Dominant | Quantized
Generate Mosaic
Click “Generate Mosaic”
The result appears on the right preview pane
Adjust settings anytime and regenerate
Save Your Mosaic
Click “Save Mosaic”
Choose format (PNG or JPEG) and output path
🧩 Project Structure

Copy code
MosaicPatternCreator/
│
├── src/
│   ├── main.cpp                  # Entry point
│   ├── ImageProcessor.cpp        # Image loading and manipulation
│   ├── MosaicGenerator.cpp       # Mosaic generation logic
│   ├── UI.cpp                    # Qt GUI implementation
│   └── Utils.cpp                 # Utility functions
│
├── include/
│   ├── ImageProcessor.h
│   ├── MosaicGenerator.h
│   ├── UI.h
│   └── Utils.h
│
├── build/
│   ├── bin/                      # Contains executable
│   ├── CMakeFiles/
│   └── Makefile
│
├── CMakeLists.txt                # Build configuration
└── README.md                     # Project documentation
🧠 Architecture Overview
Component

Responsibility

ImageProcessor

Loads and prepares the source image using OpenCV

MosaicGenerator

Applies mosaic logic based on user-selected parameters

UI

Handles GUI rendering and user interactions (Qt)

Utils

Provides helper functions for color and math utilities

Design Highlights
Modular Architecture — Clear separation of logic and interface
RAII Principles — Safe memory management for OpenCV & Qt objects
Factory-like Tile Handling — Generates shapes dynamically based on user choice
🔮 Future Enhancements
Import custom tile patterns
Text or emoji-based mosaics
Photo mosaics using secondary images
Real-time live preview
Batch image processing
Export color palette as text file
3D rendering of mosaic tiles
🤝 Contributing
Contributions, ideas, and feature suggestions are welcome!
You can fork this repository, open issues, or submit pull requests.

⚖️ License
This project is shared for educational and personal use.
Feel free to explore, modify, and learn from it.

🧩 Troubleshooting
❗ CMake can’t find Qt6
Ensure Qt6 is installed and point CMake to its directory:

bash

Copy code
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt6
❗ OpenCV not found
Specify its installation path manually if needed:

bash

Copy code
cmake .. -DOpenCV_DIR=/path/to/opencv
⚠️ Build errors on Windows
Use MSVC 2017+ or MinGW
Verify all dependencies are correctly installed and linked
Enjoy creating beautiful mosaic art! 🎨🧩

