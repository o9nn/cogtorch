# Contributing to Torch Monorepo

Thank you for your interest in contributing to the Torch monorepo! This document provides guidelines for contributing to this integrated repository.

## Repository Structure

This is a monorepo that integrates all Torch organization repositories into a single cohesive whole. All packages are located in the `packages/` directory, with their original structure preserved.

## Getting Started

### Cloning the Repository

```bash
git clone https://github.com/o9nn/org-torch.git
cd org-torch
```

### Understanding the Layout

```
org-torch/
├── packages/          # All Torch packages
│   ├── torch7/       # Core library
│   ├── nn/           # Neural networks
│   └── ...           # Other packages
├── clone-repos.sh    # Script to update packages
├── build-all.sh      # Unified build script
├── README.md         # Main documentation
├── PACKAGES.md       # Package manifest
└── CONTRIBUTING.md   # This file
```

## Making Changes

### Working on Individual Packages

Each package in the `packages/` directory maintains its original structure:

1. Navigate to the package you want to work on:
   ```bash
   cd packages/<package-name>
   ```

2. Make your changes following the package's conventions

3. Test your changes according to the package's testing procedures

### Adding New Packages

If you want to add a new package from the Torch organization:

1. Edit `clone-repos.sh` and add the repository name to the `repos` array

2. Run the script to clone the new package:
   ```bash
   ./clone-repos.sh
   ```

3. Update `PACKAGES.md` to include the new package

4. Update `README.md` if the package is significant

### Building and Testing

#### Build All Packages

```bash
./build-all.sh [install-prefix]
```

#### Build Individual Package

Navigate to the package directory and follow its build instructions:

```bash
cd packages/<package-name>
# Follow package-specific build instructions
```

## Integration Principles

This monorepo follows these principles:

1. **No Git Submodules**: All repositories are integrated directly, with `.git` directories removed

2. **Preserved Structure**: Each package maintains its original directory structure for compatibility

3. **Unified Access**: All packages are accessible through a single repository

4. **Cohesive Whole**: The monorepo acts as a singular entity representing the entire Torch ecosystem

5. **Easy Updates**: The `clone-repos.sh` script allows refreshing all packages from upstream

## Commit Guidelines

### Commit Message Format

```
<type>(<scope>): <subject>

<body>

<footer>
```

#### Types
- **feat**: New feature
- **fix**: Bug fix
- **docs**: Documentation changes
- **style**: Code style changes (formatting, etc.)
- **refactor**: Code refactoring
- **test**: Adding or updating tests
- **chore**: Maintenance tasks
- **build**: Build system changes

#### Scope
The scope should indicate which package(s) are affected:
- `torch7`: Changes to core Torch
- `nn`: Changes to neural network library
- `mono`: Changes to monorepo infrastructure
- `docs`: Documentation changes
- `build`: Build system changes

#### Examples

```
feat(nn): add new activation function

Add support for Mish activation function in nn package

Closes #123
```

```
docs(mono): update README with build instructions

Add detailed instructions for building individual packages
```

## Pull Request Process

1. **Create a Branch**: Create a feature branch for your changes
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make Changes**: Implement your changes following the guidelines above

3. **Test**: Ensure your changes work correctly
   - Build affected packages
   - Run package-specific tests
   - Verify integration with dependent packages

4. **Document**: Update documentation as needed
   - Package README files
   - Main README.md
   - PACKAGES.md (if adding/removing packages)

5. **Commit**: Commit your changes with descriptive messages

6. **Push**: Push your branch to the repository
   ```bash
   git push origin feature/your-feature-name
   ```

7. **Create PR**: Open a pull request with:
   - Clear description of changes
   - Rationale for the changes
   - Testing performed
   - Any breaking changes or migration notes

## Code Style

Each package may have its own coding style. Please:
- Follow the existing style in the package you're modifying
- Use consistent indentation
- Add comments for complex logic
- Keep functions focused and modular

## Testing

- Ensure existing tests pass before submitting changes
- Add tests for new functionality
- Follow the testing patterns established in each package

## Documentation

- Update README files when adding features
- Document public APIs and functions
- Include usage examples for new features
- Keep PACKAGES.md up to date

## Questions or Problems?

If you have questions or encounter issues:
- Check existing documentation in package directories
- Review similar implementations in other packages
- Open an issue describing your problem or question

## License

By contributing to this repository, you agree that your contributions will be licensed under the same license as the project (see LICENSE file).

## Recognition

All contributors will be recognized in the project. Thank you for helping make Torch better!
