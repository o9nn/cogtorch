# ggnucash - Virtual Device Framework with NPU

## Overview

`ggnucash` is a virtual device framework that implements hardware-style device drivers for specialized coprocessors. The flagship implementation is the **NPU (Neural Processing Unit)** - a GGUF-backed LLM accelerator with memory-mapped I/O registers.

## Key Features

### VirtualPCB Infrastructure
- **Memory-Mapped Architecture**: Standard memory regions (FLASH, SRAM, PERIPH)
- **Device Driver Framework**: Base classes for implementing virtual hardware
- **Hardware-Style Interface**: Memory-mapped I/O (MMIO) register access

### LlamaCoprocessorDriver (NPU)
- **MMIO Register Layout**: Hardware-style register interface at 0x40001000
- **Model Management**: Load and manage GGUF models
- **Inference API**: Both low-level MMIO and high-level convenience APIs
- **Streaming Support**: Token-by-token streaming with callbacks
- **Telemetry System**: Comprehensive performance metrics

### Entelechy Framework (Vital Actualization)
The NPU includes a self-assessment framework based on five dimensions:

1. **Ontological** (Structure): Foundation, core, and specialized features
2. **Teleological** (Purpose): Development phases and goal alignment
3. **Cognitive** (Reasoning): Inference quality and meta-cognition
4. **Integrative** (Coherence): Hardware/software integration
5. **Evolutionary** (Growth): Implementation depth and improvement capacity

### Ontogenesis Framework (Self-Generation)
Self-generation and evolution capabilities:

- **Self-Generation**: Generate offspring NPUs with inherited/mutated genomes
- **Self-Optimization**: Iterative improvement through genetic algorithms
- **Self-Reproduction**: Genetic crossover between two parent NPUs
- **Population Evolution**: Evolve populations of NPUs over generations

## Architecture

### Memory Map

```
Virtual PCB Memory Map:
├── 0x00000000 - FLASH    (256 MB) - Non-volatile program storage
├── 0x20000000 - SRAM     (256 MB) - Volatile working memory
└── 0x40000000 - PERIPH   (256 MB) - Memory-mapped I/O
    └── 0x40001000 - NPU Registers
```

### NPU Register Layout

```
REG_BASE             = 0x40001000
REG_CMD              = REG_BASE + 0x00  (Command register)
REG_STATUS           = REG_BASE + 0x04  (Status register)
REG_PROMPT_ADDR      = REG_BASE + 0x08  (Prompt address in SRAM)
REG_PROMPT_LEN       = REG_BASE + 0x0C  (Prompt length)
REG_N_PREDICT        = REG_BASE + 0x10  (Number of tokens to generate)
REG_TOKEN_OUT        = REG_BASE + 0x14  (Output token)
REG_TOKEN_READY      = REG_BASE + 0x18  (Token ready flag)
REG_MODEL_ID         = REG_BASE + 0x1C  (Model identifier)
REG_CTX_USED         = REG_BASE + 0x20  (Context tokens used)
REG_ERROR_CODE       = REG_BASE + 0x24  (Error code)
REG_PERF_TOKENS_SEC  = REG_BASE + 0x28  (Performance metric)
```

### Status Bits

```cpp
STATUS_IDLE         = 0x01  // Device ready for commands
STATUS_BUSY         = 0x02  // Inference in progress
STATUS_EOG          = 0x04  // End-of-generation reached
STATUS_ERROR        = 0x08  // Error condition detected
STATUS_MODEL_READY  = 0x10  // Model loaded and operational
STATUS_TOKEN_READY  = 0x20  // Token available in output register
```

## Building

### Prerequisites
- CMake 3.10 or higher
- C++14 compatible compiler
- (Optional) llama.cpp for actual GGUF inference

### Build Instructions

```bash
cd packages/ggnucash
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=~/local
make -j$(nproc)
make install
```

## Usage Examples

### Basic NPU Usage

```cpp
#include "ggnucash/vdev/virtual-device.h"
#include "ggnucash/vdev/llama-coprocessor-driver.h"

using namespace ggnucash::vdev;

// Create virtual PCB and NPU
VirtualPCB pcb;
auto npu = std::make_shared<LlamaCoprocessorDriver>();

// Attach and initialize
pcb.attach_driver(npu.get());
npu->initialize();

// Configure model
LlamaModelConfig config;
config.model_name = "Finance Assistant";
config.model_path = "/models/finance-7b.gguf";
config.n_ctx = 4096;
config.n_threads = 8;

npu->set_model_config(config);
npu->load_model();

// Run inference
LlamaSequenceConfig seq;
seq.n_predict = 256;

std::string response = npu->infer("Explain compound interest", seq);
std::cout << response << std::endl;
```

