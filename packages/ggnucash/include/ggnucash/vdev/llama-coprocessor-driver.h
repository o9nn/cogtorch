#ifndef GGNUCASH_VDEV_LLAMA_COPROCESSOR_DRIVER_H
#define GGNUCASH_VDEV_LLAMA_COPROCESSOR_DRIVER_H

#include "virtual-device.h"
#include <functional>
#include <chrono>
#include <atomic>
#include <mutex>

namespace ggnucash {
namespace vdev {

// ============================================================================
// MEMORY-MAPPED REGISTER LAYOUT
// ============================================================================

static constexpr uint64_t REG_BASE             = 0x40001000;  // PERIPH space
static constexpr uint64_t REG_CMD              = REG_BASE + 0x00;
static constexpr uint64_t REG_STATUS           = REG_BASE + 0x04;
static constexpr uint64_t REG_PROMPT_ADDR      = REG_BASE + 0x08;
static constexpr uint64_t REG_PROMPT_LEN       = REG_BASE + 0x0C;
static constexpr uint64_t REG_N_PREDICT        = REG_BASE + 0x10;
static constexpr uint64_t REG_TOKEN_OUT        = REG_BASE + 0x14;
static constexpr uint64_t REG_TOKEN_READY      = REG_BASE + 0x18;
static constexpr uint64_t REG_MODEL_ID         = REG_BASE + 0x1C;
static constexpr uint64_t REG_CTX_USED         = REG_BASE + 0x20;
static constexpr uint64_t REG_ERROR_CODE       = REG_BASE + 0x24;
static constexpr uint64_t REG_PERF_TOKENS_SEC  = REG_BASE + 0x28;

// Command bits
static constexpr uint32_t CMD_RESET       = 0x01;
static constexpr uint32_t CMD_LOAD_MODEL  = 0x02;
static constexpr uint32_t CMD_START_INF   = 0x04;
static constexpr uint32_t CMD_SOFT_STOP   = 0x08;

// Status bits
static constexpr uint32_t STATUS_IDLE         = 0x01;
static constexpr uint32_t STATUS_BUSY         = 0x02;
static constexpr uint32_t STATUS_EOG          = 0x04;
static constexpr uint32_t STATUS_ERROR        = 0x08;
static constexpr uint32_t STATUS_MODEL_READY  = 0x10;
static constexpr uint32_t STATUS_TOKEN_READY  = 0x20;

// ============================================================================
// CONFIGURATION STRUCTURES
// ============================================================================

struct LlamaModelConfig {
    std::string model_path;
    std::string model_name;
    int32_t     n_ctx          = 4096;
    int32_t     n_threads      = 4;
    int32_t     n_gpu_layers   = 0;
    int32_t     batch_size     = 1;
    bool        offload_kv_cache = false;
    bool        low_vram_mode    = false;
};

struct LlamaSequenceConfig {
    int32_t     n_predict      = 128;
    int32_t     max_ctx        = 4096;
    bool        echo_prompt    = false;
    bool        stream_tokens  = true;
    std::string system_prompt;
};

struct LlamaTelemetry {
    double   tokens_per_second = 0.0;
    uint64_t total_tokens_generated = 0;
    uint64_t total_prompts = 0;
    uint64_t last_prompt_tokens = 0;
    uint64_t last_completion_tokens = 0;
    std::chrono::steady_clock::time_point last_inference_start;
    std::chrono::steady_clock::time_point last_inference_end;
};

// ============================================================================
// ENTELECHY STRUCTURES (Vital Actualization Framework)
// ============================================================================

struct OntologicalHealth {
    double foundation_integrity;      // VirtualPCB infrastructure health
    double core_completeness;         // LlamaCoprocessorDriver implementation
    double specialized_features;      // Advanced features (KV-cache, GPU, etc.)
    double architectural_coherence;   // Overall structural health
};

struct TeleologicalAlignment {
    double phase_completion[5];       // Progress per development phase
    double roadmap_alignment;         // 0.0-1.0
    double actualization_trajectory;  // Growth vector
    double purpose_clarity;           // Goal definition clarity
};

struct CognitiveCompleteness {
    double inference_quality;         // GGUF model execution quality
    double performance_intelligence;  // Telemetry effectiveness
    double meta_cognitive_depth;      // Self-awareness level
    double overall_cognition;         // Combined cognitive health
};

struct IntegrativeHealth {
    double hardware_integration;      // VirtualPCB attachment
    double software_coherence;        // API consistency
    double system_unity;              // Device coexistence
    double overall_integration;       // Holistic integration score
};

struct EvolutionaryPotential {
    int    todo_count;                // Remaining work items
    int    fixme_count;               // Issues to resolve
    double implementation_depth;      // How "real" vs "stubbed"
    double self_improvement_capacity; // Potential for growth
    double evolutionary_fitness;      // Overall growth potential
};

// ============================================================================
// ONTOGENESIS STRUCTURES (Self-Generation Framework)
// ============================================================================

struct NPUGenome {
    std::string id;                   // Unique NPU instance ID
    int generation;                   // Evolution generation
    std::vector<std::string> lineage; // Ancestor IDs
    
    struct {
        std::vector<double> ontological;
        std::vector<double> teleological;
        std::vector<double> cognitive;
        std::vector<double> integrative;
        std::vector<double> evolutionary;
    } genes;
    
