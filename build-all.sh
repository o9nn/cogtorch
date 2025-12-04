#!/bin/bash

# Unified build script for the Torch monorepo
# This script helps build core Torch components in the correct order

set -e

INSTALL_PREFIX="${1:-$HOME/torch-install}"
PACKAGES_DIR="packages"

echo "=========================================="
echo "Torch Monorepo Build Script"
echo "=========================================="
echo "Install prefix: $INSTALL_PREFIX"
echo ""

# Create install directory
mkdir -p "$INSTALL_PREFIX"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

build_package() {
    local package=$1
    local build_type=${2:-cmake}
    
    echo -e "${YELLOW}Building $package...${NC}"
    
    if [ ! -d "$PACKAGES_DIR/$package" ]; then
        echo -e "${RED}Package $package not found, skipping...${NC}"
        return 1
    fi
    
    cd "$PACKAGES_DIR/$package"
    
    if [ "$build_type" = "cmake" ]; then
        if [ ! -f "CMakeLists.txt" ]; then
            echo -e "${YELLOW}No CMakeLists.txt found, skipping...${NC}"
            cd ../..
            return 0
        fi
        
        mkdir -p build
        cd build
        cmake .. -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
                 -DCMAKE_BUILD_TYPE=Release
        make -j$(nproc 2>/dev/null || echo 4)
        make install
        cd ..
        rm -rf build
    elif [ "$build_type" = "luarocks" ]; then
        if ! command -v luarocks &> /dev/null; then
            echo -e "${YELLOW}luarocks not found, skipping...${NC}"
            cd ../..
            return 0
        fi
        
        # Find rockspec file
        rockspec=$(find . -name "*.rockspec" -type f | head -1)
        if [ -n "$rockspec" ]; then
            luarocks make "$rockspec" --local
        else
            echo -e "${YELLOW}No rockspec found, skipping...${NC}"
        fi
    fi
    
    cd ../..
    echo -e "${GREEN}✓ $package built successfully${NC}"
    echo ""
}

# Build order matters for dependencies
echo "Building core Torch components..."
echo ""

# Core libraries first
build_package "TH" "cmake"
build_package "luajit-rocks" "cmake"
build_package "torch7" "cmake"

# Utility libraries
build_package "paths" "cmake"
build_package "cwrap" "luarocks"
build_package "sys" "luarocks"
build_package "xlua" "luarocks"
build_package "dok" "luarocks"
build_package "class" "luarocks"
build_package "trepl" "luarocks"

# Core extensions
build_package "nn" "cmake"
build_package "image" "cmake"
build_package "optim" "luarocks"
build_package "threads" "cmake"
build_package "tds" "cmake"

# CUDA support (if available)
if command -v nvcc &> /dev/null; then
    echo "CUDA detected, building CUDA packages..."
    build_package "cutorch" "cmake"
    build_package "cunn" "cmake"
else
    echo -e "${YELLOW}CUDA not detected, skipping CUDA packages${NC}"
fi

# Additional packages
build_package "gnuplot" "luarocks"
build_package "graph" "luarocks"
build_package "nngraph" "luarocks"
build_package "argcheck" "luarocks"

echo ""
echo "=========================================="
echo -e "${GREEN}Build complete!${NC}"
echo "=========================================="
echo "Installation directory: $INSTALL_PREFIX"
echo ""
echo "To use Torch, add the following to your environment:"
echo "  export PATH=\"$INSTALL_PREFIX/bin:\$PATH\""
echo "  export LD_LIBRARY_PATH=\"$INSTALL_PREFIX/lib:\$LD_LIBRARY_PATH\""
echo "  export LUA_PATH=\"$INSTALL_PREFIX/share/lua/5.1/?.lua;$INSTALL_PREFIX/share/lua/5.1/?/init.lua;;\""
echo "  export LUA_CPATH=\"$INSTALL_PREFIX/lib/lua/5.1/?.so;;\""
echo ""
