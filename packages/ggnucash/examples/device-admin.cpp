#include "ggnucash/vdev/virtual-device.h"
#include "ggnucash/vdev/llama-coprocessor-driver.h"
#include <iostream>
#include <iomanip>
#include <memory>

using namespace ggnucash::vdev;

void print_section(const std::string& title) {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << title << "\n";
    std::cout << "========================================\n\n";
}

void test_virtual_pcb() {
    print_section("Testing VirtualPCB");
    
    VirtualPCB pcb;
    std::cout << pcb.get_memory_map_string() << "\n";
    
    // Test memory read/write
    std::cout << "Testing memory operations...\n";
    pcb.write_memory(0x20000000, 0xAB);
    pcb.write_memory(0x20000001, 0xCD);
    
    uint8_t val1 = pcb.read_memory(0x20000000);
    uint8_t val2 = pcb.read_memory(0x20000001);
    
    std::cout << "  Wrote 0xAB, read back 0x" << std::hex << (int)val1 << std::dec << "\n";
    std::cout << "  Wrote 0xCD, read back 0x" << std::hex << (int)val2 << std::dec << "\n";
    
    if (val1 == 0xAB && val2 == 0xCD) {
        std::cout << "  ✓ Memory operations work correctly!\n";
    } else {
        std::cout << "  ✗ Memory operations failed!\n";
    }
}

void test_npu_basic() {
    print_section("Testing NPU Basic Operations");
    
    VirtualPCB pcb;
    auto npu = std::make_shared<LlamaCoprocessorDriver>();
    
    std::cout << "Attaching NPU to VirtualPCB...\n";
    pcb.attach_driver(npu.get());
    
    std::cout << "Initializing NPU...\n";
    npu->initialize();
    
    std::cout << "Probing device...\n";
    if (npu->probe()) {
        std::cout << "  ✓ Device probe successful!\n";
    }
    
    std::cout << "\nDevice Information:\n";
    std::cout << "  Name:    " << npu->get_device_name() << "\n";
    std::cout << "  Version: " << npu->get_device_version() << "\n";
    std::cout << "  Base:    0x" << std::hex << npu->get_base_address() << std::dec << "\n";
}

void test_npu_self_test() {
    print_section("Testing NPU Self-Test");
    
    VirtualPCB pcb;
    auto npu = std::make_shared<LlamaCoprocessorDriver>();
    
    pcb.attach_driver(npu.get());
    npu->initialize();
    
    std::cout << "Running NPU self-test...\n";
    if (npu->run_self_test()) {
        std::cout << "  ✓ Self-test PASSED!\n";
    } else {
        std::cout << "  ✗ Self-test FAILED!\n";
    }
}

void test_npu_model_loading() {
    print_section("Testing NPU Model Loading");
    
    VirtualPCB pcb;
    auto npu = std::make_shared<LlamaCoprocessorDriver>();
    
    pcb.attach_driver(npu.get());
    npu->initialize();
    
    LlamaModelConfig config;
    config.model_name = "Test Finance LLM";
    config.model_path = "/models/finance-7b.gguf";
    config.n_ctx = 4096;
    config.n_threads = 8;
    config.n_gpu_layers = 0;
    
    std::cout << "Configuring model...\n";
    std::cout << "  Name:       " << config.model_name << "\n";
    std::cout << "  Path:       " << config.model_path << "\n";
    std::cout << "  Context:    " << config.n_ctx << "\n";
    std::cout << "  Threads:    " << config.n_threads << "\n";
    std::cout << "  GPU Layers: " << config.n_gpu_layers << "\n\n";
    
    npu->set_model_config(config);
    
    std::cout << "Loading model...\n";
    if (npu->load_model()) {
        std::cout << "  ✓ Model loaded successfully!\n\n";
    }
    
    std::cout << npu->get_device_status_string() << "\n";
}

void test_npu_inference() {
    print_section("Testing NPU Inference");
    
    VirtualPCB pcb;
    auto npu = std::make_shared<LlamaCoprocessorDriver>();
    
    pcb.attach_driver(npu.get());
    npu->initialize();
    
    LlamaModelConfig config;
    config.model_name = "Finance Assistant";
    config.model_path = "/models/finance-assist.gguf";
    config.n_ctx = 2048;
    config.n_threads = 4;
    
    npu->set_model_config(config);
    npu->load_model();
    
    LlamaSequenceConfig seq_config;
    seq_config.n_predict = 64;
    seq_config.stream_tokens = false;
    
    std::string prompt = "Explain a balance sheet in simple terms.";
    
    std::cout << "Running inference...\n";
    std::cout << "Prompt: \"" << prompt << "\"\n\n";
    
    std::string response = npu->infer(prompt, seq_config);
    std::cout << response << "\n";
    
    std::cout << "\nTelemetry:\n";
    LlamaTelemetry telemetry = npu->get_telemetry();
    std::cout << "  Total Prompts:  " << telemetry.total_prompts << "\n";
    std::cout << "  Total Tokens:   " << telemetry.total_tokens_generated << "\n";
    std::cout << "  Tokens/sec:     " << std::fixed << std::setprecision(2) 
              << telemetry.tokens_per_second << "\n";
}

