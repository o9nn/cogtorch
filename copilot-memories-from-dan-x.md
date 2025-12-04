# Copilot Memories

Hey copilot it's me dan you tried to store these memories but it failed so i saved them here for you :-)

---

Now let me store some key implementation facts:

Call to store_memory
Input
{
  "subject": "NPU architecture",
  "fact": "NPU (Neural Processing Unit) implemented as hardware-style LLM coprocessor at base address 0x40001000 with 11 MMIO registers",
  "citations": "packages/ggnucash/include/ggnucash/vdev/llama-coprocessor-driver.h:26-37, packages/ggnucash/README.md:42-56",
  "reason": "The NPU implementation follows a hardware-first design philosophy where LLM inference is treated as a memory-mapped peripheral device. This architectural decision is fundamental to the entire implementation and affects how future GGUF integration and features should be added. Understanding the base address (0x40001000) and register layout is critical for any modifications to the device driver or integration with the VirtualPCB framework.",
  "category": "file_specific"
}
Failed to store memory with error: Resource not found

Call to store_memory
Input
{
  "category": "general",
  "citations": "packages/ggnucash/src/llama-coprocessor-driver.cpp:374-396",
  "fact": "Avoid recursive mutex locks: use internal helper functions (like reset_device_internal) when already holding mutex",
  "reason": "A deadlock bug was discovered and fixed where run_self_test() held a mutex and called reset_device(), which also tried to acquire the same mutex. Future code modifications must follow this pattern of creating internal helper functions (without mutex locking) for use within already-locked contexts. This prevents deadlocks in multi-threaded or self-testing scenarios.",
  "subject": "thread safety"
}
Failed to store memory with error: Resource not found

Call to store_memory
Input
{
  "category": "bootstrap_and_build",
  "citations": "packages/ggnucash/CMakeLists.txt, packages/ggnucash/build/device-admin execution",
  "fact": "ggnucash package builds with cmake and requires C++14. Build with: cd packages/ggnucash && mkdir build && cd build && cmake .. && make",
  "reason": "This build command has been verified to work successfully. Future developers or CI systems need to know the correct build procedure for the ggnucash package. The C++14 requirement is important because the code uses std::make_unique and other C++14 features, but avoids C++17 features like std::clamp.",
  "subject": "build system"
}
Failed to store memory with error: Resource not found

Call to store_memory
Input
{
  "category": "general",
  "citations": "packages/ggnucash/src/virtual-device.cpp:10-18",
  "fact": "VirtualPCB memory regions use reasonable sizes: 16MB FLASH, 16MB SRAM, 1MB PERIPH to avoid excessive allocation",
  "reason": "Initial implementation tried to allocate 256MB per region (768MB total) which caused performance issues. Reducing to 16MB/16MB/1MB provides adequate space for virtual devices while maintaining fast initialization. This constraint should be remembered when adding new devices or expanding memory requirements.",
  "subject": "memory allocation"
}
Failed to store memory with error: Resource not found

Let me create a summary document showing the complete implementation
