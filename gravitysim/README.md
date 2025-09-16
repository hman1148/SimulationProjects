# Gravity Simulation Engine

A real-time 3D gravity simulation built in C++20 with OpenGL, featuring interactive celestial body dynamics and space-time visualization.

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![OpenGL](https://img.shields.io/badge/OpenGL-3.3+-red)
![License](https://img.shields.io/badge/license-MIT-green)

## 🌌 Features

### Core Simulation
- **Real-time gravitational physics** using Newton's law of universal gravitation
- **N-body simulation** with accurate force calculations between all objects
- **Collision detection** and response system
- **Interactive object creation** with adjustable mass and initial conditions
- **Space-time grid visualization** showing gravitational field distortion

### Advanced Physics
- **Relativistic effects** including Schwarzschild radius calculations
- **Dynamic mass scaling** during object creation
- **Realistic density-based radius calculations**
- **Smooth gravitational force interpolation**

### Rendering & Graphics
- **Modern OpenGL 3.3+** rendering pipeline
- **Procedural sphere generation** with configurable detail levels
- **Dynamic lighting** with surface normal calculations
- **Glow effects** for stellar objects
- **Transparent grid overlay** showing space-time curvature
- **Free-form 3D camera** with mouse and keyboard controls

### User Interface
- **Real-time object manipulation** during simulation
- **Pause/resume functionality** for detailed analysis
- **Interactive camera system** with smooth movement
- **Mouse-based object placement** and mass adjustment
- **Keyboard shortcuts** for all major functions

## 🏗️ Architecture

This project follows a modern object-oriented design with clear separation of concerns:

```
gravitysim/
├── engine/              # Core simulation engine
│   └── GravitySimulation.hpp
├── rendering/           # OpenGL rendering system
│   ├── Renderer.hpp
│   ├── Camera.hpp
│   └── ShaderManager.hpp
├── physics/            # Physics calculations
│   └── Physics.hpp
├── models/             # Object representations
│   ├── CelestialObject.hpp
│   └── satellites/     # Specialized object types
├── input/              # Input handling
│   └── InputManager.hpp
├── grid/               # Space-time visualization
│   └── Grid.hpp
└── main.cpp           # Application entry point
```

### Design Patterns
- **Component-based architecture** for modularity
- **RAII principles** for resource management
- **Modern C++20 features** including concepts and ranges
- **Smart pointers** for memory safety
- **Abstract interfaces** for extensibility

## 🚀 Getting Started

### Prerequisites

**System Requirements:**
- C++20 compatible compiler (GCC 10+, Clang 10+, or MSVC 2019+)
- CMake 3.16 or higher
- OpenGL 3.3+ compatible graphics card

**Dependencies:**
- **GLFW 3.x** - Window management and input
- **GLEW 2.x** - OpenGL extension loading
- **GLM 0.9.9+** - Mathematics library
- **OpenGL** - Graphics API

### Installation

#### Ubuntu/Debian
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake libglfw3-dev libglew-dev libglm-dev

# Clone and build
git clone <repository-url>
cd gravitysim
mkdir build && cd build
cmake ..
make -j$(nproc)
```

#### Windows (vcpkg)
```cmd
# Install dependencies via vcpkg
vcpkg install glfw3 glew glm

# Build with CMake
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

#### macOS (Homebrew)
```bash
# Install dependencies
brew install cmake glfw glew glm

# Build project
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

### Running the Simulation
```bash
# From build directory
./bin/GravitySim
```

## 🎮 Controls

### Camera Movement
- **W/A/S/D** - Move forward/left/backward/right
- **Space** - Move up
- **Shift** - Move down
- **Mouse** - Look around
- **Scroll Wheel** - Zoom in/out

### Simulation Controls
- **Left Click** - Create new celestial object
- **Right Click + Hold** - Increase object mass during creation
- **Arrow Keys** - Position object during creation (with Shift for Z-axis)
- **K** - Pause/unpause simulation
- **Q** - Quit application

### Object Creation Workflow
1. **Left click** to start creating an object
2. Use **arrow keys** to position it
3. **Right click and hold** to increase mass
4. **Release left click** to launch the object

## 🔬 Physics Model

### Gravitational Forces
The simulation implements Newton's law of universal gravitation:

```
F = G * (m1 * m2) / r²
```

Where:
- `G = 6.6743×10⁻¹¹ m³ kg⁻¹ s⁻²` (gravitational constant)
- `m1, m2` are the masses of the objects
- `r` is the distance between their centers

### Space-Time Visualization
The grid system visualizes gravitational field strength using:
- **Grid deformation** based on mass distribution
- **Schwarzschild radius** calculations for extreme mass objects
- **Center of mass** tracking for multi-body systems

### Object Properties
- **Mass**: Determines gravitational influence
- **Density**: Affects object radius (ρ = 3344 kg/m³ default)
- **Radius**: Calculated from mass and density
- **Velocity**: Updated by gravitational acceleration

## 🛠️ Configuration

### Physics Constants
```cpp
const double G = 6.6743e-11;     // Gravitational constant
const float c = 299792458.0;      // Speed of light
float initMass = 1e22;            // Default object mass
float sizeRatio = 30000.0f;       // Scale factor for visualization
```

### Rendering Settings
- **Sphere detail**: 10×10 segments (configurable)
- **Grid resolution**: 25×25 divisions
- **Camera FOV**: 45° (adjustable)
- **Render distance**: 750,000 units

## 🔧 Development

### Building in Debug Mode
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
# Run with debugging symbols
gdb ./bin/GravitySim
```

### Adding New Features
The modular architecture makes it easy to extend:

1. **New object types**: Inherit from `CelestialObject`
2. **Custom physics**: Extend the `Physics` class
3. **Rendering effects**: Add shaders via `ShaderManager`
4. **Input modes**: Implement new handlers in `InputManager`

### Performance Optimization
- Use **Release builds** for production (`-DCMAKE_BUILD_TYPE=Release`)
- Adjust **sphere detail levels** based on performance needs
- Modify **update frequencies** for large-scale simulations

## 📊 Examples

### Earth-Moon System
```cpp
// Create Earth (scaled down)
Object earth(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 
            5.97219e24, 5515, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

// Create Moon
Object moon(glm::vec3(3844, 0, 0), glm::vec3(0, 0, 228), 
           7.34767309e22, 3344);
```

### Binary Star System
```cpp
// Two massive objects orbiting each other
Object star1(glm::vec3(-5000, 0, 0), glm::vec3(0, 0, 1500), 
            1.989e25, 5515, glm::vec4(1.0f, 0.929f, 0.176f, 1.0f), true);
            
Object star2(glm::vec3(5000, 0, 0), glm::vec3(0, 0, -1500), 
            1.989e25, 5515, glm::vec4(0.8f, 0.2f, 0.9f, 1.0f), true);
```

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details.

### Areas for Contribution
- **Performance optimization** for large-scale simulations
- **Additional physics models** (electromagnetic forces, relativistic effects)
- **Enhanced visualization** (particle trails, heat maps, velocity vectors)
- **User interface** improvements
- **Documentation** and examples

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **OpenGL** community for excellent graphics tutorials
- **GLM** developers for the comprehensive math library
- **GLFW** team for cross-platform window management
- Physics simulations inspired by real astronomical data

## 📞 Support

- **Issues**: Report bugs via GitHub Issues
- **Discussions**: Join our community discussions
- **Documentation**: Check the `/docs` folder for detailed guides
- **Performance**: See [PERFORMANCE.md](PERFORMANCE.md) for optimization tips

---

**Built with ❤️ and C++20**
