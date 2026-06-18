# Soft 3D Engine

A lightweight, purely software-driven 3D rendering engine built from scratch in C++. The engine performs all rasterization, matrix transformations, and physics-based logic on the CPU, using SFML solely as a multimedia library for window context management, input handling, and displaying the final pixel framebuffer.

![C++](https://img.shields.io/badge/C%2B%2B-17%2F20-orange.svg)
![SFML](https://img.shields.io/badge/SFML-2.6.1-green.svg)

## Features

* **Software Rasterization:** Custom triangle drawing and rasterization pipeline executed entirely on the CPU.
* **Math & Matrices:** Homemade implementations of look-at, projection, and transformation matrices for 3D clip-space calculations.
* **Real-time Visualization:** Smooth frame buffer updating (`sf::Texture::update` from standard pixel arrays).
* **Intuitive GUI:** Built-in debugging and scene manipulation controls using Dear ImGui (via `imgui-sfml`).
* **No Overhead UI Capturing:** Dedicated rendering capture tool that extracts pure 3D scenes directly from the custom framebuffer, bypassing ImGui overhead.

## Architecture & Core Components

* `src/main.cpp` & `src/Main_Cycle.cpp`: System loop setup, rendering ticks, delta-time calculations, and UI event processing.
* `include/`: Vendor dependencies grouped in a clean repository file tree:
    * `SFML-2.6.1`: Handles window management and low-level context hooks.
    * `imgui` & `portable-file-dialogs`: UI widgets and platform-native file save triggers.

##  Getting Started & Building

### Prerequisites
* Windows OS (configured for x64 architecture)
* **Visual Studio** (MSVC compiler with C++17/20 standard support)

### Installation & Compilation
Clone the repository: ```git clone https://github.com/iii1337iii/Soft-3D.git```
1. Open the solution file 3D_Engine.sln inside Visual Studio.
2. Set the active solution configuration to Release and platform to x64.

## Deployment / Distribution
To run the application standalone, ensure your output directory structure looks like this:

```Plaintext  
├── Soft_3D.exe  
├── sfml-graphics-2.dll  
├── sfml-window-2.dll  
├── sfml-system-2.dll  
├── assets/          # Mesh data and textures  
├── renders/         # Rendered images  
└── data/            # Engine configuration and runtime resources
```

### Controls & Shortcuts
Apart from the graphical user interface, the engine supports comprehensive keyboard and mouse binds for fluid scene editing:

### Object Manipulation Pipeline
1. Select Action: Press S (Scale), M (Move), or R (Rotate).
2. Select Axis: Press X, Y, or Z to lock the modification to a specific coordinate.
3. Adjust Value: Scroll the Mouse Wheel up or down to increment/decrement the value.
4. Apply Changes: Click Left Mouse Button (LMB) to confirm and commit the transformation.

### Render & Camera Controls
1. 1, 2, 3, 4: Cycle through rendering modes (Wireframe, Solid, etc.) on the fly.
2. LAlt + Mouse Wheel: Dynamically adjust the Camera's Field of View (FOV).

### Screenshots & Output
The runtime GUI allows seamless manipulation of objects. Users can capture the unblemished canvas output cleanly to a .png file at any chosen timeframe using the `Save as` functionality.
