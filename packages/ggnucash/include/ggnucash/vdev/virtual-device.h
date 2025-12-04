#ifndef GGNUCASH_VDEV_VIRTUAL_DEVICE_H
#define GGNUCASH_VDEV_VIRTUAL_DEVICE_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>

namespace ggnucash {
namespace vdev {

// Memory region types
enum class MemoryRegionType {
    FLASH,    // Non-volatile program storage
    SRAM,     // Volatile working memory
    PERIPH,   // Memory-mapped I/O peripherals
    RESERVED  // Reserved/unmapped
};

// Memory region descriptor
struct MemoryRegion {
    uint64_t base_addr;
    uint64_t size;
    MemoryRegionType type;
    std::string name;
    std::vector<uint8_t> data;
    
    MemoryRegion(uint64_t base, uint64_t sz, MemoryRegionType t, const std::string& n)
        : base_addr(base), size(sz), type(t), name(n) {
        data.resize(sz, 0);
    }
    
    bool contains(uint64_t addr) const {
        return addr >= base_addr && addr < (base_addr + size);
    }
};

// Forward declaration
class DeviceDriver;

// VirtualPCB - The "motherboard" for virtual devices
class VirtualPCB {
public:
    VirtualPCB();
    virtual ~VirtualPCB();
    
    // Memory region management
    void add_memory_region(uint64_t base_addr, uint64_t size, 
                          MemoryRegionType type, const std::string& name);
    MemoryRegion* get_region(uint64_t addr);
    const MemoryRegion* get_region(uint64_t addr) const;
    
    // Memory access
    uint8_t read_memory(uint64_t addr) const;
    void write_memory(uint64_t addr, uint8_t value);
    
    // Bulk memory operations
    void read_memory_block(uint64_t addr, uint8_t* buffer, size_t size) const;
    void write_memory_block(uint64_t addr, const uint8_t* buffer, size_t size);
    
    // Device driver management
    void attach_driver(DeviceDriver* driver);
    void detach_driver(DeviceDriver* driver);
    
    // System information
    std::string get_memory_map_string() const;
    size_t get_total_memory() const;
    
private:
    std::vector<std::unique_ptr<MemoryRegion>> memory_regions_;
    std::vector<DeviceDriver*> attached_drivers_;
};

// Base class for all device drivers
class DeviceDriver {
public:
    virtual ~DeviceDriver() = default;
    
    // Device lifecycle
    virtual bool load(VirtualPCB* pcb) = 0;     // Attach to PCB
    virtual bool initialize() = 0;               // Initialize hardware
    virtual bool probe() = 0;                    // Detect device
    virtual bool remove() = 0;                   // Cleanup
    
    // Device information
    virtual std::string get_device_name() const = 0;
    virtual std::string get_device_version() const = 0;
    virtual uint64_t get_base_address() const = 0;
    
protected:
    VirtualPCB* pcb = nullptr;
};

} // namespace vdev
} // namespace ggnucash

#endif // GGNUCASH_VDEV_VIRTUAL_DEVICE_H