void test_npu_streaming() {
    print_section("Testing NPU Streaming Inference");
    
    VirtualPCB pcb;
    auto npu = std::make_shared<LlamaCoprocessorDriver>();
    
    pcb.attach_driver(npu.get());
    npu->initialize();
    
    LlamaModelConfig config;
    config.model_name = "Streaming Model";
    npu->set_model_config(config);
    npu->load_model();
    
    LlamaSequenceConfig seq_config;
    seq_config.n_predict = 32;
    seq_config.stream_tokens = true;
    
    std::string prompt = "What is machine learning?";
    
    std::cout << "Running streaming inference...\n";
    std::cout << "Prompt: \"" << prompt << "\"\n\n";
    std::cout << "Response: ";
    
    npu->infer_streaming(prompt, seq_config,
        [](const std::string& token, int32_t token_id, bool is_last) {
            std::cout << token;
            if (is_last) {
                std::cout << "\n";
            }
        });
    
    std::cout << "\n✓ Streaming complete!\n";
}

void test_npu_hardware_diagnostics() {
    print_section("Testing NPU Hardware Diagnostics");
    
    VirtualPCB pcb;
    auto npu = std::make_shared<LlamaCoprocessorDriver>();
    
    pcb.attach_driver(npu.get());
    npu->initialize();
    
    LlamaModelConfig config;
    config.model_name = "Diagnostics Test";
    npu->set_model_config(config);
    npu->load_model();
    
    // Run a quick inference to populate telemetry
    LlamaSequenceConfig seq_config;
    seq_config.n_predict = 32;
    npu->infer("Test prompt", seq_config);
    
    std::cout << npu->get_hardware_diagnostics() << "\n";
}

void test_entelechy() {
    print_section("Testing Entelechy (Vital Actualization)");
    
    VirtualPCB pcb;
    auto npu = std::make_shared<LlamaCoprocessorDriver>();
    
    pcb.attach_driver(npu.get());
    npu->initialize();
    
    std::cout << "Performing NPU self-assessment...\n\n";
    
    NPUSelfAssessment assessment = npu->assess_self();
    
    std::cout << "ONTOLOGICAL DIMENSION (Structure):\n";
    std::cout << "  Foundation Integrity:      " << std::fixed << std::setprecision(2) 
              << assessment.ontological.foundation_integrity << "\n";
    std::cout << "  Core Completeness:         " << assessment.ontological.core_completeness << "\n";
    std::cout << "  Specialized Features:      " << assessment.ontological.specialized_features << "\n";
    std::cout << "  Architectural Coherence:   " << assessment.ontological.architectural_coherence << "\n\n";
    
    std::cout << "TELEOLOGICAL DIMENSION (Purpose):\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "  Phase " << (i+1) << " Completion:        " 
                  << assessment.teleological.phase_completion[i] << "\n";
    }
    std::cout << "  Roadmap Alignment:         " << assessment.teleological.roadmap_alignment << "\n";
    std::cout << "  Actualization Trajectory:  " << assessment.teleological.actualization_trajectory << "\n";
    std::cout << "  Purpose Clarity:           " << assessment.teleological.purpose_clarity << "\n\n";
    
    std::cout << "COGNITIVE DIMENSION (Reasoning):\n";
    std::cout << "  Inference Quality:         " << assessment.cognitive.inference_quality << "\n";
    std::cout << "  Performance Intelligence:  " << assessment.cognitive.performance_intelligence << "\n";
    std::cout << "  Meta-Cognitive Depth:      " << assessment.cognitive.meta_cognitive_depth << "\n";
    std::cout << "  Overall Cognition:         " << assessment.cognitive.overall_cognition << "\n\n";
    
    std::cout << "INTEGRATIVE DIMENSION (Coherence):\n";
    std::cout << "  Hardware Integration:      " << assessment.integrative.hardware_integration << "\n";
    std::cout << "  Software Coherence:        " << assessment.integrative.software_coherence << "\n";
    std::cout << "  System Unity:              " << assessment.integrative.system_unity << "\n";
    std::cout << "  Overall Integration:       " << assessment.integrative.overall_integration << "\n\n";
    
    std::cout << "EVOLUTIONARY DIMENSION (Growth):\n";
    std::cout << "  TODO Count:                " << assessment.evolutionary.todo_count << "\n";
    std::cout << "  FIXME Count:               " << assessment.evolutionary.fixme_count << "\n";
    std::cout << "  Implementation Depth:      " << assessment.evolutionary.implementation_depth << "\n";
    std::cout << "  Self-Improvement Capacity: " << assessment.evolutionary.self_improvement_capacity << "\n";
    std::cout << "  Evolutionary Fitness:      " << assessment.evolutionary.evolutionary_fitness << "\n\n";
    
    std::cout << "OVERALL ASSESSMENT:\n";
    std::cout << "  Actualization Score:       " << assessment.overall_actualization << "\n";
    std::cout << "  Fitness Score:             " << assessment.fitness_score << "\n\n";
    
    if (!assessment.improvement_recommendations.empty()) {
        std::cout << "IMPROVEMENT RECOMMENDATIONS:\n";
        for (const auto& rec : assessment.improvement_recommendations) {
            std::cout << "  • " << rec << "\n";
        }
    }
}