    double fitness;                   // Overall actualization score
    int age;                          // System maturity
    double actualization_level;       // Degree of potential realized
};

struct GenerationStats {
    int generation;
    double best_fitness;
    double avg_fitness;
    double diversity;
};

struct EvolutionConfig {
    int population_size = 20;
    double mutation_rate = 0.15;
    double crossover_rate = 0.8;
    double elitism_rate = 0.1;
    int max_generations = 100;
    double fitness_threshold = 0.9;
};

struct NPUSelfAssessment {
    OntologicalHealth ontological;
    TeleologicalAlignment teleological;
    CognitiveCompleteness cognitive;
    IntegrativeHealth integrative;
    EvolutionaryPotential evolutionary;
    
    double overall_actualization;
    double fitness_score;
    std::vector<std::string> improvement_recommendations;
};

// ============================================================================
// LLAMA COPROCESSOR DRIVER
// ============================================================================

// Token callback for streaming
using TokenCallback = std::function<void(const std::string&, int32_t, bool)>;

class LlamaCoprocessorDriver : public DeviceDriver {
public:
    LlamaCoprocessorDriver();
    virtual ~LlamaCoprocessorDriver();
    
    // DeviceDriver interface
    bool load(VirtualPCB* pcb_) override;
    bool initialize() override;
    bool probe() override;
    bool remove() override;
    
    std::string get_device_name() const override { return "LlamaCoprocessor"; }
    std::string get_device_version() const override { return "1.0.0-entelechy"; }
    uint64_t get_base_address() const override { return REG_BASE; }
    
    // Configuration
    void set_model_config(const LlamaModelConfig& cfg);
    LlamaModelConfig get_model_config() const { return model_config_; }
    
    // Model management
    bool load_model();
    bool unload_model();
    bool is_model_loaded() const;
    
    // Low-level MMIO API (hardware-style interface)
    bool configure_inference(uint64_t prompt_addr, uint32_t prompt_len,
                           const LlamaSequenceConfig& seq_cfg);
    bool start_inference();
    uint32_t read_status() const;
    bool token_available() const;
    int32_t read_token();
    bool reset_device();
    bool is_busy() const;
    bool has_error() const;
    uint32_t get_error_code() const;
    
    // High-level convenience API
    std::string infer(const std::string& prompt,
                     const LlamaSequenceConfig& seq_cfg);
    bool infer_streaming(const std::string& prompt,
                        const LlamaSequenceConfig& seq_cfg,
                        TokenCallback on_token);
    
    // Telemetry & diagnostics
    LlamaTelemetry get_telemetry() const { return telemetry_; }
    std::string get_device_status_string() const;
    std::string get_hardware_diagnostics();
    bool run_self_test();
    
    // Entelechy: Vital Actualization API
    NPUSelfAssessment assess_self() const;
    double get_actualization_score() const;
    double get_completeness_score() const;
    OntologicalHealth assess_ontological_dimension() const;
    TeleologicalAlignment assess_teleological_dimension() const;
    CognitiveCompleteness assess_cognitive_dimension() const;
    IntegrativeHealth assess_integrative_dimension() const;
    EvolutionaryPotential assess_evolutionary_dimension() const;
    
    // Ontogenesis: Self-Generation API
    NPUGenome get_genome() const { return genome_; }
    void set_genome(const NPUGenome& genome) { genome_ = genome; }
    double calculate_fitness() const;
    
private:
    // MMIO register access helpers
    void write_reg32(uint64_t addr, uint32_t value);
    uint32_t read_reg32(uint64_t addr) const;
    
    // Internal helpers (no mutex locking)
    bool reset_device_internal();
    
    // Internal state
    LlamaModelConfig model_config_;
    LlamaTelemetry telemetry_;
    NPUGenome genome_;
    
    mutable std::mutex mutex_;
    std::atomic<bool> model_loaded_{false};
    std::atomic<bool> inference_active_{false};
};

// ============================================================================
// ONTOGENESIS HELPER FUNCTIONS
// ============================================================================

class NPUOntogenesis {
public:
    // Self-generation
    static std::shared_ptr<LlamaCoprocessorDriver> 
    self_generate(const LlamaCoprocessorDriver& parent);
    
    // Self-optimization
    static void self_optimize(LlamaCoprocessorDriver* npu, int iterations);
    
    // Reproduction (genetic crossover)
    static std::shared_ptr<LlamaCoprocessorDriver>
    self_reproduce(const LlamaCoprocessorDriver& parent1,
                   const LlamaCoprocessorDriver& parent2);
    
    // Population evolution
    static std::vector<GenerationStats>
    evolve_population(const EvolutionConfig& config,
                     const std::vector<std::shared_ptr<LlamaCoprocessorDriver>>& seeds);
    
private:
    static NPUGenome mutate_genome(const NPUGenome& parent);
    static NPUGenome crossover_genomes(const NPUGenome& p1, const NPUGenome& p2);
    static void apply_genetic_traits(LlamaCoprocessorDriver* npu, const NPUGenome& genome);
};

} // namespace vdev
} // namespace ggnucash

#endif // GGNUCASH_VDEV_LLAMA_COPROCESSOR_DRIVER_H
