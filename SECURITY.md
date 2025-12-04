# Security Policy

## Reporting Security Vulnerabilities

If you discover a security vulnerability in this monorepo, please report it by:

1. **Do NOT** open a public issue
2. Email the maintainers directly or use GitHub's private security advisory feature
3. Include detailed information about the vulnerability:
   - Description of the issue
   - Steps to reproduce
   - Potential impact
   - Suggested fix (if available)

## Security Considerations

### Package Integration

This monorepo integrates multiple packages from the Torch organization. Each package:
- Maintains its original code and functionality
- May have its own security considerations
- Should be evaluated independently for security

### Build Scripts

The included build scripts (`build-all.sh`, `clone-repos.sh`) are provided for convenience and:
- Should be reviewed before execution
- Run with appropriate permissions
- May require external dependencies (CMake, LuaRocks, etc.)

### Third-Party Code

All packages in the `packages/` directory are from the official Torch organization:
- Source: https://github.com/torch/*
- Each package may have its own license and security policies
- Refer to individual package directories for specific details

## Best Practices

When using this monorepo:

1. **Review Code**: Always review code before building or running
2. **Update Regularly**: Use `clone-repos.sh` to update to latest versions
3. **Build Isolation**: Build in isolated environments when possible
4. **Dependency Management**: Keep build tools and dependencies up to date
5. **Access Control**: Limit write access to the repository
6. **Audit Logs**: Monitor changes and commits

## Known Considerations

- Some packages include C/C++ code that compiles to native binaries
- CUDA packages require NVIDIA drivers and may have specific security considerations
- LuaJIT FFI interfaces provide low-level access that should be used carefully
- Network operations in some packages should be used with caution

## Supported Versions

This monorepo tracks the latest versions of all Torch packages. For specific version security:
- Refer to individual package documentation in `packages/<package-name>/`
- Check the original repositories at https://github.com/torch/

## Security Updates

To get security updates:
1. Run `./clone-repos.sh` to refresh all packages from upstream
2. Review changes before committing
3. Test thoroughly after updates
4. Follow individual package security advisories

## Additional Resources

- Torch Organization: https://github.com/torch
- Individual package security policies in their respective directories
- General Lua security best practices: https://www.lua.org/