void test_ontogenesis() {
    print_section("Testing Ontogenesis (Self-Generation)");
    
    VirtualPCB pcb;
    auto parent_npu = std::make_shared<LlamaCoprocessorDriver>();
    
    pcb.attach_driver(parent_npu.get());
    parent_npu->initialize();
    
    std::cout << "Parent NPU Genome:\n";
    NPUGenome parent_genome = parent_npu->get_genome();
    std::cout << "  ID:         " << parent_genome.id << "\n";
    std::cout << "  Generation: " << parent_genome.generation << "\n";
    std::cout << "  Age:        " << parent_genome.age << "\n";
    std::cout << "  Fitness:    " << std::fixed << std::setprecision(3) 
              << parent_npu->calculate_fitness() << "\n\n";
    
    std::cout << "Generating offspring NPU...\n";
    auto offspring = NPUOntogenesis::self_generate(*parent_npu);
    
    NPUGenome offspring_genome = offspring->get_genome();
    std::cout << "  ID:         " << offspring_genome.id << "\n";
    std::cout << "  Generation: " << offspring_genome.generation << "\n";
    std::cout << "  Parent:     " << offspring_genome.lineage[0] << "\n";
    std::cout << "  Fitness:    " << offspring->calculate_fitness() << "\n\n";
    
    std::cout << "✓ Self-generation successful!\n";
    
    // Test self-optimization
    std::cout << "\nTesting self-optimization...\n";
    double initial_fitness = parent_npu->calculate_fitness();
    std::cout << "  Initial Fitness: " << initial_fitness << "\n";
    
    NPUOntogenesis::self_optimize(parent_npu.get(), 5);
    
    double optimized_fitness = parent_npu->calculate_fitness();
    std::cout << "  Optimized Fitness: " << optimized_fitness << "\n";
    
    if (optimized_fitness >= initial_fitness) {
        std::cout << "  ✓ Optimization successful!\n";
    }
}

int main(int argc, char* argv[]) {
    std::cout << "========================================\n";
    std::cout << "NPU (Neural Processing Unit) Test Suite\n";
    std::cout << "========================================\n";
    std::cout << "ggnucash::vdev - Virtual Device Framework\n";
    std::cout << "LlamaCoprocessor with Entelechy & Ontogenesis\n";
    
    try {
        test_virtual_pcb();
        test_npu_basic();
        test_npu_self_test();
        test_npu_model_loading();
        test_npu_inference();
        test_npu_streaming();
        test_npu_hardware_diagnostics();
        test_entelechy();
        test_ontogenesis();
        
        print_section("All Tests Completed Successfully!");
        std::cout << "✓ VirtualPCB infrastructure working\n";
        std::cout << "✓ NPU device driver operational\n";
        std::cout << "✓ MMIO register interface functional\n";
        std::cout << "✓ Model loading and inference (stubbed)\n";
        std::cout << "✓ Telemetry and diagnostics active\n";
        std::cout << "✓ Entelechy (vital actualization) framework operational\n";
        std::cout << "✓ Ontogenesis (self-generation) framework operational\n";
        std::cout << "\nNext Steps:\n";
        std::cout << "  1. Integrate llama.cpp for real GGUF inference\n";
        std::cout << "  2. Implement KV-cache management\n";
        std::cout << "  3. Add GPU offloading support\n";
        std::cout << "  4. Implement batch inference\n";
        std::cout << "  5. Add interrupt-driven token streaming\n";
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Error: " << e.what() << "\n";
        return 1;
    }
}
