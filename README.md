# Torch Organization Monorepo

This is an integrated monorepo containing all repositories from the [Torch organization](https://github.com/torch), unified into a single cohesive codebase. All repositories have been integrated without git submodules, creating a singular whole that embodies the entire Torch ecosystem.

## Overview

Torch is a scientific computing framework with wide support for machine learning algorithms. This monorepo integrates all the Torch organization repositories into one unified structure for easier development, building, and distribution.

## Repository Structure

All Torch repositories are organized under the `packages/` directory:

```
org-torch/
├── packages/          # All integrated torch repositories
│   ├── torch7/       # Core Torch library
│   ├── nn/           # Neural network library
│   ├── cutorch/      # CUDA backend for Torch7
│   ├── cunn/         # CUDA neural network library
│   ├── optim/        # Optimization algorithms
│   ├── image/        # Image processing toolbox
│   ├── threads/      # Threading support
│   ├── tutorials/    # Torch tutorials
│   ├── demos/        # Demo applications
│   └── [...]         # And many more packages
├── clone-repos.sh    # Script to refresh repositories
└── README.md         # This file
```

## Integrated Packages

The monorepo includes the following packages from the Torch organization:

### Core Libraries
- **torch7** - The main Torch library (http://torch.ch)
- **nn** - Neural network library for Torch
- **TH** - Standalone C TH library
- **ffi** - FFI bindings for LuaJIT-speed access to Tensors

### CUDA Support
- **cutorch** - CUDA backend for Torch7
- **cunn** - CUDA neural network implementations

### Utilities & Extensions
- **optim** - Numeric optimization package
- **image** - Image processing toolbox
- **xlua** - Extensions for Lua (string, table, etc.)
- **paths** - Path manipulation utilities
- **sys** - System utilities
- **class** - Object-oriented programming for Lua
- **argcheck** - Argument checking and function overloading

### Data Structures & Threading
- **threads** - Multi-threading with transparent data exchange
- **tds** - Torch C data structures
- **vector** - Vector operations
- **hash** - Hashing functions

### Neural Networks
- **nngraph** - Graph computation for neural networks
- **rnn** - Recurrent neural network implementations

### Visualization & UI
- **gnuplot** - Gnuplot interface for visualization
- **qtlua** - Lua interface to QT library
- **qttorch** - QT integration for Torch
- **graph** - Graph visualization package

### FFI & Bindings
- **sdl2-ffi** - LuaJIT interface to SDL2
- **cairo-ffi** - LuaJIT FFI interface to Cairo Graphics
- **sundown-ffi** - LuaJIT interface to Sundown (Markdown)

### Development & Distribution
- **luajit-rocks** - LuaJIT and luarocks in one location
- **rocks** - Rocks packages for Torch
- **distro** - Torch installation in a self-contained folder
- **ezinstall** - One-line install scripts
- **trepl** - Pure Lua-based REPL for Torch
- **env** - Default Torch environment setup

### Documentation & Extras
- **tutorials** - Machine learning tutorials for Torch7
- **demos** - Various demos and examples
- **torch.github.io** - Torch website source
- **dok** - Documentation utilities
- **cwrap** - C wrapper utilities
- **senna** - NLP SENNA interface
- **socketfile** - File-over-sockets support
- **rational** - Rational number support
- **xt** - TH/THC C++11 wrapper

## Integration Details

This monorepo was created by:

1. Cloning all repositories from https://github.com/torch/*
2. Removing individual `.git` directories to integrate them as a single repository
3. Organizing all packages under a unified `packages/` directory
4. Maintaining the original structure of each package for compatibility

All packages maintain their original functionality and can be used together as an integrated whole.

## Usage

Each package in the `packages/` directory retains its original structure, documentation, and build system. Refer to individual package READMEs for specific usage instructions.

### Building Core Components

Most Torch packages use CMake or LuaRocks for building. Example:

```bash
# For CMake-based packages
cd packages/torch7
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=~/torch
make install

# For LuaRocks packages
cd packages/nn
luarocks make rocks/nn-scm-1.rockspec
```

## Contributing

This monorepo is a unified mirror of the Torch organization repositories. For contributing to specific packages, please refer to their original repositories or contribute to this integrated version.

## License

See the [LICENSE](LICENSE) file for details. Individual packages may have their own licenses - refer to each package's directory for specific licensing information.

## Links

- Original Torch Organization: https://github.com/torch
- Torch Website: http://torch.ch
- This Monorepo: https://github.com/o9nn/org-torch

## Maintenance

To update all packages to their latest versions, run:

```bash
./clone-repos.sh
```

This will fetch the latest versions of all repositories while maintaining the monorepo structure.