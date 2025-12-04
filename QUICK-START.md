# Quick Start Guide

Welcome to the Torch Monorepo! This guide will help you get started quickly.

## What is This?

This is a unified monorepo containing all 33 repositories from the Torch organization (https://github.com/torch). Everything has been integrated into a single repository for easier access and management.

## Quick Overview

- **33 packages** integrated from the torch organization
- **No submodules** - everything is directly in the repo
- **Complete functionality** - all original features preserved
- **~173 MB** total size
- **3900+ files** with source code, tests, and documentation

## Getting Started in 3 Steps

### 1. Clone the Repository

```bash
git clone https://github.com/o9nn/org-torch.git
cd org-torch
```

### 2. Explore the Packages

```bash
# List all packages
ls packages/

# View package details
cat PACKAGE-INDEX.md

# Check a specific package
ls packages/torch7/
cat packages/torch7/README.md
```

### 3. Build (Optional)

If you want to build and install Torch:

```bash
# Build all packages to ~/torch-install
./build-all.sh

# Or specify a custom location
./build-all.sh /usr/local/torch
```

## Key Files to Read

Start with these documents to understand the repository:

1. **README.md** - Main documentation and overview
2. **PACKAGES.md** - List of all integrated packages
3. **PACKAGE-INDEX.md** - Categorized package index
4. **INTEGRATION-SUMMARY.md** - Detailed integration summary
5. **CONTRIBUTING.md** - How to contribute
6. **SECURITY.md** - Security guidelines

## Common Tasks

### Viewing Package Information

```bash
# See package categories
cat PACKAGE-INDEX.md

# View package manifest
cat PACKAGES.md

# Check package details
python3 generate-index.py
```

### Testing the Integration

```bash
# Run integration tests
./test-integration.sh
```

### Updating Packages

```bash
# Refresh all packages from upstream
./clone-repos.sh

# This will update to latest versions
```

### Building Specific Packages

```bash
# Navigate to package
cd packages/torch7

# Follow package-specific build instructions
cat README.md
```

## Package Structure

Each package in `packages/` maintains its original structure:

```
packages/
├── torch7/          # Core Torch library
│   ├── CMakeLists.txt
│   ├── README.md
│   ├── init.lua
│   └── ...
├── nn/              # Neural networks
│   ├── CMakeLists.txt
│   ├── README.md
│   └── ...
└── [31 more packages...]
```

## Build Requirements

To build packages, you may need:

- **CMake** (3.0+) - For CMake-based packages
- **LuaRocks** - For Lua packages
- **GCC/Clang** - C/C++ compiler
- **CUDA** (optional) - For GPU packages
- **Make** - Build system

### Installing Dependencies (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install cmake gcc g++ make
```

### Installing Dependencies (macOS)

```bash
brew install cmake gcc make
```

## Key Packages

### Core
- **torch7** - Main Torch library
- **nn** - Neural networks
- **TH** - Tensor library

### CUDA (GPU Support)
- **cutorch** - CUDA backend
- **cunn** - CUDA neural networks

### Utilities
- **optim** - Optimization
- **image** - Image processing
- **threads** - Multi-threading

### See PACKAGES.md for complete list

## Integration Details

This monorepo was created by:
1. ✅ Cloning all 33 torch repositories
2. ✅ Removing `.git` directories
3. ✅ Organizing under `packages/`
4. ✅ Adding unified build and documentation
5. ✅ Testing integration

## Help & Support

- **Documentation**: Read the .md files in the root directory
- **Package Docs**: Check individual package directories
- **Original Repos**: Visit https://github.com/torch
- **Issues**: Report via GitHub issues

## Next Steps

1. Read [README.md](README.md) for comprehensive overview
2. Check [PACKAGES.md](PACKAGES.md) to see all packages
3. Try building a package you're interested in
4. Read package-specific documentation
5. Explore the code in `packages/`

## Tips

- Use `grep -r "pattern" packages/` to search code
- Each package has its own README
- Build scripts are provided for convenience
- Integration is complete and tested

## Quick Reference

| Command | Purpose |
|---------|---------|
| `ls packages/` | List all packages |
| `./test-integration.sh` | Run tests |
| `./build-all.sh` | Build everything |
| `./clone-repos.sh` | Update packages |
| `cat PACKAGE-INDEX.md` | View package index |
| `python3 generate-index.py` | Generate new index |

## Summary

You now have:
- ✅ Complete Torch ecosystem in one repo
- ✅ All 33 packages ready to use
- ✅ Build scripts and documentation
- ✅ No submodule complexity

Happy exploring! 🔥
