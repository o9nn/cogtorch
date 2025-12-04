# Torch Monorepo Package Manifest

This file lists all packages integrated into the org-torch monorepo from the Torch organization.

## Package List

| Package | Description | Language | Original URL |
|---------|-------------|----------|--------------|
| torch7 | Core Torch library | C/Lua | https://github.com/torch/torch7 |
| nn | Neural network library | Lua | https://github.com/torch/nn |
| cutorch | CUDA backend for Torch7 | CUDA | https://github.com/torch/cutorch |
| cunn | CUDA neural network library | CUDA | https://github.com/torch/cunn |
| optim | Numeric optimization package | Lua | https://github.com/torch/optim |
| image | Image processing toolbox | C/Lua | https://github.com/torch/image |
| threads | Multi-threading with transparent data exchange | Lua | https://github.com/torch/threads |
| tutorials | Machine learning tutorials | Jupyter Notebook | https://github.com/torch/tutorials |
| demos | Demo applications | Lua | https://github.com/torch/demos |
| distro | Torch installation in a self-contained folder | CMake | https://github.com/torch/distro |
| nngraph | Graph computation for neural networks | Lua | https://github.com/torch/nngraph |
| qtlua | Lua interface to QT library | C++ | https://github.com/torch/qtlua |
| luajit-rocks | LuaJIT and luarocks in one location | C | https://github.com/torch/luajit-rocks |
| tds | Torch C data structures | C | https://github.com/torch/tds |
| trepl | Pure Lua-based REPL for Torch | Lua | https://github.com/torch/trepl |
| xlua | Extensions for Lua (string, table, etc.) | Lua | https://github.com/torch/xlua |
| torch.github.io | Torch website source | HTML | https://github.com/torch/torch.github.io |
| ezinstall | One-line install scripts | Shell | https://github.com/torch/ezinstall |
| class | Object-oriented programming for Lua | Lua | https://github.com/torch/class |
| rocks | Rocks packages for Torch | HTML | https://github.com/torch/rocks |
| rnn | Recurrent neural network implementations | Lua | https://github.com/torch/rnn |
| TH | Standalone C TH library | C | https://github.com/torch/TH |
| gnuplot | Gnuplot interface for visualization | Lua | https://github.com/torch/gnuplot |
| argcheck | Argument checking and function overloading | Lua | https://github.com/torch/argcheck |
| paths | Path manipulation utilities | C | https://github.com/torch/paths |
| senna | NLP SENNA interface | Lua | https://github.com/torch/senna |
| graph | Graph visualization package | Lua | https://github.com/torch/graph |
| sdl2-ffi | LuaJIT interface to SDL2 | Lua | https://github.com/torch/sdl2-ffi |
| cwrap | C wrapper utilities | Lua | https://github.com/torch/cwrap |
| xt | TH/THC C++11 wrapper | C | https://github.com/torch/xt |
| sys | System utilities | Lua | https://github.com/torch/sys |
| ffi | FFI bindings for LuaJIT-speed access | Lua | https://github.com/torch/ffi |
| sundown-ffi | LuaJIT interface to Sundown (Markdown) | C | https://github.com/torch/sundown-ffi |

## Integration Status

- **Total Packages**: 33
- **Integration Method**: Direct clone without git submodules
- **Structure**: All packages in `packages/` directory
- **Git Headers**: Removed from all packages
- **Status**: Fully integrated monorepo

## Notes

- All packages maintain their original structure for compatibility
- Each package can be built independently or as part of the whole
- Cross-package dependencies are maintained through the unified structure
- Original documentation is preserved in each package directory