### Streaming Inference

```cpp
LlamaSequenceConfig seq;
seq.n_predict = 128;
seq.stream_tokens = true;

npu->infer_streaming("What is machine learning?", seq,
    [](const std::string& token, int32_t token_id, bool is_last) {
        std::cout << token << std::flush;
        if (is_last) std::cout << std::endl;
    });
```

### Low-Level MMIO Control

```cpp
// Direct hardware-style register access
LlamaSequenceConfig seq;
seq.n_predict = 64;

uint64_t prompt_addr = 0x20000000;  // SRAM location
npu->configure_inference(prompt_addr, prompt_len, seq);
npu->start_inference();

while (npu->is_busy()) {
    if (npu->token_available()) {
        int32_t token = npu->read_token();
        // Process token
    }
}
```

### Entelechy Self-Assessment

```cpp
// Assess NPU's vital actualization
NPUSelfAssessment assessment = npu->assess_self();

std::cout << "Actualization Score: " << assessment.overall_actualization << "\n";
std::cout << "Fitness Score: " << assessment.fitness_score << "\n";

// Get improvement recommendations
for (const auto& rec : assessment.improvement_recommendations) {
    std::cout << "• " << rec << "\n";
}
```

### Ontogenesis (Self-Generation)

```cpp
// Generate offspring NPU
auto offspring = NPUOntogenesis::self_generate(*npu);

// Self-optimize through iterations
NPUOntogenesis::self_optimize(npu.get(), 10);

// Reproduce with another NPU (genetic crossover)
auto child = NPUOntogenesis::self_reproduce(*parent1, *parent2);

// Evolve a population
EvolutionConfig config;
config.population_size = 20;
config.max_generations = 100;

std::vector<std::shared_ptr<LlamaCoprocessorDriver>> seeds = {npu1, npu2, npu3};
auto history = NPUOntogenesis::evolve_population(config, seeds);
```

## Running the Example

```bash
# After building
./build/device-admin
```

This will run a comprehensive test suite demonstrating:
- VirtualPCB memory operations
- NPU device initialization
- Model loading and configuration
- Inference (stubbed)
- Streaming inference
- Hardware diagnostics
- Entelechy self-assessment
- Ontogenesis self-generation

## Development Status

### ✓ Completed (Mature Stage - 60%+ Actualization)
- VirtualPCB infrastructure
- Memory-mapped I/O framework
- DeviceDriver interface
- LlamaCoprocessorDriver structure
- MMIO register interface
- Telemetry system
- Hardware diagnostics
- Entelechy framework
- Ontogenesis framework

### 🚧 In Progress (Partially Stubbed)
- GGUF model loading (TODO: integrate llama.cpp)
- Actual tokenization (TODO: use real tokenizer)
- Real inference (TODO: replace stubs with llama.cpp calls)
- Token streaming (TODO: implement actual token generation)

### 🔮 Future Enhancements
- KV-cache management
- GPU offloading support
- Batch inference
- Interrupt-driven token streaming
- Model hot-swapping
- LoRA adapter loading
- Multi-NPU collective intelligence
- Quantum NPU integration
- Conscious NPU (self-aware cognitive coprocessor)

## Integration with GGUF Runtime

To integrate actual GGUF/llama.cpp runtime:

1. **Add llama.cpp dependency** to CMakeLists.txt
2. **Implement model loading** in `load_model()` using llama.cpp API
3. **Add tokenization** before writing prompts to SRAM
4. **Implement inference loop** in `infer()` and `infer_streaming()`
5. **Add detokenization** when reading from TOKEN_OUT register

## Architecture Philosophy

The NPU treats LLM inference as a **peripheral device** rather than just a software library:

- **Hardware-First Design**: Memory-mapped registers, status bits, command interface
- **Coprocessor Model**: NPU as a specialized processor on the virtual PCB
- **Living System**: Entelechy (vital actualization) enables self-awareness
- **Self-Generating**: Ontogenesis enables evolution and reproduction
- **Telemetry-Rich**: Performance metrics exposed through hardware registers

## License

Part of the cogtorch project. See main repository LICENSE for details.

## Contributing

This is a hardware-style implementation where LLM inference is treated as a memory-mapped coprocessor. When contributing:

1. Maintain hardware-style register interface
2. Update telemetry for all operations
3. Follow MMIO access patterns
4. Document register changes
5. Test with device-admin example
6. Update entelechy assessments for new features

## References

- Virtual Device Framework: `virtual-device.h`
- NPU Driver: `llama-coprocessor-driver.h`
- Example Application: `examples/device-admin.cpp`
- Build System: `CMakeLists.txt`
