#include "ggnucash/vdev/virtual-device.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace ggnucash {
namespace vdev {

VirtualPCB::VirtualPCB() {
    // Initialize standard memory regions with more reasonable sizes
    // FLASH: 0x00000000 - 0x00FFFFFF (16 MB)
    add_memory_region(0x00000000, 16 * 1024 * 1024, MemoryRegionType::FLASH, "FLASH");
    
    // SRAM: 0x20000000 - 0x20FFFFFF (16 MB)
    add_memory_region(0x20000000, 16 * 1024 * 1024, MemoryRegionType::SRAM, "SRAM");
    
    // PERIPH: 0x40000000 - 0x400FFFFF (1 MB - enough for many devices)
    add_memory_region(0x40000000, 1 * 1024 * 1024, MemoryRegionType::PERIPH, "PERIPH");
}

VirtualPCB::~VirtualPCB() {
    // Cleanup all drivers
    for (auto* driver : attached_drivers_) {
        driver->remove();
    }
}

void VirtualPCB::add_memory_region(uint64_t base_addr, uint64_t size,
                                   MemoryRegionType type, const std::string& name) {
    auto region = std::make_unique<MemoryRegion>(base_addr, size, type, name);
    memory_regions_.push_back(std::move(region));
}

MemoryRegion* VirtualPCB::get_region(uint64_t addr) {
    for (auto& region : memory_regions_) {
        if (region->contains(addr)) {
            return region.get();
        }
    }
    return nullptr;
}

const MemoryRegion* VirtualPCB::get_region(uint64_t addr) const {
    for (const auto& region : memory_regions_) {
        if (region->contains(addr)) {
            return region.get();
        }
    }
    return nullptr;
}

uint8_t VirtualPCB::read_memory(uint64_t addr) const {
    const MemoryRegion* region = get_region(addr);
    if (!region) {
        throw std::runtime_error("Memory read fault: address 0x" + 
                               std::to_string(addr) + " is not mapped");
    }
    
    uint64_t offset = addr - region->base_addr;
    return region->data[offset];
}

void VirtualPCB::write_memory(uint64_t addr, uint8_t value) {
    MemoryRegion* region = get_region(addr);
    if (!region) {
        throw std::runtime_error("Memory write fault: address 0x" + 
                               std::to_string(addr) + " is not mapped");
    }
    
    uint64_t offset = addr - region->base_addr;
    region->data[offset] = value;
}

void VirtualPCB::read_memory_block(uint64_t addr, uint8_t* buffer, size_t size) const {
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = read_memory(addr + i);
    }
}

void VirtualPCB::write_memory_block(uint64_t addr, const uint8_t* buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        write_memory(addr + i, buffer[i]);
    }
}

void VirtualPCB::attach_driver(DeviceDriver* driver) {
    if (!driver) {
        throw std::invalid_argument("Cannot attach null driver");
    }
    
    // Check if driver is already attached
    auto it = std::find(attached_drivers_.begin(), attached_drivers_.end(), driver);
    if (it != attached_drivers_.end()) {
        return; // Already attached
    }
    
    attached_drivers_.push_back(driver);
    driver->load(this);
}

void VirtualPCB::detach_driver(DeviceDriver* driver) {
    auto it = std::find(attached_drivers_.begin(), attached_drivers_.end(), driver);
    if (it != attached_drivers_.end()) {
        (*it)->remove();
        attached_drivers_.erase(it);
    }
}

std::string VirtualPCB::get_memory_map_string() const {
    std::ostringstream oss;
    oss << "VirtualPCB Memory Map:\n";
    oss << "=====================\n";
    
    for (const auto& region : memory_regions_) {
        oss << std::hex << std::setfill('0');
        oss << region->name << ": 0x" << std::setw(8) << region->base_addr;
        oss << " - 0x" << std::setw(8) << (region->base_addr + region->size - 1);
        oss << " (" << std::dec << (region->size / (1024 * 1024)) << " MB, ";
        
        switch (region->type) {
            case MemoryRegionType::FLASH:
                oss << "FLASH";
                break;
            case MemoryRegionType::SRAM:
                oss << "SRAM";
                break;
            case MemoryRegionType::PERIPH:
                oss << "PERIPH";
                break;
            case MemoryRegionType::RESERVED:
                oss << "RESERVED";
                break;
        }
        
        oss << ")\n";
    }
    
    oss << "\nAttached Drivers: " << attached_drivers_.size() << "\n";
    for (const auto* driver : attached_drivers_) {
        oss << "  - " << driver->get_device_name() << " v" << driver->get_device_version();
        oss << " @ 0x" << std::hex << std::setw(8) << std::setfill('0') << driver->get_base_address() << "\n";
    }
    
    return oss.str();
}

size_t VirtualPCB::get_total_memory() const {
    size_t total = 0;
    for (const auto& region : memory_regions_) {
        total += region->size;
    }
    return total;
}

} // namespace vdev
} // namespace ggnucash
