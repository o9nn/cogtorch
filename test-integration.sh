#!/bin/bash

# Integration test for the Torch monorepo
# Validates that all packages are correctly integrated

set -e

PACKAGES_DIR="packages"
EXPECTED_COUNT=33

echo "=========================================="
echo "Torch Monorepo Integration Test"
echo "=========================================="
echo ""

# Test 1: Check packages directory exists
echo "Test 1: Checking packages directory..."
if [ ! -d "$PACKAGES_DIR" ]; then
    echo "❌ FAIL: packages directory not found"
    exit 1
fi
echo "✓ PASS: packages directory exists"

# Test 2: Count packages
echo "Test 2: Counting packages..."
ACTUAL_COUNT=$(ls "$PACKAGES_DIR" | wc -l)
if [ "$ACTUAL_COUNT" -ne "$EXPECTED_COUNT" ]; then
    echo "❌ FAIL: Expected $EXPECTED_COUNT packages, found $ACTUAL_COUNT"
    exit 1
fi
echo "✓ PASS: Found $ACTUAL_COUNT packages (expected $EXPECTED_COUNT)"

# Test 3: Verify no .git directories in packages
echo "Test 3: Checking for .git directories in packages..."
GIT_DIRS=$(find "$PACKAGES_DIR" -name ".git" -type d | wc -l)
if [ "$GIT_DIRS" -ne 0 ]; then
    echo "❌ FAIL: Found $GIT_DIRS .git directories in packages"
    find "$PACKAGES_DIR" -name ".git" -type d
    exit 1
fi
echo "✓ PASS: No .git directories found in packages"

# Test 4: Check key packages exist
echo "Test 4: Verifying key packages..."
KEY_PACKAGES=("torch7" "nn" "cutorch" "cunn" "optim" "image")
for pkg in "${KEY_PACKAGES[@]}"; do
    if [ ! -d "$PACKAGES_DIR/$pkg" ]; then
        echo "❌ FAIL: Key package $pkg not found"
        exit 1
    fi
done
echo "✓ PASS: All key packages present"

# Test 5: Check for README files in key packages
echo "Test 5: Checking for documentation..."
for pkg in "${KEY_PACKAGES[@]}"; do
    if ! find "$PACKAGES_DIR/$pkg" -iname "readme*" | grep -q .; then
        echo "⚠ WARNING: No README found in $pkg"
    fi
done
echo "✓ PASS: Documentation check completed"

# Test 6: Check for build files
echo "Test 6: Checking for build configurations..."
CMAKE_COUNT=$(find "$PACKAGES_DIR" -name "CMakeLists.txt" | wc -l)
ROCKSPEC_COUNT=$(find "$PACKAGES_DIR" -name "*.rockspec" | wc -l)
echo "  - Found $CMAKE_COUNT CMakeLists.txt files"
echo "  - Found $ROCKSPEC_COUNT .rockspec files"
if [ "$CMAKE_COUNT" -eq 0 ] && [ "$ROCKSPEC_COUNT" -eq 0 ]; then
    echo "❌ FAIL: No build configuration files found"
    exit 1
fi
echo "✓ PASS: Build configurations present"

# Test 7: Verify monorepo structure files
echo "Test 7: Checking monorepo structure files..."
REQUIRED_FILES=("README.md" "PACKAGES.md" "CONTRIBUTING.md" "clone-repos.sh" "build-all.sh" ".gitignore")
for file in "${REQUIRED_FILES[@]}"; do
    if [ ! -f "$file" ]; then
        echo "❌ FAIL: Required file $file not found"
        exit 1
    fi
done
echo "✓ PASS: All monorepo structure files present"

# Test 8: Check package index
echo "Test 8: Verifying package index..."
if [ ! -f "PACKAGE-INDEX.md" ] || [ ! -f "package-index.json" ]; then
    echo "❌ FAIL: Package index files not found"
    exit 1
fi
echo "✓ PASS: Package index files present"

# Test 9: Verify no orphaned git files
echo "Test 9: Checking for orphaned git files..."
if find "$PACKAGES_DIR" -name ".gitignore" -o -name ".gitmodules" -o -name ".gitattributes" | grep -q .; then
    echo "⚠ INFO: Found git configuration files (this is acceptable)"
else
    echo "✓ INFO: No git configuration files found in packages"
fi

# Test 10: Check disk space usage
echo "Test 10: Checking disk space..."
SIZE=$(du -sh "$PACKAGES_DIR" | cut -f1)
echo "  - Total package size: $SIZE"
echo "✓ PASS: Disk space check completed"

echo ""
echo "=========================================="
echo "✓ All tests passed!"
echo "=========================================="
echo "Monorepo integration is successful."
echo ""
echo "Summary:"
echo "  - Packages: $ACTUAL_COUNT"
echo "  - CMake packages: $CMAKE_COUNT"
echo "  - LuaRocks packages: $ROCKSPEC_COUNT"
echo "  - Total size: $SIZE"
echo ""
