#!/usr/bin/env python3
"""
Package Index Generator for Torch Monorepo

This script generates an index of all packages with their descriptions
by reading from the package directories.
"""

import os
import json
from pathlib import Path

def read_package_info(package_path):
    """Extract basic information about a package."""
    info = {
        'name': os.path.basename(package_path),
        'path': str(package_path),
        'has_cmake': os.path.exists(os.path.join(package_path, 'CMakeLists.txt')),
        'has_rockspec': any(f.endswith('.rockspec') for f in os.listdir(package_path)),
        'has_readme': any(f.lower().startswith('readme') for f in os.listdir(package_path)),
    }
    
    # Try to read description from README
    readme_files = [f for f in os.listdir(package_path) if f.lower().startswith('readme')]
    if readme_files:
        readme_path = os.path.join(package_path, readme_files[0])
        try:
            with open(readme_path, 'r', encoding='utf-8', errors='ignore') as f:
                lines = f.readlines()
                # Get first non-empty line after title as description
                for i, line in enumerate(lines):
                    line = line.strip()
                    if line and not line.startswith('#') and len(line) > 10:
                        info['description'] = line[:100]
                        break
        except Exception:
            pass
    
    return info

def generate_index():
    """Generate package index."""
    packages_dir = Path('packages')
    
    if not packages_dir.exists():
        print("Error: packages directory not found")
        return
    
    packages = []
    for package_dir in sorted(packages_dir.iterdir()):
        if package_dir.is_dir():
            try:
                info = read_package_info(package_dir)
                packages.append(info)
            except Exception as e:
                print(f"Warning: Could not process {package_dir.name}: {e}")
    
    # Generate markdown index
    print(f"# Torch Monorepo Package Index")
    print(f"\nTotal Packages: {len(packages)}\n")
    print(f"Generated: {os.popen('date').read().strip()}\n")
    
    print("## Packages by Category\n")
    
    # Categorize packages
    cmake_packages = [p for p in packages if p['has_cmake']]
    luarocks_packages = [p for p in packages if p['has_rockspec']]
    
    print(f"### CMake-based Packages ({len(cmake_packages)})\n")
    for pkg in cmake_packages:
        desc = pkg.get('description', 'No description available')[:80]
        print(f"- **{pkg['name']}** - {desc}")
    
    print(f"\n### LuaRocks Packages ({len(luarocks_packages)})\n")
    for pkg in luarocks_packages:
        if not pkg['has_cmake']:  # Don't duplicate
            desc = pkg.get('description', 'No description available')[:80]
            print(f"- **{pkg['name']}** - {desc}")
    
    print("\n## All Packages (Alphabetical)\n")
    for pkg in packages:
        build_type = []
        if pkg['has_cmake']:
            build_type.append('CMake')
        if pkg['has_rockspec']:
            build_type.append('LuaRocks')
        build_str = ', '.join(build_type) if build_type else 'N/A'
        
        desc = pkg.get('description', 'No description available')[:60]
        print(f"- **{pkg['name']}** [{build_str}] - {desc}")
    
    # Generate JSON index
    index_data = {
        'packages': packages,
        'total_count': len(packages),
        'cmake_count': len(cmake_packages),
        'luarocks_count': len(luarocks_packages)
    }
    
    with open('package-index.json', 'w') as f:
        json.dump(index_data, f, indent=2)
    
    print(f"\n✓ JSON index saved to package-index.json")

if __name__ == '__main__':
    generate_index()
