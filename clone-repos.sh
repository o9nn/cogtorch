#!/bin/bash

# Script to clone all torch organization repositories into the monorepo
# This integrates all torch repos into a single cohesive monorepo structure

set -e

PACKAGES_DIR="packages"
ORG="torch"

# List of torch repositories to clone (from torch organization)
repos=(
    "torch7"
    "nn"
    "tutorials"
    "distro"
    "demos"
    "cutorch"
    "cunn"
    "nngraph"
    "threads"
    "qtlua"
    "image"
    "optim"
    "luajit-rocks"
    "tds"
    "trepl"
    "xlua"
    "torch.github.io"
    "ezinstall"
    "class"
    "rocks"
    "rnn"
    "TH"
    "gnuplot"
    "argcheck"
    "paths"
    "senna"
    "graph"
    "sdl2-ffi"
    "cwrap"
    "xt"
    "sys"
    "ffi"
    "sundown-ffi"
    "qttorch"
    "hash"
    "cairo-ffi"
    "dok"
    "socketfile"
    "rational"
    "env"
    "vector"
)

echo "Cloning torch organization repositories into $PACKAGES_DIR..."

# Create packages directory if it doesn't exist
mkdir -p "$PACKAGES_DIR"

# Clone each repository
for repo in "${repos[@]}"; do
    echo "Cloning $repo..."
    if [ -d "$PACKAGES_DIR/$repo" ]; then
        echo "  - $repo already exists, skipping..."
    else
        git clone --depth 1 "https://github.com/$ORG/$repo.git" "$PACKAGES_DIR/$repo" || {
            echo "  - Warning: Failed to clone $repo, skipping..."
            continue
        }
        
        # Remove .git directory to integrate into monorepo
        if [ -d "$PACKAGES_DIR/$repo/.git" ]; then
            echo "  - Removing .git directory from $repo..."
            rm -rf "$PACKAGES_DIR/$repo/.git"
        fi
    fi
done

echo "Repository cloning complete!"
echo "Total repositories integrated: ${#repos[@]}"
